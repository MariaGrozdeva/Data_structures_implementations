#include "List.h"

template <typename T>
class SinglyLinkedList : public List<T>
{
	struct Node
	{
		T data;
		Node* next;

		Node(T data) : data(data), next(nullptr) {}
	};
	size_t count;

	Node* head;
	Node* tail;

	void CopyFrom(const SinglyLinkedList& other);
	void Free();

	bool isEmpty() const;

	void getNode(int index, Node*& nodeToFind);

public:
	SinglyLinkedList();
	SinglyLinkedList(const SinglyLinkedList<T>& other);
	SinglyLinkedList<T>& operator= (const SinglyLinkedList<T>& other);
	~SinglyLinkedList();

	void pushBack(const T& el); // O(1)
	void pushFront(const T& el); // O(1)
	void insertAt(const T& el, int index); // O(n)

	T getAt(int index); // O(n)

	T popBack(); // O(n)
	T popFront(); // O(1)
	T removeAt(int index); // O(n)

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	size_t getSize() const;

	void print() const;
};

template<typename T>
void SinglyLinkedList<T>::CopyFrom(const SinglyLinkedList& other)
{
	Node* otherIter = other.head;

	while (otherIter != nullptr)
	{
		pushBack(otherIter->data);
		otherIter = otherIter->next;
	}
}
template<typename T>
void SinglyLinkedList<T>::Free()
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
bool SinglyLinkedList<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
}

template<typename T>
void SinglyLinkedList<T>::getNode(int index, Node*& nodeToFind)
{
	Node* iter = head;

	for (size_t i = 0; i < index; i++)
		iter = iter->next;
	nodeToFind = iter;
}

template<typename T>
SinglyLinkedList<T>::SinglyLinkedList() : head(nullptr), tail(nullptr), count(0) {}
template<typename T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other)
{
	CopyFrom(other);
}
template<typename T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator= (const SinglyLinkedList<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
template<typename T>
SinglyLinkedList<T>::~SinglyLinkedList()
{
	Free();
}

template<typename T>
void SinglyLinkedList<T>::pushBack(const T& el)
{
	Node* newNode = new Node(el);
	count++;

	if (isEmpty())
		head = tail = newNode;
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
}
template<typename T>
void SinglyLinkedList<T>::pushFront(const T& el)
{
	Node* newNode = new Node(el);
	count++;

	if (isEmpty())
		head = tail = newNode;

	newNode->next = head;
	head = newNode;
}
template<typename T>
void SinglyLinkedList<T>::insertAt(const T& el, int index)
{
	if (index > count)
		throw "Invalid index!";

	else if (index == 0)
		pushFront(el);
	else if (index == count)
		pushBack(el);

	else
	{
		Node* previousNode;
		getNode(index - 1, previousNode);

		Node* newNode = new Node(el);
		count++;

		newNode->next = previousNode->next;
		previousNode->next = newNode;
	}
}

template<typename T>
T SinglyLinkedList<T>::getAt(int index)
{
	return this->operator[](index);
}

template<typename T>
T SinglyLinkedList<T>::popBack()
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

	getNode(count - 2, tail);

	tail->next = nullptr;

	delete toRemove;
	count--;

	return data;
}
template<typename T>
T SinglyLinkedList<T>::popFront()
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
	T data = toRemove->data;

	head = head->next;

	delete toRemove;
	count--;

	return data;
}
template<typename T>
T SinglyLinkedList<T>::removeAt(int index)
{
	if (index < 0 || index >= count)
		throw "Invalid index!";
	if (index == 0)
		return popFront();
	else if (index == count - 1)
		return popBack();

	else
	{
		Node* toRemovePrev;
		getNode(index - 1, toRemovePrev);

		Node* toRemove = toRemovePrev->next;
		T data = toRemove->data;

		toRemovePrev->next = toRemove->next;
		
		delete toRemove;
		count--;

		return data;
	}
}

template<typename T>
const T& SinglyLinkedList<T>::operator[](size_t index) const
{
	if (index < 0 || index >= count)
		throw "Invalid index!";

	Node* iter = head;
	for (int i = 0; i < index; i++)
		iter = iter->next;

	return iter->data;
}
template<typename T>
T& SinglyLinkedList<T>::operator[](size_t index)
{
	if (index < 0 || index >= count)
		throw "Invalid index!";

	Node* nodeToGet;
	getNode(index, nodeToGet);

	return nodeToGet->data;
}

template<typename T>
size_t SinglyLinkedList<T>::getSize() const
{
	return count;
}

template<typename T>
void SinglyLinkedList<T>::print() const
{
	Node* iter = head;
	while (iter != nullptr)
	{
		cout << iter->data;
		if (iter != tail)
			cout << "->";
		iter = iter->next;
	}
	cout << endl;
}