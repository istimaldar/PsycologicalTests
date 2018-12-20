#pragma once
#include <fstream>

namespace PTests
{
	namespace Data
	{
		namespace Utils
		{
			using namespace std;

			class StringStreamReader
			{
			public:
				StringStreamReader& withString(string& target);

				friend istream& operator>>(istream& stream, StringStreamReader& object);
			private:
				string* content;
			};
		}
	}
}
