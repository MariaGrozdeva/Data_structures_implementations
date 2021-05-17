#include <queue>
#include <stack>
#include <functional>

#include "Graph.h"

void BFS(const Graph& g, int start);
void DFS(const Graph& g, int start);

bool containsPath(const Graph& g, int start, int end);
bool connected(const Graph& g);
bool isCyclic(const Graph& g);

void topologicalSorting(const Graph& g, vector<int>& topoSort); // Tarjan's algorithm

int Dijkstra(const Graph& g, int start, int end, vector<int>& path);

int Prim(const Graph& g, Graph& mst);