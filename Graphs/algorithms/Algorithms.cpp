#include "Algorithms.h"

void BFS(const Graph& g, int start)
{
	if (!g.existVertex(start))
		return;

	queue<int> q;
	vector<bool> visited(g.getNumOfVertices());

	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		cout << current << endl;

		vector<pair<int, int>> adjacent = g.getSuccessors(current);

		for (size_t i = 0; i < adjacent.size(); i++)
		{
			if (visited[adjacent[i].first])
				continue;

			q.push(adjacent[i].first);
			visited[adjacent[i].first] = true;
		}
	}
}

void DFS(const Graph& g, int start)
{
	if (!g.existVertex(start))
		return;

	stack<int> s;
	vector<bool> visited(g.getNumOfVertices());

	s.push(start);

	while (!s.empty())
	{
		int current = s.top();
		s.pop();

		if (visited[current])
			continue;
		visited[current] = true;

		cout << current << endl;

		vector<pair<int, int>> adjacent = g.getSuccessors(current);

		for (size_t i = 0; i < adjacent.size(); i++)
			s.push(adjacent[i].first);
	}
}

void DFS_rec(const Graph& g, vector<bool>& visited, int currentVertex)
{
	visited[currentVertex] = true;
	cout << currentVertex << endl;

	vector<pair<int, int>> adjacent = g.getSuccessors(currentVertex);

	for (int i = 0; i < adjacent.size(); i++)
	{
		if (visited[adjacent[i].first])
			continue;

		DFS_rec(g, visited, adjacent[i].first);
	}
}
void DFSrec(const Graph& g, int start)
{
	if (!g.existVertex(start))
		return;

	vector<bool> visited(g.getNumOfVertices());
	DFS_rec(g, visited, start);
}

bool BFS_containsPath(const Graph& g, int start, int end)
{
	if (!g.existVertex(start))
		throw "Invalid vertex!";

	queue<int> q;
	vector<bool> visited(g.getNumOfVertices());

	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		if (current == end)
			return true;

		vector<pair<int, int>> adjacent = g.getSuccessors(current);

		for (size_t i = 0; i < adjacent.size(); i++)
		{
			if (visited[adjacent[i].first])
				continue;

			q.push(adjacent[i].first);
			visited[adjacent[i].first] = true;
		}
	}

	return false;
}
bool containsPath(const Graph& g, int start, int end)
{
	return BFS_containsPath(g, start, end);
}

bool BFS_connected(const Graph& g)
{
	if (!g.existVertex(0))
		throw "Invalid vertex!";

	queue<int> q;
	vector<bool> visited(g.getNumOfVertices());

	int vertices = 0;

	q.push(0);
	vertices++;
	visited[0] = true;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		vector<pair<int, int>> adjacent = g.getSuccessors(current);

		for (size_t i = 0; i < adjacent.size(); i++)
		{
			if (visited[adjacent[i].first])
				continue;

			q.push(adjacent[i].first);
			visited[adjacent[i].first] = true;

			vertices++;
		}
	}

	return vertices == g.getNumOfVertices();
}
bool connected(const Graph& g)
{
	if (g.isOriented())
		throw "The graph should NOT be oriented!";
	
	return BFS_connected(g);
}

bool BFS_isBipartite(const Graph& g, vector<int> visited, int start)
{
	queue<int> q;
	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int current = q.front();
		q.pop();

		vector<pair<int, int>> adjacent = g.getSuccessors(current);
		size_t currentColour = visited[current];

		for (int i = 0; i < adjacent.size(); i++)
		{
			if (visited[adjacent[i].first] == currentColour)
				return false;

			if (visited[adjacent[i].first])
				continue;

			q.push(adjacent[i].first);
			visited[adjacent[i].first] = currentColour == 1 ? 2 : 1;
		}
	}

	return true;
}
bool isBipartite(const Graph& g)
{
	if (g.isOriented())
		throw "The graph should NOT be oriented!";

	vector<int> visited(g.getNumOfVertices());

	for (int i = 0; i < visited.size(); i++)
	{
		if (!visited[i] && !BFS_isBipartite(g, visited, i))
			return false;
	}

	return true;
}

