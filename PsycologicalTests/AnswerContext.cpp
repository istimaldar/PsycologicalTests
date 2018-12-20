#include "pch.h"
#include "AnswerContext.h"


#include "StringStreamWriter.h"
#include "StringStreamReader.h"


namespace PTests
{
	namespace Data
	{
		namespace Contexts
		{
			using namespace Utils;

			AnswerContext::AnswerContext(bool isBinary) : Context(isBinary)
			{
			}

			Answer* AnswerContext::read(ifstream& file)
			{
				int id, answerNumber, questionId;
				bool isCorrectAnswer;
				string text;
				StringStreamReader reader = StringStreamReader();

				try
				{
					file >> id >> answerNumber >> isCorrectAnswer >> questionId >> reader.withString(text);
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

				return new Answer(id, answerNumber, isCorrectAnswer, questionId, text);
			}

			void AnswerContext::write(ofstream& file, const Answer& data)
			{
				StringStreamWriter writer = StringStreamWriter();

				file << data.getId() << " " << data.getAnswerNumber() << " " << data.isCorrect() << " " << data.
					getQuestionId()
					<< " " << writer.withString(data.getText());

				seal(file);
			}
		}
	}
}
