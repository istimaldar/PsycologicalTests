#include "pch.h"
#include "Model.h"

namespace PTests
{
	namespace Data
	{
		namespace Models
		{
			Model::Model(int id) : mId(id)
			{
			}

			int Model::getId() const
			{
				return mId;
			}

			void Model::setId(int value)
			{
				mId = value;
			}

			Model::~Model() = default;
		}
	}
}
