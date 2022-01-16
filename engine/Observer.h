#ifndef OBSERVER_H
#define OBSERVER_H

#include <tuple>
#include <string>
#include <vector>
#include "ObjectPool.h"

#define SUBJECT_ADD_OBSERVER(sub,TEv,obs) ((static_cast<Octo::ObserverSubject<TEv>*>(&sub))->AddObserver(obs))
#define SUBJECT_REMOVE_OBSERVER(sub,TEv,obs) ((static_cast<Octo::ObserverSubject<TEv>*>(&sub))->RemoveObserver(obs))
#define SUBJECT_NOTIFY_OBSERVERS(sub,TEv,pay) ((static_cast<Octo::ObserverSubject<TEv>*>(&sub))->Notify(pay))
//TODO doubly linked list
namespace Octo
{
	template <typename TEvent>
	class IObserver
	{
	public:
		virtual void OnNotify(const TEvent& payload) = 0;
	};
	
	template <typename TEvent>
	struct ObserverNode
	{
		IObserver<TEvent>* ObserverPtr;
		ObserverNode<TEvent>* NextNodePtr;

		ObserverNode() = default;
		void Reset()
		{
			ObserverPtr = nullptr;
			NextNodePtr = nullptr;
		}
	};

	template <typename TEvent>
	class ObserverSubject
	{
	public:
		void AddObserver(IObserver<TEvent>* observerPtr)
		{
			ObserverNode<TEvent>* newNode = nodePool.GetObject();
			newNode->ObserverPtr = observerPtr;
			newNode->NextNodePtr = headNodePtr;
			headNodePtr = newNode;
		}
		void RemoveObserver(IObserver<TEvent>* observerPtr)
		{
			if (headNodePtr->ObserverPtr == observerPtr)
			{
				headNodePtr = headNodePtr->NextNodePtr;
				nodePool.ReturnObject(headNodePtr);
				return;
			}

			ObserverNode<TEvent>* currentNodePtr = headNodePtr;
			while (currentNodePtr != nullptr)
			{
				if (currentNodePtr->NextNodePtr->ObserverPtr == observerPtr)
				{
					currentNodePtr->NextNodePtr = currentNodePtr->NextNodePtr->NextNodePtr;
					nodePool.ReturnObject(currentNodePtr->NextNodeObject);
					return;
				}

				currentNodePtr = currentNodePtr->NextNodePtr;
			}
		}
		void Notify(const TEvent& payload)
		{
			ObserverNode<TEvent>* currentNodePtr = headNodePtr;
			while (currentNodePtr != nullptr)
			{
				currentNodePtr->ObserverPtr->OnNotify(payload);
				currentNodePtr = currentNodePtr->NextNodePtr;
			}
		}

	private:
		ObserverNode<TEvent>* headNodePtr;
		static ObjectPool<ObserverNode<TEvent>> nodePool;
	};
}

#endif
