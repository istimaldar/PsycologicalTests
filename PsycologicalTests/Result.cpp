#include "pch.h"
#include "Result.h"


namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			const pair<int, int>& Result::getInterval() const
			{
				return mInterval;
			}

			void Result::setInterval(const pair<int, int>& interval)
			{
				mInterval = interval;
			}

			int Result::getTestId() const
			{
				return mTestId;
			}

			void Result::setTestId(int testId)
			{
				mTestId = testId;
			}

			Result::Result(int id) : Model(id), mTestId(-1)
			{
			}

			Result::Result(int id, pair<int, int> interval, int testId, const string& resultName,
			               const string& resultDescription) : Model(id),
			                                                  mInterval(move(interval)),
			                                                  mTestId(testId),
			                                                  mResultName(resultName),
			                                                  mResultDescription(resultDescription)
			{
			}

			const string& Result::getResultName() const
			{
				return mResultName;
			}

			void Result::setResultName(const string& resultName)
			{
				mResultName = resultName;
			}

			const string& Result::getResultDescription() const
			{
				return mResultDescription;
			}

			void Result::setResultDescription(const string& resultDescription)
			{
				mResultDescription = resultDescription;
			}
		}
	}
}
