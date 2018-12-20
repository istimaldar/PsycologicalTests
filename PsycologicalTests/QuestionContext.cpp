#include "pch.h"
#include "QuestionContext.h"


#include "StringStreamWriter.h"
#include "StringStreamReader.h"

namespace PTests
{
	namespace Data
	{
		namespace Contexts
		{
			using namespace Utils;

			QuestionContext::QuestionContext(bool isBinary) : Context(isBinary)
			{
			}

			Question* QuestionContext::read(ifstream& file)
			{
				int id, questionNumber, testId;
				string text;
				StringStreamReader reader = StringStreamReader();
				try
				{
					file >> id >> questionNumber >> testId >> reader.withString(text);
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

				return new Question(id, questionNumber, testId, text);
			}

			void QuestionContext::write(ofstream& file, const Question& data)
			{
				StringStreamWriter writer = StringStreamWriter();

				file << data.getId() << " " << data.getQuestionNumber() << " " << data.getTestId() << " "
					<< writer.withString(data.getText());

				seal(file);
			}
		}
	}
}
