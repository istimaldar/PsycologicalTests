#include "pch.h"
#include "ResultService.h"


#include "ResultContext.h"

namespace PTests
{
	namespace Services
	{
		ResultService::ResultService(bool isBinary) : Service(new ResultContext(isBinary)), mIsBinary(isBinary)
		{
		}

		ValidationResult* ResultService::validateModel(const Result& model)
		{
			return new ValidationResult{true, ""};
		}

		void ResultService::includeDependent(Result& model)
		{
		}
	}
}
