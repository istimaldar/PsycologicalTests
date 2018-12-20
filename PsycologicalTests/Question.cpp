#include "pch.h"
#include "Question.h"

namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			int Question::getQuestionNumber() const
			{
				return mQuestionNumber;
			}

			void Question::setQuestionNumber(int questionNumber)
			{
				mQuestionNumber = questionNumber;
			}

			const string& Question::getText() const
			{
				return mText;
			}

			void Question::setText(const string& text)
			{
				mText = text;
			}

			const list<Answer *>& Question::getAnswers() const
			{
				return mAnswers;
			}

			void Question::setAnswers(const list<Answer *>& answers)
			{
				mAnswers = answers;
			}

			int Question::getTestId() const
			{
				return mTestId;
			}

			void Question::setTestId(int testId)
			{
				mTestId = testId;
			}

			Question::Question(int id) : Model(id)
			{
			}

			Question::Question(int id, int questionNumber, int testId, const string& text) : Model(id),
			                                                                                 mQuestionNumber(
				                                                                                 questionNumber),
			                                                                                 mTestId(testId),
			                                                                                 mText(text)
			{
			}

			Question* Question::addAnswers(list<Answer *> answers)
			{
				ensureAnswersIsCleared();
				mAnswers = move(answers);
				return this;
			}

			Question* Question::addAnswers(list<int> answers)
			{
				ensureAnswersIsCleared();
				for (auto answer : answers)
				{
					mAnswers.push_back(new Answer(answer));
				}
				return this;
			}

			Question::~Question()
			{
				ensureAnswersIsCleared();
			}

			void Question::ensureAnswersIsCleared()
			{
				for (auto answer : mAnswers)
				{
					delete answer;
				}
				mAnswers.clear();
			}
		}
	}
}
