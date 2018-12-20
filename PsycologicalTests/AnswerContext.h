#pragma once
#include "Context.h"
#include "Answer.h"

namespace PTests
{
	namespace Data
	{
		namespace Contexts
		{
			using namespace Models;


			class AnswerContext : public Context<Answer>
			{
			public:
				explicit AnswerContext(bool isBinary);

				Answer* read(ifstream& file) override;

				void write(ofstream& file, const Answer& data) override;
			};
		}
	}
}
