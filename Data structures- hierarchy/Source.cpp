#include "SinglyLinkedList.hpp"
#include "DoublyLinkedList.hpp"

void testFunction(List<int>* l)
{
	l->pushBack(1);
	l->pushBack(2);
	l->pushBack(3);
	l->pushBack(4);
	l->pushBack(5);

	l->print();
}

int main()
{
	SinglyLinkedList<int> sl;
	testFunction(&sl);
	sl.popFront();
	sl.popBack();
	sl.print();

	DoublyLinkedList<int> dl;
	testFunction(&dl);
	dl.insertAt(0, 0);
	dl.removeAt(5);
	dl.print();
}