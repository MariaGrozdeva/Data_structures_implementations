#include "Iterator.hpp"

template<typename T>
bool Search(Iterator<T>& begin, Iterator<T>& end, T el)
{
	// auto-> Vector<T>::VectorIterator
	// auto-> DoublyLinkedList<T>::DoublyLinkedListIterator
	for (auto& it = begin; it != end; it++)
	{
		if (*it == el)
			return true;
	}
	return false;
}