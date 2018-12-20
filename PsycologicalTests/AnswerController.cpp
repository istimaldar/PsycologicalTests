#include "pch.h"
#include "AnswerController.h"


namespace PTests
{
	namespace Controllers
	{
		AnswerController* AnswerController::mInstance = nullptr;

		AnswerController& AnswerController::getInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new AnswerController();
			}

			return *mInstance;
		}

		void AnswerController::index(ListingPurpose purpose, ListingMessages messages,
		                             function<bool(const Answer&)> filterFunction)
		{
			listItems<Answer>(purpose, mAnswerService, messages,
			                  [this](const Answer& answer) { return answer.getText(); },
			                  [this](ListingPurpose purpose) { return resolveAction(purpose); },
			                  std::move(filterFunction));
		}

		void AnswerController::create(int questionId)
		{
			Answer* answer = createOrEdit(questionId);
			mAnswerService->create(*answer);
			delete answer;
		}

		Answer* AnswerController::createOrEdit(int questionId, int id)
		{
			list<Answer *>* questionAnswers = mAnswerService->read(
				[questionId](const Answer& answer) { return answer.getQuestionId() == questionId; });
			const auto answerNumber = static_cast<int>(questionAnswers->size() + 1);
			Utility::disposeList(*questionAnswers);

			clearConsole();
			cout << "Creating new answer..." << endl;

			cin.clear();
			cin.ignore(INT16_MAX, '\n');

			bool isCorrect;
			do
			{
				string input;
				cout << "Is answer correct (y/n): ";
				cin >> input;
				if (input == "y")
				{
					isCorrect = true;
					break;
				}
				if (input == "n")
				{
					isCorrect = false;
					break;
				}
				cout << "Incorrect input. Please, enter y or n." << endl;
			}
			while (true);

			cin.clear();
			cout << "Enter answer text:" << endl;
			cout.flush();
			cin.ignore(INT16_MAX, '\n');
			const string text = readMultiline();

			return new Answer(id, answerNumber, isCorrect, questionId, text);
		}

		void AnswerController::edit(int id)
		{
			Answer* oldAnswer = mAnswerService->readById(id);
			int questionId = oldAnswer->getQuestionId();
			delete oldAnswer;
			Answer* answer = createOrEdit(questionId, id);
			mAnswerService->update(*answer);
			delete answer;
		}

		void AnswerController::deleteItem(int id) const
		{
			mAnswerService->deleteElements(
				[id](const Answer& answer) { return answer.getId() == id; });
		}

		function<void(int)> AnswerController::resolveAction(ListingPurpose purpose)
		{
			switch (purpose)
			{
			case ListingPurpose::Edit:
				return [this](int id) { edit(id); };
			case ListingPurpose::Delete:
				return [this](int id) { deleteItem(id); };
			default:
				return [](int)
				{
				};
			}
		}

		AnswerController::AnswerController() = default;
	}
}
