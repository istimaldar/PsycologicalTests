#pragma once
#include <list>
#include <functional>
#include "Service.h"

namespace PTests
{
	namespace Controllers
	{
		using namespace std;
		using namespace PTests::Services;

		enum ListingPurpose
		{
			Run = 1,
			Edit = 2,
			Delete = 3
		};

		struct ListingMessages
		{
			string greeting;
			string empty;
		};

		class Controller
		{
		public:
			virtual ~Controller() = 0;

		protected:
			void showMenu(string title, list<pair<string, function<void()>>>& menu);

			static void clearConsole();
			string readMultiline();

			template <typename T>
			void listItems(ListingPurpose purpose, Service<T>* service, ListingMessages messages,
			               function<string(T)> promptFunction,
			               function<function<void(int)>(ListingPurpose)> actionResolver,
			               function<bool(const T&)> filterFunction = [](const T&) { return true; });

			string readMultiline() const;
		};

		template <typename T>
		void Controller::listItems(ListingPurpose purpose, Service<T>* service, ListingMessages messages,
		                           function<string(T)> promptFunction,
		                           function<function<void(int)>(ListingPurpose)> actionResolver,
		                           function<bool(const T&)> filterFunction)
		{
			static_assert(is_base_of<Model, T>::value, "Type parameter must br child of Model");
			clearConsole();
			cout << messages.greeting << endl;
			list<T *>* items = service->read(true);

			int number = 0;
			if (!items->empty())
			{
				for (auto item : (*items))
				{
					number++;
					cout << number << ". " << promptFunction(*item) << endl;
				}
			}
			else
			{
				cout << messages.empty << endl;
			}

			number++;
			cout << number << ". Back to main menu" << endl;

			number++;
			cout << number << ". Exit" << endl;

			function<void(int)> itemAction = actionResolver(purpose);

			int result;
			do
			{
				cout << "Select menu item: ";
				cin >> result;
				if (result > 0 & result <= number)
				{
					break;
				}
				else
				{
					cout << "Invalid input. Please, enter number between 1 and " << number << "." << endl;
				}
			}
			while (true);

			function<void()> menuItems[] = {
				[this, itemAction, result, items]()
				{
					int i = result - 1;
					auto itemsIterator = items->begin();
					while (i > 0 && itemsIterator != items->end())
					{
						++itemsIterator;
						i--;
					}
					auto* typedItem = dynamic_cast<Model *>((*itemsIterator));
					itemAction(typedItem->getId());
				},
				{
					[]()
					{
					}
				},
				{[]() { exit(0); }}
			};
			const int functionNumber = (result - number + 3) > 0 ? result - number + 2 : 0;

			menuItems[functionNumber]();

			Utility::disposeList(*items);
		}
	}
}
