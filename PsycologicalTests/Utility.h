#pragma once
#include <list>

namespace PTests
{
	namespace Utils
	{
		using namespace std;

		class Utility
		{
		public:
			template <typename T>
			static void disposeList(list<T*>& disposable);
		};

		template <typename T>
		void Utility::disposeList(list<T *>& disposable)
		{
			for (auto element : disposable)
			{
				if (element != nullptr)
				{
					delete element;
				}
			}
			disposable.clear();
			delete &disposable;
		}
	}
}
