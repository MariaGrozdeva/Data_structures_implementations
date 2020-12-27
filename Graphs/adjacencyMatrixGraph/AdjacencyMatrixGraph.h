#pragma once
#include "Graph.h"

class AdjacencyMatrixGraph : public Graph
{
private:
	vector<vector<int>> adjMatrix; // space complexity: O(n^2)

public:
	AdjacencyMatrixGraph(int numOfVertices, bool oriented = true);

	int addVertex(); // O(n)
	void removeVertex(int vertex); // O(n^2)

	void addEdge(int start, int end, int weight); // O(1)
	void removeEdge(int start, int end); // O(1)

	vector<pair<int, int>> getSuccessors(int vertex) const; // O(n)
	vector<pair<int, int>> getPredecessors(int vertex) const; // O(n)

	bool adjacent(int vertex1, int vertex2) const; // O(1)
};