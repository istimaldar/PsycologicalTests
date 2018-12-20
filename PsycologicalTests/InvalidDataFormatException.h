#pragma once
#include <stdexcept>

using namespace std;

namespace PTests
{
	namespace Infrastructure
	{
		class InvalidDataFormatException : public runtime_error
		{
		public:
			explicit InvalidDataFormatException(const string& what_arg);
		};
	}
}
