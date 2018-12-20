#include "pch.h"
#include "AnswerService.h"
#include "AnswerContext.h"


namespace PTests
{
	namespace Services
	{
		using namespace PTests::Infrastructure;

		AnswerService::AnswerService(bool isBinary) : Service(new AnswerContext(isBinary)), mIsBinary(isBinary)
		{
		}

		ValidationResult* AnswerService::validateModel(const Answer& model)
		{
			return new ValidationResult{true, ""};
		}

		void AnswerService::includeDependent(Answer& model)
		{
		}
	}
}
