#pragma once
#include "Result.h"
#include "Service.h"

namespace PTests
{
	namespace Services
	{
		using namespace Data::Models;

		class ResultService : public Service<Result>
		{
		public:
			explicit ResultService(bool isBinary);

		private:
			ValidationResult* validateModel(const Result& model) override;

			void includeDependent(Result& model) override;

			bool mIsBinary;
		};
	}
}
