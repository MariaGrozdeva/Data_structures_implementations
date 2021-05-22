#include <queue>
#include <stack>
#include <functional>

#include "AdjacencyListGraph.h"

void BFS(const Graph& g, int start);
void DFS(const Graph& g, int start);
void DFSrec(const Graph& g, int start);

bool containsPath(const Graph& g, int start, int end);
bool connected(const Graph& g);
bool isBipartite(const Graph& g);
bool isCyclic(const Graph& g);

void topologicalSorting(const Graph& g, vector<int>& topoSort, bool calledBySCC = false); // Tarjan's algorithm
void SCC(const AdjacencyListGraph& g); // Kosaraju's algorithm for finding all strongly connected components

int Dijkstra(const Graph& g, int start, int end, vector<int>& path);

int Prim(const Graph& g, Graph& mst);