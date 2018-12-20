#include "pch.h"
#include "QuestionService.h"


#include "QuestionContext.h"
#include "AnswerService.h"

namespace PTests
{
	namespace Services
	{
		QuestionService::QuestionService(bool isBinary) : Service(new QuestionContext(isBinary)), mIsBinary(isBinary)
		{
		}

		ValidationResult* QuestionService::validateModel(const Question& model)
		{
			return new ValidationResult{true, ""};
		}

		void QuestionService::includeDependent(Question& model)
		{
			int questionId = model.getId();
			AnswerService answerService = AnswerService(mIsBinary);

			model.addAnswers(*answerService.read([questionId](const Answer& answer)
			                                     {
				                                     return answer.getQuestionId() == questionId;
			                                     },
			                                     true));
		}
	}
}
