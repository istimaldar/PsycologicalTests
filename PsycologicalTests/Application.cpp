#include "pch.h"
#include "Application.h"

#include <iostream>
#include <functional>
#include "Utility.h"

namespace PTests
{
	namespace Infrastructure
	{
		using namespace std;
		using namespace Utils;

		const size_t BUFFERS_SIZE = 65536;

		Application* Application::mInstance = nullptr;

		Application& Application::getInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new Application();
			}
			return *mInstance;
		}


		int Application::run()
		{
			MainController::getInstance().mainMenu();
			return 0;
		}

		Application::Application() = default;
	}
}
