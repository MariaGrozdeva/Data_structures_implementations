#include "List.h"
#include "Iterator.hpp"

template <typename T>
class DoublyLinkedList : public List<T>
{
	struct Node
	{
		T data;
		Node* previous;
		Node* next;

		Node(T data) : data(data), previous(nullptr), next(nullptr) {}
	};
	size_t count;

	Node* head;
	Node* tail;

	void CopyFrom(const DoublyLinkedList& other);
	void Free();

	bool isEmpty() const;

	void getNode(int index, Node*& nodeToFind);

public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList<T>& other);
	DoublyLinkedList<T>& operator= (const DoublyLinkedList<T>& other);
	~DoublyLinkedList();

	void pushBack(const T& el); // O(1)
	void pushFront(const T& el); // O(1)
	void insertAt(const T& el, int index); // O(n)

	T getAt(size_t index); // O(n)

	T popBack(); // O(1)
	T popFront(); // O(1)
	T removeAt(int index); // O(n)

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	size_t getSize() const;

	void print() const;

	class DoublyLLIterator : public Iterator<T>
	{
		Node* currentNode;

	public:
		DoublyLLIterator(Node* currentNode) : currentNode(currentNode) {}

		T& operator*()
		{
			return currentNode->data;
		}
		void operator++()
		{
			if (currentNode != nullptr)
				currentNode = currentNode->next;
		}
		void operator--()
		{
			if (currentNode->previous != nullptr)
				currentNode = currentNode->previous;
		}
		bool operator!=(Iterator<T>& other)
		{
			DoublyLLIterator* otherPtr = (DoublyLLIterator*)&other;
			return currentNode != otherPtr->currentNode;
		}
	};
	DoublyLLIterator begin()
	{
		return DoublyLLIterator(head);
	}
	DoublyLLIterator end()
	{
		return DoublyLLIterator(nullptr);
	}
};

template<typename T>
void DoublyLinkedList<T>::CopyFrom(const DoublyLinkedList& other)
{
	Node* otherIter = other.head;

	while (otherIter != nullptr)
	{
		pushBack(otherIter->data);
		otherIter = otherIter->next;
	}
}
template<typename T>
void DoublyLinkedList<T>::Free()
{
	Node* iter = head;

	while (iter != nullptr)
	{
		Node* toDelete = iter;
		iter = iter->next;
		delete toDelete;
	}
}

template<typename T>
bool DoublyLinkedList<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
}

template<typename T>
void DoublyLinkedList<T>::getNode(int index, Node*& nodeToFind)
{
	Node* iter = head;

	for (size_t i = 0; i < index; i++)
		iter = iter->next;
	nodeToFind = iter;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
{
	CopyFrom(other);
}
template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator= (const DoublyLinkedList<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	Free();
}

template<typename T>
void DoublyLinkedList<T>::pushBack(const T& el)
{
	Node* newNode = new Node(el);
	count++;

	if (isEmpty())
		head = tail = newNode;
	else
	{
		tail->next = newNode;
		newNode->previous = tail;
		tail = newNode;
	}
}
template<typename T>
void DoublyLinkedList<T>::pushFront(const T& el)
{
	Node* newNode = new Node(el);
	count++;

	if (isEmpty())
		head = tail = newNode;
	else
	{
		newNode->next = head;
		head->previous = newNode;
		head = newNode;
	}
}
template<typename T>
void DoublyLinkedList<T>::insertAt(const T& el, int index)
{
	if (index > count)
		throw "Invalid index!";

	else if (index == 0)
		pushFront(el);
	else if (index == count)
		pushBack(el);

	else
	{
		Node* noteAtIndex;
		getNode(index, noteAtIndex);

		Node* newNode = new Node(el);
		count++;

		newNode->next = noteAtIndex;
		newNode->previous = noteAtIndex->previous;

		noteAtIndex->previous->next = newNode;
		noteAtIndex->previous = newNode;
	}
}

template<typename T>
T DoublyLinkedList<T>::getAt(size_t index)
{
	return this->operator[](index);
}

template<typename T>
T DoublyLinkedList<T>::popBack()
{
	if (count == 0)
		throw "Error! Empty list!";

	if (count == 1)
	{
		T data = head->data;
		delete head;
		head = tail = nullptr;
		count--;

		return data;
	}

	Node* toRemove = tail;
	T data = toRemove->data;

	tail = tail->previous;

	tail->next = nullptr;

	delete toRemove;
	count--;

	return data;
}
template<typename T>
T DoublyLinkedList<T>::popFront()
{
	if (count == 0)
		throw "Error! Empty list!";

	if (count == 1)
	{
		T data = head->data;
		delete head;
		head = tail = nullptr;
		count--;

		return data;
	}

	Node* toRemove = head;
	T data = head->data;

	head = head->next;
	head->previous = nullptr;

	delete toRemove;
	count--;

	return data;
}
template<typename T>
T DoublyLinkedList<T>::removeAt(int index)
{
	if (index < 0 || index >= count)
		throw "Invalid index!";
	if (index == 0)
		return popFront();
	else if (index == count - 1)
		return popBack();

	else
	{
		Node* toRemove;
		getNode(index, toRemove);
		T data = toRemove->data;

		toRemove->previous->next = toRemove->next;

		delete toRemove;
		count--;

		return data;
	}
}

template<typename T>
const T& DoublyLinkedList<T>::operator[](size_t index) const
{
	if (index < 0 || index >= count)
		throw "Invalid index!";

	Node* iter = head;
	for (int i = 0; i < index; i++)
		iter = iter->next;

	return iter->data;
}
template<typename T>
T& DoublyLinkedList<T>::operator[](size_t index)
{
	if (index < 0 || index >= count)
		throw "Invalid index!";

	Node* nodeToGet;
	getNode(index, nodeToGet);

	return nodeToGet->data;
}

template<typename T>
size_t DoublyLinkedList<T>::getSize() const
{
	return count;
}

template<typename T>
void DoublyLinkedList<T>::print() const
{
	Node* iter = head;
	while (iter != nullptr)
	{
		cout << iter->data;
		if (iter != tail)
			cout << "<->";
		iter = iter->next;
	}
	cout << endl;
}