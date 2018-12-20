#pragma once
#include <list>
#include "Result.h"
#include "Question.h"

namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			class Test : public Model
			{
			public:
				explicit Test(int id);

				Test(int id, const string& title, const string& description);

				Test* addResults(list<Result *> results);

				Test* addResults(list<int> results);

				Test* addQuestions(list<Question *> questions);

				Test* addQuestions(list<int> questions);

				const string& getTitle() const;

				void setTitle(const string& title);

				const string& getDescription() const;

				void setDescription(const string& description);

				const list<Result *>& getResults() const;

				void setResults(const list<Result *>& results);

				const list<Question *>& getQuestions() const;

				void setQuestions(const list<Question *>& questions);

				~Test() override;

			private:
				string mTitle;

				string mDescription;

				list<Result*> mResults;

				list<Question*> mQuestions;

				void ensureQuestionsIsCleared();

				void ensureResultsIsCleared();
			};
		}
	}
}
