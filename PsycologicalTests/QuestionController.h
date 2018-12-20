#pragma once
#include "Controller.h"
#include "Question.h"
#include "QuestionService.h"
#include "AnswerController.h"

namespace PTests
{
	namespace Controllers
	{
		using namespace Data::Models;
		using namespace Services;

		class QuestionController : public Controller
		{
		public:
			static QuestionController& getInstance();

			bool run(const Question& question, int numberOfQuestions);

			void index(ListingPurpose purpose, ListingMessages messages,
			           function<bool(const Question&)> filterFunction = [](const Question&) { return true; });

			void create(int testId);

			void edit(int id);

			void deleteItem(int id) const;

			void listEditOptions(int id);
		private:
			QuestionController();

			static QuestionController* mInstance;

			QuestionService* mQuestionService = new QuestionService(false);

			Question* createOrEdit(int testId, int id = -1);

			function<void(int)> resolveAction(ListingPurpose purpose);

			bool checkIfAnswersCorrect(list<Answer*> answers, list<int>& selectedNumbers) const;
		};
	}
}
