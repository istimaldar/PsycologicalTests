#pragma once
#include <string>
#include <typeinfo>
#include <unordered_map>
#include "Answer.h"
#include "Question.h"
#include "Test.h"
#include "Result.h"

namespace PTests
{
	namespace Infrastructure
	{
		using namespace std;
		using namespace PTests::Data::Models;

		class Storage
		{
		public:
			static Storage& getInstance();

			const string getFileName(const type_info& type) const;
		private:
			static Storage* mInstance;

			Storage();

			const unordered_map<string, string> mFileNames = {
				{typeid(Answer).name(), "Answers"},
				{typeid(Question).name(), "Question"},
				{typeid(Result).name(), "Results"},
				{typeid(Test).name(), "Test"}
			};
		};
	}
}
