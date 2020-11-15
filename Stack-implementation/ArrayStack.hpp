#include <iostream>
using namespace std;

template <typename T>
class ArrayStack
{
	T* data;
	size_t size;
	size_t capacity;

	void CopyFrom(const ArrayStack& other);
	void Free();

	void Resize(size_t newCapacity);

	bool isEmpty() const;

public:
	ArrayStack();

	ArrayStack(size_t capacity);
	ArrayStack(const ArrayStack<T>& other);
	ArrayStack<T>& operator=(const ArrayStack<T>& other);
	~ArrayStack();

	void push(T element); // O(1)
	void pop(); // O(1)
	T top(); // O(1)
	void print() const;
};

size_t closestPowerOfTwo(size_t number)
{
	number--;

	number |= number >> 1;
	number |= number >> 2;
	number |= number >> 4;
	number |= number >> 8;
	number |= number >> 16;

	return number + 1;
}

template <typename T>
void ArrayStack<T>::CopyFrom(const ArrayStack& other)
{
	if (other.isEmpty())
		return;

	size = other.size;
	capacity = other.capacity;

	data = new T[capacity];
	for (int i = 0; i < size; i++)
		data[i] = other.data[i];
}
template <typename T>
void ArrayStack<T>::Free()
{
	delete data;
}

template <typename T>
void ArrayStack<T>::Resize(size_t newCapacity)
{
	capacity = newCapacity;
	T* temp = new T[capacity];

	for (int i = 0; i < size; i++)
		temp[i] = data[i];

	Free();
	data = temp;
}

template <typename T>
bool ArrayStack<T>::isEmpty() const
{
	return size == 0;
}

template <typename T>
ArrayStack<T>::ArrayStack() : ArrayStack(4) {}

template <typename T>
ArrayStack<T>::ArrayStack(size_t capacity)
{
	this->capacity = closestPowerOfTwo(capacity);
	size = 0;

	data = new T[this->capacity];
}
template <typename T>
ArrayStack<T>::ArrayStack(const ArrayStack<T>& other)
{
	CopyFrom(other);
}
template <typename T>
ArrayStack<T>& ArrayStack<T>::operator=(const ArrayStack<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
template <typename T>
ArrayStack<T>::~ArrayStack()
{
	Free();
}

template <typename T>
void ArrayStack<T>::push(T element)
{
	if (size == capacity)
		Resize(capacity * 2);

	data[size++] = element;
}
template <typename T>
void ArrayStack<T>::pop()
{
	if (size == 0)
		throw "Empty array stack! Nothing to pop!";

	if (--size < capacity / 2)
		Resize(capacity / 2);
}
template <typename T>
T ArrayStack<T>::top()
{
	if (size == 0)
		throw "Empty linked stack! No top!";

	return data[size - 1];
}
template <typename T>
void ArrayStack<T>::print() const
{
	for (int i = 0; i < size; i++)
		cout << data[i] << ' ';
	cout << endl;
}