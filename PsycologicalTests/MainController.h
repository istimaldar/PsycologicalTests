#pragma once
#include "Controller.h"

namespace PTests
{
	namespace Controllers
	{
		class MainController : public Controller
		{
		public:
			static MainController& getInstance();

			void mainMenu();
		private:
			MainController();

			static MainController* mInstance;
		};
	}
}
