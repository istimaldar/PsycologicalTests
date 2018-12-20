#include "pch.h"
#include "MainController.h"
#include "TestController.h"


namespace PTests
{
	namespace Controllers
	{
		MainController* MainController::mInstance = nullptr;

		MainController& MainController::getInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new MainController();
			}

			return *mInstance;
		}

		void MainController::mainMenu()
		{
			list<pair<string, function<void()>>> menu = {
				{
					"Launch test", []()
					{
						TestController::getInstance().index(ListingPurpose::Run,
						                                    {
							                                    "Select test to run...",
							                                    "No tests yet. Create some tests first."
						                                    }
						);
					}
				},
				{"Add new test", []() { TestController::getInstance().create(); }},
				{
					"Edit test", []()
					{
						TestController::getInstance().index(ListingPurpose::Edit,
						                                    {
							                                    "Select test to edit...",
							                                    "No tests yet. Create some tests first."
						                                    });
					}
				},
				{
					"Delete test", []()
					{
						TestController::getInstance().index(ListingPurpose::Delete,
						                                    {
							                                    "Select test to delete...",
							                                    "No tests yet. Create some tests first."
						                                    });
					}
				},
				{"Exit", []() { exit(0); }}
			};
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
			do
			{
				showMenu("Welcome to test application. To begin work with tests select one item from list below.",
				         menu);
			}
			while (true);
#pragma clang diagnostic pop
		}

		MainController::MainController() = default;
	}
}
