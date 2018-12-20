#pragma once
#include "Test.h"
#include "QuestionService.h"
#include "ResultService.h"

namespace PTests
{
	namespace Services
	{
		using namespace Data::Models;

		class TestService : public Service<Test>
		{
		public:
			explicit TestService(bool isBinary);
		private:
			ValidationResult* validateModel(const Test& model) override;

			void includeDependent(Test& model) override;

			bool mIsBinary;
		};
	}
}
