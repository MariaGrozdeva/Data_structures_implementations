#pragma once

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph
{
protected:
	int numOfVertices;
	bool oriented;

public:
	Graph(int numOfVertices, bool oriented) : numOfVertices(numOfVertices), oriented(oriented) {}

	int getNumOfVertices() const;
	bool existVertex(int vertex) const;

	virtual int addVertex() = 0;
	virtual void removeVertex(int vertex) = 0;

	virtual void addEdge(int start, int end, int weight) = 0;
	virtual void removeEdge(int start, int end) = 0;

	virtual vector<pair<int, int>> getSuccessors(int vertex) const = 0; // if oriented
	virtual vector<pair<int, int>> getPredecessors(int vertex) const = 0; // if oriented
	virtual vector<pair<int, int>> getNeighbors(int vertex) const; // if not oriented
};