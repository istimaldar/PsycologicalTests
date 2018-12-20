#pragma once
#include <list>
#include "Answer.h"
#include "Model.h"

namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			using namespace std;

			class Question : public Model
			{
			public:
				explicit Question(int id);

				Question(int id, int questionNumber, int testId, const string& text);

				Question* addAnswers(list<Answer *> answers);

				Question* addAnswers(list<int> answers);

				int getQuestionNumber() const;

				void setQuestionNumber(int questionNumber);

				const string& getText() const;

				void setText(const string& text);

				const list<Answer *>& getAnswers() const;

				void setAnswers(const list<Answer *>& answers);

				int getTestId() const;

				void setTestId(int testId);

				~Question() override;

			private:
				int mQuestionNumber = 1;

				list<Answer*> mAnswers = list<Answer*>();

				int mTestId = -1;

				string mText = "";

				void ensureAnswersIsCleared();
			};
		}
	}
}
