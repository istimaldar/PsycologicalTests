#pragma once
#include "Context.h"
#include "Result.h"

namespace PTests
{
	namespace Data
	{
		namespace Contexts
		{
			using namespace Models;

			class ResultContext : public Context<Result>
			{
			public:
				explicit ResultContext(bool isBinary);

				Result* read(ifstream& file) override;

				void write(ofstream& file, const Result& data) override;
			};
		}
	}
}
