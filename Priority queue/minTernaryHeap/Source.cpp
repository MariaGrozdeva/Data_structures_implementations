#include "PriorityQueueMinTernaryHeap.hpp"

void heapSort(vector<int>& v) // O(nlog(n))
{
	PriorityQueue<int> q(v);

	for (int i = 0; i < v.size(); i++) // O(n)
		v[i] = q.pullHighestPriorityElement(); // O(nlog(n))
}

int main()
{
	vector<int> v{ 8,6,5,30,99,12,70,7,10,3,6,10,9,4,10 };
	PriorityQueue<int> q(v);

	cout << q.pullHighestPriorityElement() << endl;
	cout << q.pullHighestPriorityElement() << endl;
	cout << q.pullHighestPriorityElement() << endl;
	cout << q.pullHighestPriorityElement() << endl;
	cout << q.pullHighestPriorityElement() << endl;
	q.print();
}