bool DFS_containsCycle(const Graph& g, vector<bool>& visited, vector<bool>& stack, int currentVertex)
{
	visited[currentVertex] = true;
	stack[currentVertex] = true;

	vector<pair<int, int>> adjacent = g.getSuccessors(currentVertex);

	for (size_t i = 0; i < adjacent.size(); i++)
	{
		int current = adjacent[i].first;
		if (stack[current])
			return true;

		if (DFS_containsCycle(g, visited, stack, current))
			return true;
	}

	stack[currentVertex] = false;
	return false;
}
bool isCyclic(const Graph& g)
{
	if (!g.isOriented())
		throw "The graph should be oriented!";

	vector<bool> visited(g.getNumOfVertices());
	vector<bool> stack(g.getNumOfVertices());

	for (size_t i = 0; i < visited.size(); i++)
	{
		if (!visited[i] && DFS_containsCycle(g, visited, stack, i))
			return true;
	}

	return false;
}

void DFSrec_topologicalSorting(const Graph& g, vector<bool>& visited, stack<int>& currentRes, int currentVertex)
{
	visited[currentVertex] = true;
		
	vector<pair<int, int>> adjacent = g.getSuccessors(currentVertex);

	for (int i = 0; i < adjacent.size(); i++)
	{
		int current = adjacent[i].first;

		if (visited[current])
			continue;

		DFSrec_topologicalSorting(g, visited, currentRes, current);
	}

	currentRes.push(currentVertex);
}
void topologicalSorting(const Graph& g, vector<int>& topoSort, bool calledBySCC)
{
	if (!calledBySCC)
	{
		if (isCyclic(g))
			throw "Only acyclic graphs can be sorted topologically!";
	}

	vector<bool> visited(g.getNumOfVertices());
	stack<int> result;

	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i])
			continue;

		DFSrec_topologicalSorting(g, visited, result, i);
	}

	while (!result.empty())
	{
		topoSort.push_back(result.top());
		result.pop();
	}
}

void DFS_rec_SCC(const Graph& g, vector<bool>& visited, vector<bool>& lastlyVisited, int currentVertex)
{
	visited[currentVertex] = true;
	lastlyVisited[currentVertex] = true;

	vector<pair<int, int>> adjacent = g.getSuccessors(currentVertex);

	for (int i = 0; i < adjacent.size(); i++)
	{
		if (visited[adjacent[i].first])
			continue;

		DFS_rec_SCC(g, visited, lastlyVisited, adjacent[i].first);
	}
}
void DFSrec_SCC(const Graph& g, vector<int> topoSort)
{
	vector<bool> visited(g.getNumOfVertices());

	cout << "The strongly connected components are:" << endl;

	for (int i = 0; i < topoSort.size(); i++)
	{
		if (visited[topoSort[i]])
			continue;

		vector<bool> lastlyVisited(g.getNumOfVertices());

		DFS_rec_SCC(g, visited, lastlyVisited, topoSort[i]);

		for (int j = 0; j < lastlyVisited.size(); j++)
		{
			if (lastlyVisited[j])
				cout << j << " ";
		}
		cout << endl;

		lastlyVisited.clear();
	}
}
void SCC(const AdjacencyListGraph& g)
{
	vector<int> topoSort;
	topologicalSorting(g, topoSort, true);

	AdjacencyListGraph transposed = g.getTransposedGraph();

	DFSrec_SCC(transposed, topoSort);
}

