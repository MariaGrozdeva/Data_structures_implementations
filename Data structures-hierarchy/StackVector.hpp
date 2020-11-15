#include "Vector.hpp"

template <typename T>
class StackVector : private Vector<T>
{
public:
	void push(const T& el);
	T pop();
	T peek();

	void printStack() const;
};

template <typename T>
void StackVector<T>::push(const T& el)
{
	this->pushBack(el);
}

template <typename T>
T StackVector<T>::pop()
{
	return this->popBack();
}

template <typename T>
T StackVector<T>::peek()
{
	return this->getAt(this->count - 1);
}

template <typename T>
void StackVector<T>::printStack() const
{
	this->print();
}