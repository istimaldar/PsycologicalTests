#pragma once
#include <fstream>

namespace PTests
{
	namespace Data
	{
		namespace Utils
		{
			using namespace std;

			class StringStreamWriter
			{
			public:
				StringStreamWriter& withString(const string& target);

				friend ostream& operator<<(ostream& stream, StringStreamWriter& object);
			private:
				const string* content;
			};
		}
	}
}
