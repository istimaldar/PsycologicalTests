#include "pch.h"
#include "ResultController.h"

namespace PTests
{
	namespace Controllers
	{
		ResultController* ResultController::mInstance = nullptr;

		ResultController& ResultController::getInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new ResultController();
			}

			return *mInstance;
		}

		void ResultController::index(ListingPurpose purpose, ListingMessages messages,
		                             function<bool(const Result&)> filterFunction)
		{
			listItems<Result>(purpose, mResultService, messages,
			                  [this](const Result& result) { return result.getResultName(); },
			                  [this](ListingPurpose purpose) { return resolveAction(purpose); },
			                  std::move(filterFunction));
		}

		void ResultController::create(int testId)
		{
			Result* result = createOrEdit(testId);
			mResultService->create(*result);
			delete result;
		}

		void ResultController::edit(int id)
		{
			Result* oldResult = mResultService->readById(id);
			int testId = oldResult->getTestId();
			delete oldResult;
			Result* result = createOrEdit(testId, id);
			mResultService->update(*result);
			delete result;
		}

		void ResultController::deleteItem(int id)
		{
			mResultService->deleteElements([id](const Result& result) { return result.getId() == id; });
		}

		Result* ResultController::createOrEdit(int testId, int id)
		{
			list<Result *>* resultsForTest = mResultService->read(
				[testId](const Result& result) { return result.getTestId() == testId; });
			auto takenIntervals = list<pair<int, int>>();
			for (auto result : (*resultsForTest))
			{
				takenIntervals.push_back(result->getInterval());
			}
			Utility::disposeList(*resultsForTest);

			list<Question *>* questionsInTest = mQuestionService->read(
				[testId](const Question& question) { return question.getTestId() == testId; });
			auto numberOfQuestions = static_cast<int>(questionsInTest->size());
			Utility::disposeList(*questionsInTest);


			clearConsole();
			cout << "Creating new result..." << endl;
			cout << "Number of questions: " << numberOfQuestions << endl;
			cout << "Existing intervals: ";
			for (auto interval : takenIntervals)
			{
				cout << "[" << interval.first << "; " << interval.second << "] ";
			}
			cout << endl;

			cin.clear();

			int lowerBound = -1;
			cout << "Enter lower bound: ";
			cout.flush();
			do
			{
				cin >> lowerBound;
				if (validateResultInterval(lowerBound, takenIntervals))
				{
					if (lowerBound >= 0 && lowerBound <= numberOfQuestions)
					{
						break;
					}
					else
					{
						cout << "Invalid input. Please, enter number between 0 and " << numberOfQuestions << "." <<
							endl;
					}
				}
			}
			while (true);

			cin.clear();

			int upperBound = -1;
			cout << "Enter upper bound: ";
			cout.flush();
			do
			{
				cin >> upperBound;
				if (validateResultInterval(upperBound, takenIntervals))
				{
					if (upperBound >= lowerBound && upperBound <= numberOfQuestions)
					{
						break;
					}
					else
					{
						cout << "Invalid input. Please, enter number between " << lowerBound << " and " <<
							numberOfQuestions
							<< "." << endl;
					}
				}
			}
			while (true);

			cin.clear();
			cin.ignore(INT16_MAX, '\n');

			cout << "Enter result name: " << endl;
			cout.flush();
			string name;
			getline(cin, name);

			cin.clear();

			cout << "Enter result description: " << endl;
			cout.flush();
			string description;
			description = readMultiline();

			return new Result(id, pair<int, int>(lowerBound, upperBound), testId, name, description);
		}

		function<void(int)> ResultController::resolveAction(ListingPurpose purpose)
		{
			switch (purpose)
			{
			case ListingPurpose::Edit:
				return [this](int id) { return edit(id); };
			case ListingPurpose::Delete:
				return [this](int id) { return deleteItem(id); };
			default:
				return [](int)
				{
				};
			}
		}

		bool ResultController::validateResultInterval(int value, list<pair<int, int>>& intervals)
		{
			for (auto interval : intervals)
			{
				if (value >= interval.first && value <= interval.second)
				{
					cout << "Invalid value! Value is intersecting with interval [" << interval.first << "; "
						<< interval.second << "].";
					return false;
				}
			}
			return true;
		}

		void ResultController::run(list<Result *> results, int numberOfCorrectAnswers, int numberOfQuestions)
		{
			clearConsole();
			cout << "Test results:" << endl;

			bool found = false;
			for (auto* result : results)
			{
				if (numberOfCorrectAnswers >= result->getInterval().first &&
					numberOfCorrectAnswers <= result->getInterval().second)
				{
					cout << "Correct answers: " << numberOfCorrectAnswers << " of " << numberOfQuestions << endl;
					cout << result->getResultName() << endl;
					cout << result->getResultDescription() << endl;
					found = true;
					break;
				}
			}

			if (!found)
			{
				cout << "Result for " << numberOfCorrectAnswers << " not found. Check test for accuracy." << endl;
			}

			cout << "Press enter to return to main menu...";

			cin.clear();
			cin.ignore(INT16_MAX, '\n');

			do
			{
			}
			while (cin.get() != '\n');
		}


		ResultController::ResultController() = default;
	}
}
