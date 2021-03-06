// circularList list with header node

#ifndef circularListWithHeader_
#define circularListWithHeader_

#include<iostream>
#include<sstream>
#include<string>
#include "chainNode.h"
#include "myExceptions.h"

using namespace std;

/**
Double linked list node.
	element
	prev
	next
*/
template <class T>
struct doubleLinkedChainNode : chainNode<T>
{
	T element;
	doubleLinkedChainNode<T>* prev, * next;

	doubleLinkedChainNode()
	{
		next = nullptr;
		prev = nullptr;
	}

	doubleLinkedChainNode(
		const T& _element,
		doubleLinkedChainNode<T>* _prev,
		doubleLinkedChainNode<T>* _next) : element(_element), next(_next), prev(_prev) { }
};

/**
Double linked list.
	head
	tail
*/
template<class T>
class circularListWithHeader
{
public:
	// constructor
	circularListWithHeader();

	// some methods
	int size() const { return listSize; }
	int indexOf(const T& theElement) const;
	void insert(int theIndex, const T& theElement);
	void output(ostream& out) const;
	doubleLinkedChainNode<T>* remove(int index);

	/**
	Iterator inline class.
	*/
	class Iterator
	{
	public:
		Iterator() : current(headNode->next) { }
		Iterator(const doubleLinkedChainNode<T>* node) : current(node) { }

		Iterator& operator=(doubleLinkedChainNode<T>* node)
		{
			this->current = node;
			return *this;
		}
		Iterator& operator++()
		{
			current = current->next;
			return *this;
		}
		Iterator operator++(int)
		{
			Iterator iterator = *this;
			++* this;
			return iterator;
		}
		bool operator!=(const Iterator& iterator)
		{
			return current != iterator.current;
		}
		int operator*()
		{
			return current->element;
		}

	private:
		const doubleLinkedChainNode<T>* current;
	};

	Iterator begin()
	{
		return Iterator(headNode->next);
	}
	Iterator head()
	{
		return Iterator(headNode);
	}
	Iterator end()
	{
		return Iterator(tailNode->prev);
	}

protected:
	void checkIndex(int theIndex) const;
	// throw illegalIndex if theIndex invalid
	doubleLinkedChainNode<T>* headNode, tailNode;
	int listSize;              // number of elements in list
};

template<class T>
circularListWithHeader<T>::circularListWithHeader()
{// Constructor.
	headNode = new doubleLinkedChainNode<T>();
	headNode->next = headNode;
	tailNode = new doubleLinkedChainNode<T>();
	listSize = 0;
}

template<class T>
void circularListWithHeader<T>::checkIndex(int theIndex) const
{// Verify that theIndex is between 0 and listSize - 1.
	if (theIndex < 0 || theIndex >= listSize)
	{
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

}

template<class T>
int circularListWithHeader<T>::indexOf(const T& theElement) const
{// Return index of first occurrence of theElement.
 // Return -1 if theElement not in list.

   // Put theElement in header node
	headerNode->element = theElement;

	// search the chain for theElement
	chainNode<T>* currentNode = headerNode->next;
	int index = 0;  // index of currentNode
	while (currentNode->element != theElement)
	{
		// move to next node
		currentNode = currentNode->next;
		index++;
	}

	// make sure we found matching element
	if (currentNode == headerNode)
		return -1;
	else
		return index;
}

template<class T>
void circularListWithHeader<T>::insert(int theIndex, const T& theElement)
{// Insert theElement so that its index is theIndex.
	if (theIndex < 0 || theIndex > listSize)
	{// invalid index
		ostringstream s;
		s << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(s.str());
	}

	// find predecessor of new element
	chainNode<T>* p = headerNode;
	for (int i = 0; i < theIndex; i++)
		p = p->next;

	// insert after p
	p->next = new chainNode<T>(theElement, p->next);

	listSize++;
}

template<class T>
void circularListWithHeader<T>::output(ostream& out) const
{// Put the list into the stream out.
	for (chainNode<T>* currentNode = headerNode->next;
		currentNode != headerNode;
		currentNode = currentNode->next)
		out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const circularListWithHeader<T>& x)
{
	x.output(out); return out;
}

#endif
