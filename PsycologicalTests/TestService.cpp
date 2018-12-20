#include "pch.h"
#include "TestService.h"

#include "TestContext.h"

namespace PTests
{
	namespace Services
	{
		TestService::TestService(bool isBinary) : Service(new TestContext(isBinary)), mIsBinary(isBinary)
		{
		}

		ValidationResult* TestService::validateModel(const Test& model)
		{
			return new ValidationResult{true, ""};
		}

		void TestService::includeDependent(Test& model)
		{
			int testId = model.getId();
			QuestionService questionService = QuestionService(mIsBinary);

			model.addQuestions(*questionService.read(
				[testId](const Question& question) { return question.getTestId() == testId; },
				true));

			ResultService resultService = ResultService(mIsBinary);

			model.addResults(*resultService.read(
				[testId](const Result& result) { return result.getTestId() == testId; },
				true));
		}
	}
}
