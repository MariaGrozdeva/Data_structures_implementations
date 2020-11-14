#include "SinglyLinkedList.hpp"

template <typename T>
class StackSLL : private SinglyLinkedList<T>
{
public:
	void push(const T& el);
	T pop();
	T peek();

	void printStack() const;
};

template <typename T>
void StackSLL<T>::push(const T& el)
{
	this->pushFront(el);
}

template <typename T>
T StackSLL<T>::pop()
{
	return this->popFront();
}

template <typename T>
T StackSLL<T>::peek()
{
	return this->getAt(this->count - 1);
}

template <typename T>
void StackSLL<T>::printStack() const
{
	this->print();
}