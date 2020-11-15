#include <iostream>
using namespace std;

template <typename T>
class LinkedQueue
{
	struct Node
	{
		T data;
		Node* next;

		Node(T data) : data(data), next(nullptr) {}
	};

	Node* head;
	Node* tail;

	void CopyFrom(const LinkedQueue<T>& other);
	void Free();

	bool isEmpty() const;

public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue<T>& other);
	LinkedQueue<T>& operator= (const LinkedQueue<T>& other);
	~LinkedQueue();

	void enqueue(T element);
	T dequeue();
	void print() const;
};

template <typename T>
void LinkedQueue<T>::CopyFrom(const LinkedQueue<T>& other)
{
	if (other.isEmpty())
		head = tail = nullptr;

	else
	{
		head = new Node(other.head->data);
		Node* thisIter = head;
		Node* otherIter = other.head;

		while (otherIter->next != nullptr)
		{
			otherIter = otherIter->next;
			Node* newNode = new Node(otherIter->data);

			thisIter->next = newNode;
			thisIter = thisIter->next;
		}
		thisIter->next = nullptr;
		tail = thisIter;
	}
}
template <typename T>
void LinkedQueue<T>::Free()
{
	Node* iter = head;
	while (iter != nullptr)
	{
		Node* toRemove = iter;
		iter = iter->next;
		delete toRemove;
	}
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
	return head == nullptr && tail == nullptr;
}

template <typename T>
LinkedQueue<T>::LinkedQueue() : head(nullptr), tail(nullptr) {}
template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other)
{
	CopyFrom(other);
}
template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator= (const LinkedQueue<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
	Free();
}

template <typename T>
void LinkedQueue<T>::enqueue(T element)
{
	Node* newNode = new Node(element);
	if (isEmpty())
		head = tail = newNode;
	else
	{
		tail->next = newNode;
		tail = newNode;
	}
}
template <typename T>
T LinkedQueue<T>::dequeue()
{
	if (isEmpty())
		throw "Empty linked queue! Nothing to dequeue!";

	T dataToRemove = head->data;
	if (head->next == nullptr)
	{
		delete head;
		head = tail = nullptr;
	}
	else
	{
		Node* toRemove = head;
		head = head->next;
		delete toRemove;
	}

	return dataToRemove;
}
template <typename T>
void LinkedQueue<T>::print() const
{
	Node* iter = head;
	while (iter != nullptr)
	{
		cout << iter->data;
		if (iter->next != nullptr)
			cout << "->";
		iter = iter->next;
	}
	cout << endl;
}