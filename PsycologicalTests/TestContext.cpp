#include "pch.h"
#include "TestContext.h"


#include "StringStreamWriter.h"
#include "StringStreamReader.h"

namespace PTests
{
	namespace Data
	{
		namespace Contexts
		{
			using namespace Utils;

			TestContext::TestContext(bool isBinary) : Context(isBinary)
			{
			}

			Test* TestContext::read(ifstream& file)
			{
				int id;
				string title, description;
				StringStreamReader reader = StringStreamReader();

				try
				{
					file >> id >> reader.withString(title) >> reader.withString(description);
					check(file);
				}
				catch (const ifstream::failure& e)
				{
					return nullptr;
				}
				catch (const InvalidDataFormatException& e)
				{
					return nullptr;
				}

				return new Test(id, title, description);
			}

			void TestContext::write(ofstream& file, const Test& data)
			{
				StringStreamWriter writer = StringStreamWriter();

				file << data.getId() << " " << writer.withString(data.getTitle()) << " "
					<< writer.withString(data.getDescription());

				seal(file);
			}
		}
	}
}
