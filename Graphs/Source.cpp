#include "AdjacencyListGraph.h"
#include "AdjacencyMatrixGraph.h"
#include "EdgeListGraph.h"
#include "Algorithms.hpp"

int main()
{
	AdjacencyListGraph g(6, false);

	g.addEdge(0, 1, 0);
	g.addEdge(0, 2, 0);
	g.addEdge(0, 3, 0);
	g.addEdge(1, 4, 0);
	g.addEdge(2, 3, 0);
	g.addEdge(3, 1, 0);
	g.addEdge(3, 3, 0);
	g.addEdge(3, 5, 0);
	g.addEdge(4, 3, 0);

	cout << BFS_containsPath(g, 0, 5);
}