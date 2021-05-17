#include <queue>
#include <stack>
#include <functional>

#include "Graph.h"

void BFS(const Graph& g, int start);
void DFS(const Graph& g, int start);

bool BFS_containsPath(const Graph& g, int start, int end);
bool containsPath(const Graph& g, int start, int end);

bool BFS_connected(const Graph& g);
bool connected(const Graph& g);

bool DFS_containsCycle(const Graph& g, vector<bool>& visited, vector<bool>& stack, int currentVertex);
bool isCyclic(const Graph& g);

// Tarjan's algorithm
void DFSrec_topologicalSorting(const Graph& g, vector<bool>& visited, stack<int>& currentRes, int currentVertex);
void topologicalSorting(const Graph& g, vector<int>& topoSort);

int Dijkstra(const Graph& g, int start, int end, vector<int>& path);

int Prim(const Graph& g, Graph& mst);