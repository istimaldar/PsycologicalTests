#pragma once
#include "Controller.h"
#include "Test.h"
#include "TestService.h"
#include "TestController.h"
#include "QuestionController.h"

namespace PTests
{
	namespace Controllers
	{
		using namespace Services;

		class TestController : public Controller
		{
		public:
			static TestController& getInstance();

			void index(ListingPurpose purpose, ListingMessages messages,
			           function<bool(const Test&)> filterFunction = [](const Test&) { return true; });

			void create();

			void deleteItem(int id);

			void listEditOptions(int id);

			void edit(int id);

			void run(int id) const;
		private:
			TestController();

			TestService* mTestService = new TestService(false);

			static TestController* mInstance;

			Test* createOrEdit(int id = -1);

			function<void(int)> resolveAction(ListingPurpose purpose);
		};
	}
}
