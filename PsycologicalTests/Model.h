#pragma once
#include <istream>

namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			using namespace std;

			class Model
			{
			public:
				explicit Model(int id);

				int getId() const;

				void setId(int value);

				virtual ~Model() = 0;
			protected:
				int mId;
			};
		}
	}
}
