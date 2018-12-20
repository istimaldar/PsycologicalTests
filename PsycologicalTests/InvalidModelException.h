#pragma once
#include <stdexcept>

using namespace std;

namespace PTests
{
	namespace Infrastructure
	{
		class InvalidModelException : public runtime_error
		{
		public:
			explicit InvalidModelException(const string& what_arg);
		};
	}
}
