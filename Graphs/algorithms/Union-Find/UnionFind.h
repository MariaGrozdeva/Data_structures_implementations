#include <iostream>
#include <vector>

using namespace std;

class UnionFind
{
private:
	vector<int> parents;
	vector<int> sizes;

public:
	UnionFind(int n); // set of n elements (0..n-1)

	bool Union(int n, int k); // O(log(n))
	int Find(int n); // O(log(n))
};