#include "pch.h"
#include "StringStreamWriter.h"

namespace PTests
{
	namespace Data
	{
		namespace Utils
		{
			StringStreamWriter& StringStreamWriter::withString(const string& target)
			{
				content = &target;
				return *this;
			}

			ostream& operator<<(ostream& stream, StringStreamWriter& object)
			{
				if (object.content != nullptr)
				{
					stream << object.content->length() << " " << (*object.content).c_str();
				}

				object.content = nullptr;

				return stream;
			}
		}
	}
}
