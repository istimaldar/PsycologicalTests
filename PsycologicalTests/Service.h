#pragma once
#include <functional>
#include <list>
#include "Context.h"
#include "Utility.h"
#include "InvalidModelException.h"
#include "Model.h"
#include "Storage.h"

namespace PTests
{
	namespace Services
	{
		using namespace std;
		using namespace Data::Contexts;
		using namespace Infrastructure;
		using namespace Utils;
		using namespace Data::Models;

		struct ValidationResult
		{
			bool success;
			string errorMessage;
		};

		template <class T>
		class Service
		{
			static_assert(is_base_of<Model, T>::value, "Service template parameter must be child of Model");
		public:
			explicit Service(Context<T>* context) : mContext(context)
			{
			}

			virtual void create(T& data);

			virtual T* readById(int id);

			virtual T* readById(int id, bool deep);

			virtual list<T*>* read(bool all);

			virtual list<T*>* read(function<bool(const T&)> conditions);

			virtual list<T*>* read(function<bool(const T&)> conditions, bool deep);

			virtual void update(const T& newData);

			virtual void deleteElements(function<bool(const T&)> conditions);

			virtual ~Service()
			{
				if (mContext != nullptr)
				{
					delete mContext;
				}
			}

		protected:
			Context<T>* mContext = nullptr;

			int mLastIdCache = -1;

			virtual ValidationResult* validateModel(const T& model) = 0;

			virtual void includeDependent(T& model) = 0;
		};

		template <class T>
		void Service<T>::create(T& data)
		{
			if (mLastIdCache < 0)
			{
				auto emptyList = read(false);
				Utility::disposeList<T>(*emptyList);
			}

			ValidationResult* result = validateModel(data);
			if (!result->success)
			{
				string errorMessage = result->errorMessage;
				delete result;
				throw InvalidModelException(errorMessage);
			}
			delete result;

			mLastIdCache++;
			auto* typedData = dynamic_cast<Model*>(&data);
			typedData->setId(mLastIdCache);
			ofstream file = ofstream(Storage::getInstance().getFileName(typeid(T)), ios::app | ios::ate);
			mContext->write(file, data);
			file.close();
		}

		template <class T>
		T* Service<T>::readById(int id)
		{
			return readById(id, false);
		}

		template <class T>
		list<T *>* Service<T>::read(function<bool(const T&)> conditions)
		{
			return read(conditions, false);
		}

		template <class T>
		void Service<T>::update(const T& newData)
		{
			ValidationResult* result = validateModel(newData);
			if (!result->success)
			{
				string errorMessage = result->errorMessage;
				delete result;
				throw InvalidModelException(errorMessage);
			}
			delete result;

			list<T*>* content = read(true);
			const auto* typedData = dynamic_cast<const Model*>(&newData);

			ofstream file = ofstream(Storage::getInstance().getFileName(typeid(T)), ios::out | ios::trunc);
			for (T* element : (*content))
			{
				auto* typedElement = dynamic_cast<Model*>(element);
				if (typedElement->getId() == typedData->getId())
				{
					mContext->write(file, newData);
				}
				else
				{
					mContext->write(file, *element);
				}
			}
			file.close();
			Utility::disposeList(*content);
		}

		template <class T>
		void Service<T>::deleteElements(function<bool(const T&)> conditions)
		{
			list<T*>* content = read(true);

			ofstream file = ofstream(Storage::getInstance().getFileName(typeid(T)), ios::out | ios::trunc);
			for (T* element : (*content))
			{
				if (!conditions(*element))
				{
					mContext->write(file, *element);
				}
			}
			file.close();
			Utility::disposeList(*content);
		}

		template <class T>
		list<T *>* Service<T>::read(bool all)
		{
			ifstream file = ifstream(Storage::getInstance().getFileName(typeid(T)));

			auto* result = new list<T*>();

			if (!file.good())
			{
				return result;
			}

			while (!file.eof())
			{
				T* current = mContext->read(file);
				if (current != nullptr)
				{
					const auto* typedCurrent = dynamic_cast<const Model *>(current);
					mLastIdCache = typedCurrent->getId();
					if (all)
					{
						result->push_back(current);
					}
					else
					{
						delete current;
					}
				}
			}

			return result;
		}

		template <class T>
		list<T *>* Service<T>::read(function<bool(const T&)> conditions, bool deep)
		{
			ifstream file = ifstream(Storage::getInstance().getFileName(typeid(T)));

			auto* result = new list<T*>();

			if (!file.good())
			{
				return result;
			}

			while (!file.eof())
			{
				T* current = mContext->read(file);
				if (current != nullptr)
				{
					const auto* typedCurrent = dynamic_cast<const Model *>(current);
					mLastIdCache = typedCurrent->getId();
					if (conditions(*current))
					{
						if (deep)
						{
							includeDependent(*current);
						}
						result->push_back(current);
					}
					else
					{
						delete current;
					}
				}
			}

			return result;
		}

		template <class T>
		T* Service<T>::readById(int id, bool deep)
		{
			ifstream file = ifstream(Storage::getInstance().getFileName(typeid(T)));

			T* result = nullptr;

			if (!file.good())
			{
				return result;
			}

			while (!file.eof())
			{
				T* current = mContext->read(file);
				if (current != nullptr)
				{
					auto* typedCurrent = dynamic_cast<Model *>(current);
					if (typedCurrent->getId() == id)
					{
						result = current;
						if (deep)
						{
							includeDependent(*current);
						}
						break;
					}
					else
					{
						delete current;
					}
				}
			}

			return result;
		}
	}
}
