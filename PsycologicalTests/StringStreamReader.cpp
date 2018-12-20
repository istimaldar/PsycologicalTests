#include "pch.h"
#include "StringStreamReader.h"


namespace PTests
{
	namespace Data
	{
		namespace Utils
		{
			StringStreamReader& StringStreamReader::withString(string& target)
			{
				content = &target;
				return *this;
			}

			istream& operator>>(istream& stream, StringStreamReader& object)
			{
				if (object.content != nullptr)
				{
					size_t size;
					stream >> size;

					if (stream.good())
					{
						char* buffer = new char[size + 1];
						buffer[size] = '\0';

						stream.ignore();
						stream.read(buffer, size * sizeof(char));

						(*object.content) = buffer;
						delete[] buffer;
					}
				}

				object.content = nullptr;

				return stream;
			}
		}
	}
}
