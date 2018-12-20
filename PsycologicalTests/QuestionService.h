#pragma once
#include "Question.h"
#include "Service.h"

namespace PTests
{
	namespace Services
	{
		using namespace Data::Models;

		class QuestionService : public Service<Question>
		{
		public:
			explicit QuestionService(bool isBinary);
		private:
			ValidationResult* validateModel(const Question& model) override;

			void includeDependent(Question& model) override;

			bool mIsBinary;
		};
	}
}
