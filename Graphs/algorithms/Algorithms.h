<<<<<<< HEAD
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

int Dijkstra(const Graph& g, int start, int end, vector<int>& path);

int Prim(const Graph& g, Graph& mst);
=======
#include <queue>
#include <stack>
#include "Graph.h"

void BFS(const Graph& g, int start);
void DFS(const Graph& g, int start);

bool BFS_containsPath(const Graph& g, int start, int end);
bool containsPath(const Graph& g, int start, int end);

bool BFS_connected(const Graph& g);
bool connected(const Graph& g);

int Dijkstra(const Graph& g, int start, int end, vector<int>& path);
>>>>>>> 53aed6a93650d8aa658aa387583e956af5645eb6
