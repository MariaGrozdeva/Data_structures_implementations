#include <iostream>
using namespace std;

template <typename T>
class LinkedStack
{
	struct Node
	{
		T data;
		Node* next;

		Node(T data) : data(data), next(nullptr) {}
	};

	Node* head;

	void CopyFrom(const LinkedStack<T>& other);
	void Free();

	bool isEmpty() const;

public:
	LinkedStack();

	LinkedStack(const LinkedStack<T>& other);
	LinkedStack<T>& operator=(const LinkedStack<T>& other);
	~LinkedStack();

	void push(T element); // O(1)
	void pop(); // O(1)
	T top(); // O(1)
	void print() const;
};

template <typename T>
void LinkedStack<T>::CopyFrom(const LinkedStack<T>& other)
{
	if (other.isEmpty())
		head = nullptr;

	else
	{
		Node* otherIter = other.head;
		head = new Node(other.head->data);

		Node* thisIter = head;

		while (otherIter->next != nullptr)
		{
			thisIter->next = new Node(otherIter->next->data);

			thisIter = thisIter->next;
			otherIter = otherIter->next;
		}

		thisIter->next = nullptr;
	}
}
template <typename T>
void LinkedStack<T>::Free()
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
bool LinkedStack<T>::isEmpty() const
{
	return head == nullptr;
}

template <typename T>
LinkedStack<T>::LinkedStack() : head(nullptr) {}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other)
{
	CopyFrom(other);
}
template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
template <typename T>
LinkedStack<T>::~LinkedStack()
{
	Free();
}

template <typename T>
void LinkedStack<T>::push(T element)
{
	Node* newNode = new Node(element);

	if (isEmpty())
		head = newNode;
	else
	{
		newNode->next = head;
		head = newNode;
	}

}
template <typename T>
void LinkedStack<T>::pop()
{
	if (isEmpty())
		throw "Empty linked stack! Nothing to pop!";

	else if (head->next == nullptr)
	{
		delete head;
		head = nullptr;
	}
	else
	{
		Node* toRemove = head;
		head = head->next;

		delete toRemove;
	}
}
template <typename T>
T LinkedStack<T>::top()
{
	if (isEmpty())
		throw "Empty linked stack! No top!";
	return head->data;
}
template <typename T>
void LinkedStack<T>::print() const
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