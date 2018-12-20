#include "pch.h"
#include "InvalidModelException.h"

namespace PTests
{
	namespace Infrastructure
	{
		InvalidModelException::InvalidModelException(const string& what_arg) : runtime_error(what_arg)
		{
		}
	}
}
