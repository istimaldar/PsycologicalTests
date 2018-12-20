#pragma once
#include <iostream>
#include <fstream>
#include "InvalidDataFormatException.h"


namespace PTests
{
	namespace Data
	{
		namespace Contexts
		{
			using namespace std;
			using namespace Infrastructure;

			template <typename T>
			class Context
			{
			public:
				virtual ~Context() = default;

				explicit Context(bool isBinary) : mIsBinary(isBinary)
				{
				}

				virtual T* read(ifstream& file) = 0;

				virtual void write(ofstream& file, const T& data) = 0;
			protected:
				void seal(ofstream& file);

				void check(ifstream& file);

				bool mIsBinary = false;
			private:
				const string RECORDS_SEPARATOR = "\n";
			};

			template <typename T>
			void Context<T>::seal(ofstream& file)
			{
				size_t size = RECORDS_SEPARATOR.length();

				file.write(RECORDS_SEPARATOR.c_str(), size);
			}

			template <typename T>
			void Context<T>::check(ifstream& file)
			{
				size_t size = RECORDS_SEPARATOR.length();
				char* buffer = new char[size + 1];
				buffer[size] = '\0';

				file.read(buffer, size);
				string result = buffer;

				delete[] buffer;

				if (result != RECORDS_SEPARATOR)
				{
					throw InvalidDataFormatException("Records in data file has wrong format");
				}
			}
		}
	}
}


