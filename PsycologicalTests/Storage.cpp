#include "pch.h"
#include "Storage.h"

namespace PTests
{
	namespace Infrastructure
	{
		Storage* Storage::mInstance = nullptr;

		Storage& Storage::getInstance()
		{
			if (mInstance == nullptr)
			{
				mInstance = new Storage();
			}
			return *mInstance;
		}

		const string Storage::getFileName(const type_info& type) const
		{
			if (mFileNames.find(type.name()) == mFileNames.end())
			{
				throw invalid_argument("Type of model not recognized");
			}
			return mFileNames.at(type.name());
		}

		Storage::Storage()
		{
		}
	}
}
