#include "pch.h"
#include "InvalidDataFormatException.h"


namespace PTests
{
	namespace Infrastructure
	{
		InvalidDataFormatException::InvalidDataFormatException(const string& what_arg) : runtime_error(what_arg)
		{
		}
	}
}