int Dijkstra(const Graph& g, int start, int end, vector<int>& path)
{
	vector<int> dist(g.getNumOfVertices(), INT_MAX);
	vector<int> previous(g.getNumOfVertices());

	struct temp
	{
		int vertex;
		int distFromStart;

		bool operator<(const temp& other) const
		{
			return distFromStart > other.distFromStart;
		}
	};

	priority_queue<temp> q;

	dist[start] = 0;
	q.push({ start, 0 });

	while (!q.empty())
	{
		temp currentVertex = q.top();

		if (currentVertex.vertex == end)
		{
			int current = end;
			while (current != start)
			{
				path.push_back(current);
				current = previous[current];
			}

			path.push_back(start);
			reverse(path.begin(), path.end());

			return currentVertex.distFromStart;
		}

		q.pop();

		vector<pair<int, int>> successors = g.getSuccessors(currentVertex.vertex);

		for (int i = 0; i < successors.size(); i++)
		{
			int currentSuccessor = successors[i].first;
			int currentWeight = successors[i].second;

			if (dist[currentVertex.vertex] + currentWeight < dist[currentSuccessor])
			{
				dist[currentSuccessor] = dist[currentVertex.vertex] + currentWeight;
				q.push({ currentSuccessor , dist[currentSuccessor] });
				previous[currentSuccessor] = currentVertex.vertex;
			}
		}
	}

	return INT_MAX;
}

vector<vector<int>> FloydWarshall(const Graph& g)
{
	vector<vector<int>> minDistances(g.getNumOfVertices(), vector<int>(g.getNumOfVertices(), INT_MAX));
	vector<pair<int, int>> successors;

	// mark all edges
	for (int i = 0; i < g.getNumOfVertices(); i++)
	{
		successors = g.getSuccessors(i);
		for (int j = 0; j < successors.size(); j++)
			minDistances[i][successors[j].first] = successors[j].second;
	}

	for (int i = 0; i < g.getNumOfVertices(); i++)
		minDistances[i][i] = 0;

	for (int k = 0; k < g.getNumOfVertices(); k++) // intermediate vertices
	{
		for (int i = 0; i < g.getNumOfVertices(); i++) // start vertex
		{
			for (int j = 0; j < g.getNumOfVertices(); j++) // end vertex
			{
				if (minDistances[i][j] > minDistances[i][k] + minDistances[k][j])
				{
					if (minDistances[i][k] != INT_MAX && minDistances[k][j] != INT_MAX)
						minDistances[i][j] = minDistances[i][k] + minDistances[k][j];
				}
			}
		}
	}

	return move(minDistances);
}

int Prim(const Graph& g, Graph& mst)
{
        if (g.isOriented())
		throw "The graph should NOT be oriented!";

	int mstWeight = 0;
	int addedEdges = 0;
	
	vector<bool> visited(g.getNumOfVertices(), false);

	auto comp = [](const tuple<int, int, int>& lhs, const tuple<int, int, int>& rhs) { return get<2>(lhs) > get<2>(rhs); };
	priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, decltype(comp)> q(comp);

	q.push(make_tuple(0, 0, 0)); // virtual edge for the start

	while (addedEdges < g.getNumOfVertices() - 1)
	{
		tuple<int, int, int> currentEdge = q.top();
		q.pop();

		int currentEdgeStart = get<0>(currentEdge);
		int currentEdgeEnd = get<1>(currentEdge);
		int currentEdgeWeight = get<2>(currentEdge);

		if (visited[currentEdgeEnd])
			continue;

		mstWeight += currentEdgeWeight;

		if (currentEdgeStart != currentEdgeEnd) // in order not to count the virtual edge
		{
			addedEdges++;
			cout << "Added edge: " << currentEdgeStart << "----" << currentEdgeEnd << " with weight: " << currentEdgeWeight << endl;
			mst.addEdge(currentEdgeStart, currentEdgeEnd, currentEdgeWeight);
		}
		visited[currentEdgeEnd] = true;

		vector<pair<int, int>> successors = g.getSuccessors(currentEdgeEnd);

		for (int i = 0; i < successors.size(); i++)
			q.push(make_tuple(currentEdgeEnd, successors[i].first, successors[i].second));
	}

	return mstWeight;
}
