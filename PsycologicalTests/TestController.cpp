#include "pch.h"
#include "TestController.h"
#include "ResultController.h"


namespace PTests
{
	namespace Controllers
	{
		TestController* TestController::mInstance = nullptr;

		TestController& TestController::getInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new TestController();
			}

			return *mInstance;
		}

		void TestController::index(ListingPurpose purpose, ListingMessages messages,
		                           function<bool(const Test&)> filterFunction)
		{
			listItems<Test>(purpose, mTestService, messages, [this](const Test& test) { return test.getTitle(); },
			                [this](ListingPurpose purpose) { return resolveAction(purpose); },
			                std::move(filterFunction));
		}

		function<void(int)> TestController::resolveAction(ListingPurpose purpose)
		{
			switch (purpose)
			{
			case ListingPurpose::Delete:
				return [this](int id) { return deleteItem(id); };
			case ListingPurpose::Edit:
				return [this](int id) { return listEditOptions(id); };
			case ListingPurpose::Run:
				return [this](int id) { return run(id); };
			}
		}

		void TestController::deleteItem(int id)
		{
			mTestService->deleteElements([id](const Test& test) { return test.getId() == id; });
		}

		void TestController::listEditOptions(int id)
		{
			list<pair<string, function<void()>>> menu = {
				{"Edit test record", [this, id]() { edit(id); }},
				{
					"Add question", [id]()
					{
						QuestionController::getInstance().create(id);
					}
				},
				{
					"Edit question", [id]()
					{
						QuestionController::getInstance().index(ListingPurpose::Edit,
						                                        {
							                                        "Select question to edit...",
							                                        "No questions yet. Create some questions first."
						                                        },
						                                        [id](const Question& question)
						                                        {
							                                        return question.getTestId() ==
								                                        id;
						                                        });
					}
				},
				{
					"Delete question", [id]()
					{
						QuestionController::getInstance().index(ListingPurpose::Delete,
						                                        {
							                                        "Select question to delete...",
							                                        "No questions yet. Create some questions first."
						                                        },
						                                        [id](const Question& question)
						                                        {
							                                        return question.getTestId() == id;
						                                        });
					}
				},
				{"Add result", [id]() { ResultController::getInstance().create(id); }},
				{
					"Edit result", [id]()
					{
						ResultController::getInstance().index(ListingPurpose::Edit,
						                                      {
							                                      "Select result to edit...",
							                                      "No results yet. Create some results first."
						                                      },
						                                      [id](const Result& result)
						                                      {
							                                      return result.getTestId() == id;
						                                      });
					}
				},
				{
					"Delete result", [id]()
					{
						ResultController::getInstance().index(ListingPurpose::Delete,
						                                      {
							                                      "Select result to delete...",
							                                      "No results yet. Create some results first."
						                                      },
						                                      [id](const Result& result)
						                                      {
							                                      return result.getTestId() == id;
						                                      });
					}
				},
				{
					"Back to main menu", []()
					{
					}
				},
				{"Exit", []() { exit(0); }}
			};
			showMenu("Select test edit option.", menu);
		}

		void TestController::run(int id) const
		{
			Test* test = mTestService->readById(id, true);
			int correctAnswers = 0;
			const int numberOfQuestions = static_cast<int>(test->getQuestions().size());

			for (auto question : test->getQuestions())
			{
				bool isQuestionCorrect = QuestionController::getInstance().run(*question, numberOfQuestions);
				if (isQuestionCorrect)
				{
					correctAnswers++;
				}
			}

			ResultController::getInstance().run(test->getResults(), correctAnswers, numberOfQuestions);

			delete test;
		}

		Test* TestController::createOrEdit(int id)
		{
			string title;

			clearConsole();
			cout << "Creating new test..." << endl;

			cin.clear();
			cin.ignore(INT16_MAX, '\n');

			cout << "Enter test title: " << endl;
			cout.flush();
			getline(cin, title);

			cin.clear();

			cout << "Enter test description: " << endl;
			cout.flush();
			string description = readMultiline();

			title = title.empty() ? "NOTITLE" : title;
			description = description.empty() ? "NODESCRIPTION" : description;

			return new Test(id, title, description);
		}

		void TestController::create()
		{
			Test* test = createOrEdit();
			mTestService->create(*test);
			delete test;
		}

		void TestController::edit(int id)
		{
			Test* test = createOrEdit(id);
			mTestService->update(*test);
			delete test;
		}

		TestController::TestController() = default;
	}
}
