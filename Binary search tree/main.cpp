#include "BinarySearchTree.hpp"

int main()
{
	BinarySearchTree<int> bst;
	bst.insert(1);
	bst.insert(5);
	bst.insert(3);

	bst.print();
	cout << endl;

	vector<int> vc{ 1,3,5,7,9 };
	BinarySearchTree<int>(vc);
	bst.print();
}