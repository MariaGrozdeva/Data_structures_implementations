#pragma once
#include "Graph.h"

class AdjacencyListGraph : public Graph
{
private:
	struct Edge
	{
		int end;
		int weight;
	};

	vector<list<Edge>> adjList; // space complexity: O(n + m)

public:
	AdjacencyListGraph(int numOfVertices, bool oriented = true);

	int addVertex(); // O(1)
	void removeVertex(int vertex); // O(n+m)

	void addEdge(int start, int end, int weight); // O(1)
	void removeEdge(int start, int end); // O(m)

	vector<pair<int, int>> getSuccessors(int vertex) const; // O(m)
	vector<pair<int, int>> getPredecessors(int vertex) const; // O(n + m)

	bool adjacent(int vertex1, int vertex2) const; // O(n)

	AdjacencyListGraph getTransposedGraph() const; // O(n + m)
};
