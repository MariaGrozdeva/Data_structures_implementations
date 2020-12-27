#include "AdjacencyListGraph.h"

AdjacencyListGraph::AdjacencyListGraph(int numOfVertices, bool oriented) :
	Graph(numOfVertices, oriented), adjList(numOfVertices) {}

int AdjacencyListGraph::addVertex()
{
	adjList.push_back(list<Edge>());
	numOfVertices++;

	return numOfVertices - 1;
}
void AdjacencyListGraph::removeVertex(int vertex)
{
	adjList.erase(adjList.begin() + vertex);
	numOfVertices--;

	for (int i = 0; i < numOfVertices; i++)
	{
		for (auto it = adjList[i].begin(); it != adjList[i].end();)
		{
			if (it->end == vertex)
				it = adjList[i].erase(it);
			else
			{
				if (it->end > vertex)
					it->end--;
				it++;
			}
		}
	}
}

void AdjacencyListGraph::addEdge(int start, int end, int weight)
{
	if (!existVertex(start))
		throw "Invalid vertex!";

	adjList[start].push_back({ end, weight });
	if (!oriented)
		adjList[end].push_back({ start, weight });
}
void AdjacencyListGraph::removeEdge(int start, int end)
{
	if (!existVertex(start) || !existVertex(end))
		throw "Invalid vertices!";

	for (auto it = adjList[start].begin(); it != adjList[start].end();)
	{
		if (it->end == end)
			it = adjList[start].erase(it);
		else
			it++;
	}

	if (oriented)
		return;

	for (auto it = adjList[end].begin(); it != adjList[end].end();)
	{
		if (it->end == start)
			it = adjList[end].erase(it);
		else
			it++;
	}
}

vector<pair<int, int>> AdjacencyListGraph::getSuccessors(int vertex) const
{
	vector<pair<int, int>> successors;

	for (auto it = adjList[vertex].begin(); it != adjList[vertex].end(); it++)
		successors.push_back(make_pair(it->end, it->weight));

	return successors;
}
vector<pair<int, int>> AdjacencyListGraph::getPredecessors(int vertex) const
{
	vector<pair<int, int>> predecessors;

	for (int i = 0; i < numOfVertices; i++)
	{
		for (auto it = adjList[i].begin(); it != adjList[i].end(); it++)
		{
			if (it->end == vertex)
				predecessors.push_back(make_pair(i, it->weight));
		}
	}
	return predecessors;
}

bool AdjacencyListGraph::adjacent(int vertex1, int vertex2) const
{
	for (auto it = adjList[vertex1].begin(); it != adjList[vertex1].end(); it++)
	{
		if (it->end == vertex2)
			return true;
	}
	return false;
}