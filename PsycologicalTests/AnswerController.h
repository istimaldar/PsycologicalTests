#pragma once
#include "Controller.h"
#include "Answer.h"
#include "AnswerService.h"
#include <functional>

namespace PTests
{
	namespace Controllers
	{
	using namespace Services;
	using namespace Data::Models;

	class AnswerController : public Controller
	{
	public:
		static AnswerController& getInstance();

		void index(ListingPurpose purpose, ListingMessages messages,
		           function<bool(const Answer&)> filterFunction = [](const Answer&) { return true; });

		void create(int questionId);

		void edit(int id);

		void deleteItem(int id) const;
	private:
		AnswerController();

		static AnswerController* mInstance;

		AnswerService* mAnswerService = new AnswerService(false);

		Answer* createOrEdit(int questionId, int id = -1);

		function<void(int)> resolveAction(ListingPurpose purpose);
	};
	}
}
