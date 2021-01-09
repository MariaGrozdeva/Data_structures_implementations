#include "AdjacencyMatrixGraph.h"

AdjacencyMatrixGraph::AdjacencyMatrixGraph(int numOfVertices, bool oriented) : Graph(numOfVertices, oriented), adjMatrix(numOfVertices)
{
	vector<int> templateVector(numOfVertices);

	for (int i = 0; i < numOfVertices; i++)
		adjMatrix[i] = templateVector;
}

int AdjacencyMatrixGraph::addVertex()
{
	adjMatrix.push_back(vector<int>(numOfVertices + 1));
	numOfVertices++;

	for (int i = 0; i < numOfVertices - 1; i++)
		adjMatrix[i].push_back(0);

	return numOfVertices - 1;
}
void AdjacencyMatrixGraph::removeVertex(int vertex)
{
	if (!existVertex(vertex))
		throw "Invalid vertex!";

	adjMatrix.erase(adjMatrix.begin() + vertex);

	numOfVertices--;

	for (int i = 0; i < numOfVertices; i++)
		adjMatrix[i].erase(adjMatrix[i].begin() + vertex);
}

void AdjacencyMatrixGraph::addEdge(int start, int end, int weight)
{
	if (!existVertex(start) || !existVertex(end))
		throw "Invalid vertices!";

	adjMatrix[start][end] = weight;
	if (!oriented)
		adjMatrix[end][start] = weight;
}
void AdjacencyMatrixGraph::removeEdge(int start, int end)
{
	if (!existVertex(start) || !existVertex(end))
		throw "Invalid vertices!";

	adjMatrix[start][end] = 0;
	if (!oriented)
		adjMatrix[end][start] = 0;
}

vector<pair<int, int>> AdjacencyMatrixGraph::getSuccessors(int vertex) const
{
	if (!existVertex(vertex))
		throw "Invalid vertex!";

	vector<pair<int, int>> successors;

	for (int i = 0; i < numOfVertices; i++)
	{
		if (adjMatrix[vertex][i] > 0)
			successors.push_back(make_pair(i, adjMatrix[vertex][i]));
	}
	return successors;
}
vector<pair<int, int>> AdjacencyMatrixGraph::getPredecessors(int vertex) const
{
	if (!existVertex(vertex))
		throw "Invalid vertex!";

	vector<pair<int, int>> predecessors;

	for (int i = 0; i < numOfVertices; i++)
	{
		if (adjMatrix[i][vertex] > 0)
			predecessors.push_back(make_pair(i, adjMatrix[i][vertex]));
	}
	return predecessors;
}

bool AdjacencyMatrixGraph::adjacent(int vertex1, int vertex2) const
{
	return adjMatrix[vertex1][vertex2] > 0;
}