#include "pch.h"
#include "Answer.h"

namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			int Answer::getAnswerNumber() const
			{
				return mAnswerNumber;
			}

			void Answer::setAnswerNumber(int answerNumber)
			{
				mAnswerNumber = answerNumber;
			}

			bool Answer::isCorrect() const
			{
				return mIsCorrect;
			}

			void Answer::setIsCorrect(bool isCorrect)
			{
				mIsCorrect = isCorrect;
			}

			int Answer::getQuestionId() const
			{
				return mQuestionId;
			}

			void Answer::setQuestionId(int questionId)
			{
				mQuestionId = questionId;
			}

			const string& Answer::getText() const
			{
				return mText;
			}

			void Answer::setText(const string& text)
			{
				mText = text;
			}

			Answer::Answer(int id) : Model(id)
			{
			}

			Answer::Answer(int id, int answerNumber, bool isCorrectAnswer, int questionId, const string& text) :
				Model(id),
				mAnswerNumber(
					answerNumber),
				mIsCorrect(
					isCorrectAnswer),
				mQuestionId(
					questionId),
				mText(text)
			{
			}
		}
	}
}
