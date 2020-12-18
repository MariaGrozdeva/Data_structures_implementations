#include <iostream>
#include <vector>
#include <algorithm> 

using namespace std;

template <typename T>
class BinarySearchTree
{
	struct Node
	{
		T data;
		Node* left;
		Node* right;

		Node(T data) : data(data), left(nullptr), right(nullptr) {}
	};

	Node* root;

	void CopyFrom_rec(const Node* otherNode, Node*& root);
	void Free_rec(Node* root);

	void print_rec(Node* root) const;

	bool contains_rec(T el, Node* currentNode, Node*& prevNode);
	bool remove_rec(T el, Node*& currentNode);

	void createBST_rec(const vector<T> v, int startIndex, int endIndex, Node*& root);

	void CopyFrom(const BinarySearchTree& other);
	void Free();

	void findMin(Node* root, Node*& minNode);

public:
	BinarySearchTree(const vector<T> v);

	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree& other);
	BinarySearchTree<T>& operator= (const BinarySearchTree& other);
	~BinarySearchTree();

	bool contains(T el);
	bool insert(T el);
	bool remove(T el);

	void print() const;
};

template <typename T>
void BinarySearchTree<T>::CopyFrom_rec(const Node* otherNode, Node*& root)
{
	if (!otherNode)
		return;

	root = new Node(otherNode->data);

	CopyFrom_rec(otherNode->left, root->left);
	CopyFrom_rec(otherNode->right, root->right);
}
template <typename T>
void BinarySearchTree<T>::CopyFrom(const BinarySearchTree& other)
{
	CopyFrom_rec(other.root, root);
}

template <typename T>
void BinarySearchTree<T>::Free_rec(Node* root)
{
	if (!root)
		return;

	Free_rec(root->left);
	Free_rec(root->right);

	delete root;
}
template <typename T>
void BinarySearchTree<T>::Free()
{
	Free_rec(root);
}

template <typename T>
void BinarySearchTree<T>::createBST_rec(const vector<T> v, int startIndex, int endIndex, Node*& root)
{
	if (startIndex > endIndex)
		return;

	int posOfTempData = (startIndex + endIndex) / 2;
	T tempData = v[posOfTempData];

	root = new Node(tempData);
	createBST_rec(v, startIndex, posOfTempData - 1, root->left);
	createBST_rec(v, posOfTempData + 1, endIndex, root->right);
}
template <typename T>
BinarySearchTree<T>::BinarySearchTree(const vector<T> v)
{
	if (!is_sorted(v.begin(), v.end()))
		throw "Array should be sorted!";

	createBST_rec(v, 0, v.size() - 1, root);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree() : root(nullptr) {}
template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree& other) : root(nullptr)
{
	CopyFrom(other);
}
template <typename T>
BinarySearchTree<T>& BinarySearchTree<T>::operator= (const BinarySearchTree& other)
{
	if (this != &other)
	{
		Free();
		CopyFrom(other);
	}
	return *this;
}
template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	Free();
}

template <typename T>
bool BinarySearchTree<T>::contains_rec(T el, Node* currentNode, Node*& prevNode)
{	
	if (!currentNode)
		return false;
	if (currentNode->data == el)
		return true;

	prevNode = currentNode;

	if (el < currentNode->data)
		return contains_rec(el, currentNode->left, prevNode);
	return contains_rec(el, currentNode->right, prevNode);
}
template <typename T>
bool BinarySearchTree<T>::contains(T el)
{
	Node* temp = nullptr;
	return contains_rec(el, root, temp);
}

template <typename T>
bool BinarySearchTree<T>::insert(T el)
{
	if (!root)
	{
		root = new Node(el);
		return true;
	}

	Node* prev = nullptr;
	bool found = contains_rec(el, root, prev);

	if (found)
		return false;

	if (el < prev->data)
		prev->left = new Node(el);
	else
		prev->right = new Node(el);


	return true;
}

template <typename T>
void BinarySearchTree<T>::findMin(Node* root, Node*& minNode)
{
	Node* iter = root;

	while (iter != nullptr)
	{
		minNode = iter;
		iter = iter->left;
	}
}
template <typename T>
bool BinarySearchTree<T>::remove_rec(T el, Node*& currentNode)
{
	Node* prev = nullptr;
	bool found = contains_rec(el, currentNode, prev);

	if (!found)
		return false;

	Node*& toDelete = !prev ? currentNode : el < prev->data ? prev->left : prev->right;

	if (!toDelete->left && !toDelete->right)
	{
		delete toDelete;
		toDelete = nullptr;
	}

	else if (!toDelete->left || !toDelete->right)
	{
		Node* newChildOfPrev = toDelete->left ? toDelete->left : toDelete->right;
		delete toDelete;
		toDelete = newChildOfPrev;
	}

	else
	{
		Node* minNode;
		findMin(toDelete->right, minNode);

		swap(minNode->data, toDelete->data);

		return remove_rec(el, toDelete->right);
	}

	return true;
}
template <typename T>
bool BinarySearchTree<T>::remove(T el)
{
	return remove_rec(el, root);
}

template <typename T>
void BinarySearchTree<T>::print_rec(Node* root) const
{
	if (!root)
		return;

	print_rec(root->left);
	cout << root->data << " ";
	print_rec(root->right);
}
template <typename T>
void BinarySearchTree<T>::print() const
{
	print_rec(root);
}