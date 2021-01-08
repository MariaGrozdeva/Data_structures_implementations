#include "Graph.h"

class EdgeListGraph : public Graph
{
private:
	struct Edge
	{
		int start;
		int end;
		int weight;
	};

	list<Edge> edgeList; // space complexity: O(m)

public:
	EdgeListGraph(int numOfVertices, bool oriented = true);

	int addVertex(); // O(1)
	void removeVertex(int vertex); // O(m)

	void addEdge(int start, int end, int weight); // O(1)
	void removeEdge(int start, int end); // O(m)

	vector<pair<int, int>> getSuccessors(int vertex) const; // O(m)
	vector<pair<int, int>> getPredecessors(int vertex) const; // O(m)

	bool adjacent(int vertex1, int vertex2) const; // O(m)
};