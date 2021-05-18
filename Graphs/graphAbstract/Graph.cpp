#include "Graph.h"

int Graph::getNumOfVertices() const
{
	return numOfVertices;
}
bool Graph::isOriented() const
{
	return oriented;
}
bool Graph::existVertex(int vertex) const
{
	return vertex < numOfVertices;
}

vector<pair<int, int>> Graph::getNeighbors(int vertex) const
{
	if (oriented)
		throw "Oriented graph! Use getSuccessors() or getPredecessors()!";

	vector<pair<int, int>> neighbors = getSuccessors(vertex);
	vector<pair<int, int>> toBeInserted = getPredecessors(vertex);

	neighbors.insert(neighbors.end(), toBeInserted.begin(), toBeInserted.end());

	return neighbors;
}
