#include "PriorityQueueMaxBinaryHeap.hpp"

void heapSort(vector<int>& v) // O(nlog(n))
{
	PriorityQueue<int> q(v); 

	for (int i = v.size() - 1; i >= 0; i--) // O(n)
	{
		v[i] = q.pullHighestPriorityElement(); // O(log(n))
	}
}

int main()
{
	vector<int> v{ 2,7,3,1,17,36,25,100,19 };
	PriorityQueue<int> q(v);

	cout << q.pullHighestPriorityElement() << endl;
	cout << q.pullHighestPriorityElement() << endl;
	cout << q.pullHighestPriorityElement() << endl;
	q.print();
}