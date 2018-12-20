#pragma once
#include "Context.h"
#include "Question.h"

namespace PTests
{
	namespace Data
	{
		namespace Contexts
		{
			using namespace Models;

			class QuestionContext : public Context<Question>
			{
			public:
				explicit QuestionContext(bool isBinary);

				Question* read(ifstream& file) override;

				void write(ofstream& file, const Question& data) override;
			};
		}
	}
}
