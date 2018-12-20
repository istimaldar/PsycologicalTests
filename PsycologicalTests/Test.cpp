#include "pch.h"
#include "Test.h"


namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			const string& Test::getTitle() const
			{
				return mTitle;
			}

			void Test::setTitle(const string& title)
			{
				mTitle = title;
			}

			const string& Test::getDescription() const
			{
				return mDescription;
			}

			void Test::setDescription(const string& description)
			{
				mDescription = description;
			}

			const list<Result *>& Test::getResults() const
			{
				return mResults;
			}

			void Test::setResults(const list<Result *>& results)
			{
				mResults = results;
			}

			const list<Question *>& Test::getQuestions() const
			{
				return mQuestions;
			}

			void Test::setQuestions(const list<Question *>& questions)
			{
				mQuestions = questions;
			}

			Test::Test(int id) : Model(id)
			{
			}

			Test::Test(int id, const string& title, const string& description) : Model(id),
			                                                                     mTitle(title),
			                                                                     mDescription(description)
			{
			}

			Test* Test::addResults(list<Result *> results)
			{
				ensureResultsIsCleared();
				mResults = move(results);
				return this;
			}

			Test* Test::addResults(list<int> results)
			{
				ensureResultsIsCleared();
				for (auto result : results)
				{
					mResults.push_back(new Result(result));
				}
				return this;
			}

			Test* Test::addQuestions(list<Question *> questions)
			{
				ensureQuestionsIsCleared();
				mQuestions = move(questions);
				return this;
			}

			Test* Test::addQuestions(list<int> questions)
			{
				ensureQuestionsIsCleared();
				for (auto question : questions)
				{
					mQuestions.push_back(new Question(question));
				}
				return this;
			}

			void Test::ensureQuestionsIsCleared()
			{
				for (auto question : mQuestions)
				{
					delete question;
				}
				mQuestions.clear();
			}

			void Test::ensureResultsIsCleared()
			{
				for (auto result : mResults)
				{
					delete result;
				}
				mResults.clear();
			}

			Test::~Test()
			{
				ensureQuestionsIsCleared();
				ensureResultsIsCleared();
			}
		}
	}
}
