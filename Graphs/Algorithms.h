#include <queue>
#include <stack>
#include "C:\Users\Maria\source\repos\Data structures\Graphs\graphAbstract\Graph.h"

void BFS(const Graph& g, int start);
void DFS(const Graph& g, int start);

bool BFS_containsPath(const Graph& g, int start, int end);
bool containsPath(const Graph& g, int start, int end);

bool BFS_connected(const Graph& g);
bool connected(const Graph& g);

int Dijkstra(const Graph& g, int start, int end, vector<int>& path);