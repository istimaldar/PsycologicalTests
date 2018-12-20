#include "pch.h"
#include "QuestionController.h"

namespace PTests
{
	namespace Controllers
	{
		QuestionController* QuestionController::mInstance = nullptr;

		QuestionController& QuestionController::getInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new QuestionController();
			}

			return *mInstance;
		}

		bool QuestionController::run(const Question& question, int numberOfQuestions)
		{
			clearConsole();

			cout << "Question " << question.getQuestionNumber() << " of " << numberOfQuestions << endl;
			cout << question.getText() << endl;

			int number = 1;
			for (auto answer : question.getAnswers())
			{
				cout << number << ". " << answer->getText() << endl;
				number++;
			}

			cout << number << ". " << "Accept and continue" << endl;

			bool exit = false;
			auto selectedIndexes = list<int>();
			do
			{
				int selected;
				cout << "Enter number to change answer selection status. Selected answers: (";
				for (auto selectedIndex : selectedIndexes)
				{
					cout << selectedIndex << ", ";
				}
				cout << ")" << endl;

				cin.clear();
				cin >> selected;
				if (selected < 1 || selected > number)
				{
					cout << "Invalid input. Please, enter number between 1 and " << number << "." << endl;
				}
				else if (selected == number)
				{
					exit = true;
				}
				else
				{
					if (find(selectedIndexes.begin(), selectedIndexes.end(), selected) == selectedIndexes.end())
					{
						selectedIndexes.push_back(selected);
					}
					else
					{
						selectedIndexes.remove(selected);
					}
					selectedIndexes.sort();
				}
			}
			while (!exit);

			return checkIfAnswersCorrect(question.getAnswers(), selectedIndexes);
		}

		void QuestionController::index(ListingPurpose purpose, ListingMessages messages,
		                               function<bool(const Question&)> filterFunction)
		{
			listItems<Question>(purpose, mQuestionService, messages,
			                    [this](const Question& question) { return question.getText(); },
			                    [this](ListingPurpose purpose) { return resolveAction(purpose); },
			                    std::move(filterFunction));
		}

		void QuestionController::create(int testId)
		{
			Question* question = createOrEdit(testId);
			mQuestionService->create(*question);
			delete question;
		}

		Question* QuestionController::createOrEdit(int testId, int id)
		{
			list<Question *>* currentTestQuestions = mQuestionService->read(
				[testId](const Question& question) { return question.getTestId() == testId; });
			const auto questionNumber = static_cast<int>(currentTestQuestions->size() + 1);
			Utility::disposeList(*currentTestQuestions);

			clearConsole();
			cout << "Creating new question..." << endl;

			cin.clear();
			cin.ignore(INT16_MAX, '\n');

			string text;
			cout << "Enter question text: " << endl;
			cout.flush();
			text = readMultiline();

			return new Question(id, questionNumber, testId, text);
		}

		function<void(int)> QuestionController::resolveAction(ListingPurpose purpose)
		{
			switch (purpose)
			{
			case ListingPurpose::Edit:
				return [this](int id) { listEditOptions(id); };
			case ListingPurpose::Delete:
				return [this](int id) { deleteItem(id); };
			default:
				return [](int)
				{
				};
			};
		}

		void QuestionController::edit(int id)
		{
			Question* oldQuestion = mQuestionService->readById(id);
			const int testId = oldQuestion->getTestId();
			delete oldQuestion;
			Question* question = createOrEdit(testId, id);
			mQuestionService->update(*question);
			delete question;
		}

		void QuestionController::deleteItem(int id) const
		{
			mQuestionService->deleteElements(
				[id](const Question& question) { return question.getId() == id; });
		}

		void QuestionController::listEditOptions(int id)
		{
			list<pair<string, function<void()>>> menu = {
				{"Edit test record", [this, id]() { edit(id); }},
				{
					"Add answer", [this, id]()
					{
						AnswerController::getInstance().create(id);
					}
				},
				{
					"Edit answer", [this, id]()
					{
						AnswerController::getInstance().index(ListingPurpose::Edit,
						                                      {
							                                      "Select answer to edit...",
							                                      "No answers yet. Create some answers first."
						                                      },
						                                      [id](const Answer& answer)
						                                      {
							                                      return answer.getQuestionId() ==
								                                      id;
						                                      });
					}
				},
				{
					"Delete answer", [this, id]()
					{
						AnswerController::getInstance().index(ListingPurpose::Delete,
						                                      {
							                                      "Select answer to delete...",
							                                      "No answers yet. Create some answers first."
						                                      },
						                                      [id](const Answer& answer)
						                                      {
							                                      return answer.getQuestionId() ==
								                                      id;
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
			showMenu("Select question edit option.", menu);
		}

		bool QuestionController::checkIfAnswersCorrect(list<Answer *> answers, list<int>& selectedNumbers) const
		{
			int answerNumber = 1, amountOfChecked = 0;
			int* selectedAnswersArray = new int[selectedNumbers.size()];
			selectedNumbers.sort();
			copy(selectedNumbers.begin(), selectedNumbers.end(), selectedAnswersArray);
			bool result = true;
			for (auto answer : answers)
			{
				if ((answer->isCorrect() && selectedAnswersArray[amountOfChecked] != answerNumber) ||
					(!answer->isCorrect() && selectedAnswersArray[amountOfChecked] == answerNumber) ||
					(amountOfChecked == selectedNumbers.size()))
				{
					result = false;
					break;
				}
				else if (selectedAnswersArray[amountOfChecked] == answerNumber)
				{
					amountOfChecked++;
				}
				answerNumber++;
			}
			delete[] selectedAnswersArray;
			return result;
		}

		QuestionController::QuestionController() = default;
	}
}
