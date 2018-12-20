#pragma once
#include "Answer.h"
#include "Service.h"

namespace PTests
{
	namespace Services
	{
		using namespace Data::Models;

		class AnswerService : public Service<Answer>
		{
		public:
			explicit AnswerService(bool isBinary);
		private:
			ValidationResult* validateModel(const Answer& model) override;

			void includeDependent(Answer& model) override;

			bool mIsBinary;
		};
	}
}
