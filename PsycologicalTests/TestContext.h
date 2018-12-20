#pragma once
#include "Context.h"
#include "Test.h"

namespace PTests
{
	namespace Data
	{
		namespace Contexts
		{
			using namespace Models;

			class TestContext : public Context<Test>
			{
			public:
				explicit TestContext(bool isBinary);

				Test* read(ifstream& file) override;

				void write(ofstream& file, const Test& data) override;
			};
		}
	}
}
