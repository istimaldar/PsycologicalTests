#pragma once
#include "Question.h"
#include "MainController.h"

namespace PTests
{
	namespace Infrastructure
	{
		using namespace std;
		using namespace Data::Models;
		using namespace Services;
		using namespace Controllers;

		class Application
		{
		public:
			static Application& getInstance();

			int run();

		private:
			static Application* mInstance;

			Application();
		};
	}
}
