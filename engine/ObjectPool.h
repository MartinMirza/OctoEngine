#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <cstdint>
#include <bitset>
#include <unordered_map>
#include <concepts>

namespace Octo 
{
	template <typename TObject>
	concept HasResetMethod = requires(TObject t)
	{
		{ t.Reset() };
	};

	template <typename TObject>
		requires HasResetMethod<TObject>
	class ObjectPool
	{
	public:
		ObjectPool(int size) : poolSize(size)
		{
			InitializePool();
		}
		~ObjectPool()
		{
			for (int index = 0; index < poolSize; index++)
			{
				delete pool[index];
			}

			delete[] pool;
			delete[] inUse;
		}
		ObjectPool(const ObjectPool& source)
		{
			poolSize = source.poolSize;
			InitializePool();
		}
		ObjectPool& operator =(const ObjectPool& source)
		{
			if (&source == this)
			{
				return *this;
			}

			poolSize = source.poolSize;
			InitializePool();
		}
		TObject* const GetObject()
		{
			for (int index = 0; index < poolSize; index++)
			{
				if (inUse[index] == false)
				{
					inUse[index] = true;
					return pool[index];
				}
			}

			return nullptr;
		}
		void ReturnObject(TObject* objectPtr)
		{
			auto iterator = ptrToIndex.find(reinterpret_cast<std::uintptr_t>(objectPtr));

			if (iterator != ptrToIndex.end())
			{
				int index = iterator->second;
				objectPtr->Reset();
				inUse[index] = false;
			}
		}
	private:
		int poolSize = 0;
		TObject** pool;
		bool* inUse;
		std::unordered_map<std::uintptr_t, int> ptrToIndex;

		void InitializePool()
		{
			pool = new TObject* [poolSize];
			inUse = new bool [poolSize];

			for (int index = 0; index < poolSize; index++)
			{
				TObject* newObject = new TObject();

				pool[index] = newObject;
				inUse[index] = false;
				ptrToIndex.insert(std::make_pair(reinterpret_cast<std::uintptr_t>(newObject), index));
			}
		}
	};
}

#endif
