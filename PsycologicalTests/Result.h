#pragma once
#include "Model.h"

namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			class Result : public Model
			{
			public:
				explicit Result(int id);

				Result(int id, pair<int, int> interval, int testId, const string& resultName,
				       const string& resultDescription);

				const pair<int, int>& getInterval() const;

				void setInterval(const pair<int, int>& interval);

				int getTestId() const;

				void setTestId(int testId);

				const string& getResultName() const;

				void setResultName(const string& resultName);

				const string& getResultDescription() const;

				void setResultDescription(const string& resultDescription);

			private:
				pair<int, int> mInterval;

				int mTestId;

				string mResultName;

				string mResultDescription;
			};
		}
	}
}
