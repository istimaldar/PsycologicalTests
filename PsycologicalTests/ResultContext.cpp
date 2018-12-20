#include "pch.h"
#include "ResultContext.h"


#include "StringStreamWriter.h"
#include "StringStreamReader.h"

namespace PTests
{
	namespace Data
	{
		namespace Contexts
		{
			using namespace Utils;

			ResultContext::ResultContext(bool isBinary) : Context(isBinary)
			{
			}

			Result* ResultContext::read(ifstream& file)
			{
				int id, intervalBegin, intervalEnd, testId;
				string resultName, resultDescription;
				StringStreamReader reader = StringStreamReader();

				try
				{
					file >> id >> intervalBegin >> intervalEnd >> testId >> reader.withString(resultName)
						>> reader.withString(resultDescription);
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

				return new Result(id, pair<int, int>(intervalBegin, intervalEnd), testId, resultName, resultDescription);
			}

			void ResultContext::write(ofstream& file, const Result& data)
			{
				StringStreamWriter writer = StringStreamWriter();

				file << data.getId() << " " << data.getInterval().first << " " << data.getInterval().second << " "
					<< data.getTestId() << " " << writer.withString(data.getResultName()) << " "
					<< writer.withString(data.getResultDescription());

				seal(file);
			}
		}
	}
}
