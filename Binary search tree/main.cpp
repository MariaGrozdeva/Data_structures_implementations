#include "BinarySearchTree.hpp"

int main()
{
	BinarySearchTree<int> bst;
	bst.insert(1);
	bst.insert(3);
	bst.insert(5);
	bst.print();
	cout << endl;

	bst.remove(1);
	bst.print();
	cout << endl;

	vector<int> v{ 1,3,5,7,9 };

	BinarySearchTree<int> bst2(v);
	bst2.print();
}