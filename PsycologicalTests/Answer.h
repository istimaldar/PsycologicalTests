#pragma once
#include "Model.h"
#include <string>

namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			using namespace std;

			class Answer : public Model
			{
			public:
				explicit Answer(int id);

				Answer(int id, int answerNumber, bool isCorrectAnswer, int questionId, const string& text);

				int getAnswerNumber() const;

				void setAnswerNumber(int answerNumber);

				bool isCorrect() const;

				void setIsCorrect(bool isCorrect);

				int getQuestionId() const;

				void setQuestionId(int questionId);

				const string& getText() const;

				void setText(const string& text);
			private:
				int mAnswerNumber = 1;

				bool mIsCorrect = false;

				int mQuestionId = -1;

				string mText = "";
			};
		}
	}
}
