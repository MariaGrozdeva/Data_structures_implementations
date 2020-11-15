#include "SinglyLinkedList.hpp"

template <typename T>
class QueueSLL : private SinglyLinkedList<T>
{
public:
	void enqueue(const T& el);
	T dequeue();
	T peek();

	void printQueue() const;
};

template <typename T>
void QueueSLL<T>::enqueue(const T& el)
{
	this->pushBack(el);
}

template <typename T>
T QueueSLL<T>::dequeue()
{
	return this->popFront();
}

template <typename T>
T QueueSLL<T>::peek()
{
	return this->getAt(this->count - 1);
}

template <typename T>
void QueueSLL<T>::printQueue() const
{
	this->print();
}