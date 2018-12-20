#pragma once
#include "Controller.h"
#include "Result.h"
#include "ResultService.h"
#include "QuestionService.h"

namespace PTests
{
	namespace Controllers
	{
		using namespace Data::Models;
		using namespace Services;

		class ResultController : public Controller
		{
		public:
			static ResultController& getInstance();

			void run(const list<Result*> results, int numberOfCorrectAnswers, int numberOfQuestions);

			void index(ListingPurpose purpose, ListingMessages messages,
			           function<bool(const Result&)> filterFunction = [](const Result&) { return true; });

			void create(int testId);

			void edit(int id);

			void deleteItem(int id);
		private:
			ResultController();

			static ResultController* mInstance;

			ResultService* mResultService = new ResultService(false);

			QuestionService* mQuestionService = new QuestionService(false);

			Result* createOrEdit(int testId, int id = -1);

			function<void(int)> resolveAction(ListingPurpose purpose);

			static bool validateResultInterval(int value, list<pair<int, int>>& intervals);
		};
	}
}
