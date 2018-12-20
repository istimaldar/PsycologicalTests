#include "pch.h"
#include "Controller.h"

#include <iostream>
#include <string>

namespace PTests
{
	namespace Controllers
	{
		void Controller::showMenu(std::string title,
		                          std::list<std::pair<std::string, std::function<void()>>>& menu)
		{
			clearConsole();
			cout << title << endl;
			int number = 1;
			for (auto iterator = menu.begin(); iterator != menu.end(); iterator++, number++)
			{
				auto menuItem = *iterator;
				cout << number << ". " << menuItem.first << endl;
			}
			int result = 0;
			do
			{
				cout << "Select menu item: ";
				cin >> result;
				if (result >= 1 && result <= number)
				{
					auto iterator = menu.begin();
					while (result > 1)
					{
						iterator++;
						result--;
					}
					(*iterator).second();
					break;
				}
				else
				{
					cout << "Invalid input. Please, enter number between 1 and " << number << "." << endl;
					cin.clear();
					cin.ignore(INT16_MAX, '\n');
				}
			}
			while (true);
		}

		void Controller::clearConsole()
		{
#if defined(_WIN32) || defined(_WIN64)
			system("cls");
#else
		system("clear");
#endif
		}

		string Controller::readMultiline()
		{
			string result;
			do
			{
				string buffer;
				getline(cin, buffer);
				if (buffer.empty())
				{
					result.pop_back();
					break;
				}
				result += buffer + '\n';
			}
			while (true);
			return result;
		}

		Controller::~Controller() = default;
	}
}
