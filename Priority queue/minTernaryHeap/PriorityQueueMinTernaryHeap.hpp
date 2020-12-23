#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class PriorityQueue
{
	vector<T> data;

	int leftChild(int index);
	int middleChild(int index);
	int rightChild(int index);
	int parent(int index);

	void swapElWithChildOrParent(int& toBeShiftedIndex, int& childOrParentIndex);
	void heapify(int index);

public:
	PriorityQueue() = default;
	PriorityQueue(const vector<T>& v); // O(n)

	void insertWithPriority(T el); // O(log(n))
	T pullHighestPriorityElement(); // O(log(n))

	bool isEmpty(); // O(1)

	void print_rec(int elIndex, int space);
	void print();
};

template <typename T>
PriorityQueue<T>::PriorityQueue(const vector<T>& v)
{
	data = v;

	for (int i = data.size() / 3 - 1; i >= 0; i--)
		heapify(i);
}

template <typename T>
int PriorityQueue<T>::leftChild(int index)
{
	return 3 * index + 1;
}
template <typename T>
int PriorityQueue<T>::middleChild(int index)
{
	return 3 * index + 2;
}
template <typename T>
int PriorityQueue<T>::rightChild(int index)
{
	return 3 * index + 3;
}
template <typename T>
int PriorityQueue<T>::parent(int index)
{
	return (index - 1) / 3;
}

template <typename T>
void PriorityQueue<T>::swapElWithChildOrParent(int& toBeShiftedIndex, int& childOrParentIndex)
{
	swap(data[toBeShiftedIndex], data[childOrParentIndex]);
	toBeShiftedIndex = childOrParentIndex;
}
template <typename T>
void PriorityQueue<T>::heapify(int index)
{
	int toBeShiftedDownIndex = index;

	while (true)
	{
		T toBeShiftedDown = data[toBeShiftedDownIndex];

		int leftChildIndex = leftChild(toBeShiftedDownIndex);
		int middleChildIndex = middleChild(toBeShiftedDownIndex);
		int rightChildIndex = rightChild(toBeShiftedDownIndex);

		bool shouldGoLeft = (leftChildIndex < data.size()) && (toBeShiftedDown > data[leftChildIndex]);
		bool shouldGoMiddle = (middleChildIndex < data.size()) && (toBeShiftedDown > data[middleChildIndex]);
		bool shouldGoRight = (rightChildIndex < data.size()) && (toBeShiftedDown > data[rightChildIndex]);

		if (shouldGoLeft && shouldGoMiddle && shouldGoRight)
		{
			T minData = min(data[leftChildIndex], min(data[middleChildIndex], data[rightChildIndex]));
			int& minDataIndex =
				minData == data[leftChildIndex] ?
				leftChildIndex :
				minData == data[middleChildIndex] ?
				middleChildIndex : rightChildIndex;

			swapElWithChildOrParent(toBeShiftedDownIndex, minDataIndex);
		}

		else if (shouldGoLeft && shouldGoMiddle)
		{
			T minData = min(data[leftChildIndex], data[middleChildIndex]);
			int& minDataIndex = minData == data[leftChildIndex] ? leftChildIndex : middleChildIndex;
			swapElWithChildOrParent(toBeShiftedDownIndex, minDataIndex);
		}
		else if (shouldGoMiddle && shouldGoRight)
		{
			T minData = min(data[middleChildIndex], data[rightChildIndex]);
			int& minDataIndex = minData == data[middleChildIndex] ? middleChildIndex : rightChildIndex;
			swapElWithChildOrParent(toBeShiftedDownIndex, minDataIndex);
		}
		else if (shouldGoLeft && shouldGoRight)
		{
			T minData = min(data[leftChildIndex], data[rightChildIndex]);
			int& minDataIndex = minData == data[leftChildIndex] ? leftChildIndex : rightChildIndex;
			swapElWithChildOrParent(toBeShiftedDownIndex, minDataIndex);
		}

		else if (shouldGoLeft || shouldGoMiddle || shouldGoRight)
		{
			if (shouldGoLeft)
				swapElWithChildOrParent(toBeShiftedDownIndex, leftChildIndex);
			else if (shouldGoMiddle)
				swapElWithChildOrParent(toBeShiftedDownIndex, middleChildIndex);
			else
				swapElWithChildOrParent(toBeShiftedDownIndex, rightChildIndex);
		}

		else
			break;
	}
}

template <typename T>
void PriorityQueue<T>::insertWithPriority(T el)
{
	data.push_back(el);

	int toBeShiftedUpIndex = data.size() - 1;
	int parentIndex = parent(toBeShiftedUpIndex);

	while (toBeShiftedUpIndex && (data[parentIndex] > data[toBeShiftedUpIndex]))
	{
		swapElWithChildOrParent(toBeShiftedUpIndex, parentIndex);
		parentIndex = parent(toBeShiftedUpIndex);
	}
}
template <typename T>
T PriorityQueue<T>::pullHighestPriorityElement()
{
	if (isEmpty())
		throw "Empty priority queue!";

	T elToReturn = data[0];
	if (data.size() == 1)
	{
		data.pop_back();
		return elToReturn;
	}

	swap(data[0], data[data.size() - 1]);

	data.pop_back();
	heapify(0);

	return elToReturn;
}

template <typename T>
bool PriorityQueue<T>::isEmpty()
{
	return data.size() == 0;
}

template <typename T>
void PriorityQueue<T>::print_rec(int elIndex, int space)
{
	const int SPACES_COUNT = 10;
	if (elIndex >= data.size())
		return;
	space += SPACES_COUNT;

	print_rec(rightChild(elIndex), space);
	cout << endl;

	print_rec(middleChild(elIndex), space);
	for (int i = SPACES_COUNT; i < space; i++)
		cout << " ";
	cout << data[elIndex] << endl;

	print_rec(leftChild(elIndex), space);
}
template <typename T>
void PriorityQueue<T>::print()
{
	print_rec(0, 0);
}