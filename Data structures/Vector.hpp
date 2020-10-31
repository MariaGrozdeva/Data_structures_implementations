#include "List.h"

template <typename T>
class Vector : public List<T>
{
	T* data;
	
	int count;
	int capacity;

	void CopyFrom(const Vector<T>& other);
	void Free();

	void Resize(int newCapacity);

public:
	Vector(int capacity);

	Vector();
	Vector(const Vector<T>& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

	void pushBack(const T& el); // O(n) -> но O(1) амортизирано (константно амортизирано)
	void pushFront(const T& el); // O(n)
	void insertAt(const T& el, int index); // O(n)

	T getAt(int index); // O(1)

	T popBack(); // O(n) -> но O(1) амортизирано (константно амортизирано)
	T popFront(); // O(n)
	T removeAt(int index); // O(n)

	const T& operator[](size_t index) const;
	T& operator[](size_t index);

	size_t getSize() const;

	void print() const;
};

int closestPowerOfTwo(int n)
{
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	
	return n + 1;
}

template <typename T>
void Vector<T>::CopyFrom(const Vector<T>& other)
{
	this->count = other.count;
	this->capacity = other.capacity;

	this->data = new T[capacity];
	for (int i = 0; i < count; i++)
		this->data[i] = other.data[i];
}
template <typename T>
void Vector<T>::Free()
{
	delete[] data;
}

template <typename T>
void Vector<T>::Resize(int newCapacity)
{
	this->capacity = newCapacity;

	T* temp = new T[capacity];
	for (int i = 0; i < count; i++)
		temp[i] = data[i];

	Free();
	data = temp;		
}

template <typename T>
Vector<T>::Vector(int capacity)
{
	count = 0;
	this->capacity = closestPowerOfTwo(capacity);

	data = new T[capacity];
}

template <typename T>
Vector<T>::Vector() : Vector(4)
{}
template <typename T>
Vector<T>::Vector(const Vector<T>& other)
{
	CopyFrom(other);
}
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
template <typename T>
Vector<T>::~Vector()
{
	Free();
}

template <typename T>
void Vector<T>::pushBack(const T& el)
{
	if (count == capacity)
		Resize(capacity * 2);

	data[count++] = el;
}
template <typename T>
void Vector<T>::pushFront(const T& el)
{
	if (count == capacity)
		Resize(capacity * 2);

	for (int i = count; i > 0; i--)
		data[i] = data[i - 1];

	data[0] = el;
	count++;
}
template <typename T>
void Vector<T>::insertAt(const T& el, int index)
{
	if (index < 0 || index > count)
		throw "Error! Invalid index!";

	if (count == capacity)
		Resize(capacity * 2);

	for (int i = count; i > index; i--)
		data[i] = data[i - 1];

	data[index] = el;
	count++;
}

template <typename T>
T Vector<T>::getAt(int index)
{
	if (index < 0 || index >= count)
		throw "Error! Invalid index!";

	return data[index];
}

template <typename T>
T Vector<T>::popBack()
{
	if (count == 0)
		throw "Empty vector!";

	T elementToRemove = data[--count];

	if (count < capacity / 2)
		Resize(capacity / 2);

	return elementToRemove;
}
template <typename T>
T Vector<T>::popFront()
{
	if (count == 0)
		throw "Empty vector!";

	T elementToRemove = data[0];

	for (int i = 1; i < count; i++)
		data[i - 1] = data[i];

	if (--count < capacity / 2)
		Resize(capacity / 2);

	return elementToRemove;
}
template <typename T>
T Vector<T>::removeAt(int index)
{
	if (index < 0 || index >= count)
		throw "Error! Invalid index!";

	T elementToRemove = data[index];

	for (int i = index; i < count - 1; i++)
		data[i] = data[i + 1];

	if (--count < capacity / 2)
		Resize(capacity / 2);

	return elementToRemove;
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const
{
	if (index >= count)
		throw "Error! Invalid index!";
	return data[index];
}
template <typename T>
T& Vector<T>::operator[](size_t index)
{
	if (index >= count)
		throw "Error! Invalid index!";
	return data[index];
}

template <typename T>
size_t Vector<T>::getSize() const
{
	return count;
}

template <typename T>
void Vector<T>::print() const
{
	for (int i = 0; i < count; i++)
		cout << data[i] << " ";
	for (int i = count; i < capacity; i++)
		cout << "_ ";
	cout << endl;
}