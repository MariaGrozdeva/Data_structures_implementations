#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

template <typename T>
struct Node
{
	T data;
	Node* left;
	Node* right;

	Node(T data) : data(data), left(nullptr), right(nullptr) {}
};

template <typename T>
void Free(Node<T>* root)
{
	if (!root)
		return;

	Free(root->left);
	Free(root->right);

	delete root;
}

class Graph
{
private:
	vector<vector<int>> adjList;

public:
	Graph(int n) : adjList(n) {}

	void addEdge(int start, int end)
	{
		adjList[start].push_back(end);
		adjList[end].push_back(start);
	}
	vector<int> getSuccessors(int vertex) const
	{
		return adjList[vertex];
	}
	int getVertexCount() const
	{
		return adjList.size();
	}
};
class GraphChar
{
private:
	vector<vector<char>> adjList;

public:
	GraphChar(int n) : adjList(n) {}

	void addEdge(char start, char end)
	{
		adjList[start].push_back(end);
		//adjList[end].push_back(start);
	}
	vector<char> getSuccessors(char vertex) const
	{
		return adjList[vertex];
	}
	int getVertexCount() const
	{
		return adjList.size();
	}
};


// ДЪРВЕТА
// Задача 1: Да се изведат всички думи, получени при обхождане в широчина (BFS) на двоично дърво, съставено от латински букви.
// Един "ред" в дървото отговаря на една дума.
int height(Node<char>* root)
{
	if (!root)
		return -1;

	return 1 + max(height(root->left), height(root->right));
}
void getWordsBFS(Node<char>* root, vector<string>& words)
{
	int heightOfRoot = height(root);

	vector<Node<char>*> nodesOnLevel;
	vector<Node<char>*> nodesOnNextLevel;
	nodesOnLevel.push_back(root);

	for (int i = 0; i <= heightOfRoot; i++)
	{
		string tempWord = "";
		for (int j = 0; j < nodesOnLevel.size(); j++)
		{
			tempWord += nodesOnLevel[j]->data;
			
			if (nodesOnLevel[j]->left)
				nodesOnNextLevel.push_back(nodesOnLevel[j]->left);
			if (nodesOnLevel[j]->right)
				nodesOnNextLevel.push_back(nodesOnLevel[j]->right);
		}

		words.push_back(tempWord);
		nodesOnLevel = nodesOnNextLevel;
		nodesOnNextLevel.clear();
	}
}

// Задача 2: Да се изведат всички думи, получени при обхождане в дълбочина (DFS) на двоично дърво, съставено от латински букви.
void getWordsDFS(Node<char>* root, vector<string>& words, string tempWord = "")
{
	if (!root)
		return;

	if (!root->left && !root->right)
	{
		tempWord += root->data;
		words.push_back(tempWord);
		return;
	}

	tempWord += root->data;

	getWordsDFS(root->left, words, tempWord);
	getWordsDFS(root->right, words, tempWord);
}

// Задача 3: Напишете функция, която приема двоично дърво и връща дали в дървото има път от листо до друго листо само с четни числа.
void getAllPaths(Node<int>* root, vector<vector<int>>& paths, vector<int>& currentPath)
{
	if (!root)
		return;

	if (root->data % 2)
		return;

	if (!root->left && !root->right)
	{
		paths.push_back(currentPath);
		return;
	}

	currentPath.push_back(root->data);

	getAllPaths(root->left, paths, currentPath);
	getAllPaths(root->right, paths, currentPath);

	currentPath.pop_back();
}
bool existsEvenPathFromLeafToLeaf(Node<int>* root)
{
	vector<vector<int>> paths;
	vector<int> path;

	getAllPaths(root, paths, path);

	return paths.size() > 1 ? true : false;
}

// Задача 4: Напишете функция, която приема двоично дърво А и двоично дърво Б и проверява дали Б е поддърво на А.
bool checkIfSubtree(Node<int>* rootA, Node<int>* rootB)
{
	if (!rootB)
		return true;

	if (rootA->data == rootB->data)
		return checkIfSubtree(rootA->left, rootB->left) && checkIfSubtree(rootA->right, rootB->right);

	return false;
}
bool isSubtree(Node<int>* rootA, Node<int>* rootB)
{
	if (!rootA)
		return false;

	if (rootA->data == rootB->data)
	{
		if (checkIfSubtree(rootA->left, rootB->left) && checkIfSubtree(rootA->right, rootB->right))
			return true;
	}

	return isSubtree(rootA->left, rootB) || isSubtree(rootA->right, rootB);
}

struct NodeFull
{
	int data;
	vector<NodeFull*> children;

	NodeFull(int data) : data(data) {}
};
// Задача 5: Напишете функция, която проверява дали дърво с произволен брой наследници, погледнато отляво, е същото като погледнато отдясно.
bool isTreeSeenTheSameFromBothSides(NodeFull* root, vector<int>& view)
{
	vector<NodeFull*> current;
	current.push_back(root);

	while (!current.empty())
	{
		vector<NodeFull*> next;

		if (current[0]->data != current[current.size() - 1]->data)
		{
			view.clear();
			return false;
		}

		view.push_back(current[0]->data);

		for (int i = 0; i < current.size(); i++)
			next.insert(next.end(), current[i]->children.begin(), current[i]->children.end());

		current = next;
	}

	return true;
}

// Задача 6: Задача 5, но за двоично дърво.
bool isTreeSeenTheSameFromBothSides(Node<int>* root, vector<int>& view)
{
	vector<Node<int>*> current;
	current.push_back(root);

	while (!current.empty())
	{
		vector<Node<int>*> next;

		if (current[0]->data != current[current.size() - 1]->data)
		{
			view.clear();
			return false;
		}

		view.push_back(current[0]->data);

		for (int i = 0; i < current.size(); i++)
		{
			if (current[i]->left)
				next.push_back(current[i]->left);
			if (current[i]->right)
				next.push_back(current[i]->right);
		}

		current = next;
	}

	return true;
}

// Задача 7: Дадено е дърво с произволен брой наследници. "Хубав път" в дървото ще наричаме такъв път, 
// в който стойността на всеки връх се дели на стойността на следващия. Напишете функция, която приема такова дърво 
// и връща най-дългия "хубав път" започващ от корена.
void getLongestPrettyPath(NodeFull* root, vector<int>& path)
{
	path.push_back(root->data);
	vector<int> longestPath;

	for (int i = 0; i < root->children.size(); i++)
	{
		if (!root->children[i]->data || !root->data % root->children[i]->data)
			continue;

		vector<int> subPath;
		getLongestPrettyPath(root->children[i], subPath);

		if (subPath.size() > longestPath.size())
			longestPath = subPath;
	}

	path.insert(path.end(), longestPath.begin(), longestPath.end());
}

// Задача 8: Задача 7, но за двоично дърво.
void getLongestPrettyPath(Node<int>* root, vector<int>& path)
{
	if (!root)
		return;

	path.push_back(root->data);
	
	vector<int> longestSubPath;
	vector<int> subPathLeft;
	vector<int> subPathRight;

	if (root->left && root->left->data && !(root->data % root->left->data))
		getLongestPrettyPath(root->left, subPathLeft);
	if (root->right && root->right->data && !(root->data % root->right->data))
		getLongestPrettyPath(root->right, subPathRight);

	longestSubPath = subPathLeft.size() > subPathRight.size() ? subPathLeft : subPathRight;

	path.insert(path.end(), longestSubPath.begin(), longestSubPath.end());
}


// ГРАФИ
// Задача 1:
// Има голям панаир в града, в този панаир има много атракции и искаме да пробваме всичките, 
// обаче знаем, че като отидем ще се разсеяме и ще забравим през кои сме минали и през кои не сме. 
// Тъй като искаме да минем през всички точно веднъж, си правим програма, която ни казва в какъв ред да ги обходим.
//    Вход:
// На първия ред стои число n- брой атракции, които искаме да посетим. 
// На втория ред стои число m, брой пътища между две атракции. 
// На следващите m реда има наредени двойки от числа (v1, v2), казващи че има път между атракция v1 и атракция v2.
//    Изход:
// Примерен ред, в който да обходим атракциите точно веднъж.
void DFS_panair(const Graph& g, int start, vector<int>& path)
{
	vector<bool> visited(g.getVertexCount(), false);
	stack<int> s;

	s.push(start);

	while (!s.empty())
	{
		int currentVertex = s.top();
		s.pop();

		if (visited[currentVertex])
			continue;

		path.push_back(currentVertex);
		visited[currentVertex] = true;

		vector<int> successors = g.getSuccessors(currentVertex);

		for (int i = 0; i < successors.size(); i++)
			s.push(successors[i]);
	}
}

// Задача 2: Разнасяне на вестници
// Намираме се в малко село. В него има n къщи и m пътища, всеки път свързва две къщи. 
// В къща с номер i живее едно момче, разнасящо вестници. 
// Тъй като е малко, му дават да разнася вестници до точно една къща всеки ден. 
// Момчето иска да раздаде вестници на целия град, затова в следващите n - 1 дни раздава вестници до различни къщи.
// Да се напише алгоритъм, който дава примерен маршрут, по който момчето да стига до различна къща през всички n - 1 дни ( 1 на ден ), 
// преминавайки през някои от m-те пътища,
// без да повтаря къщи по своя маршрут и да не доставя до къща, до която е доставил в предишен ден. 
// Да се изведе къщата, до която е доставил, деня, в който е доставил и пътя, по който е поел.
//    Вход:
// На първите два реда се въвеждат числата n - брой къщи и m - брой пътища. 
// В следващите m реда следват двойки (v1, v2), казващи, че има път от къща v1 до къща v2. 
// След всички тези редове се въвежда i- номера на къщата, в която живее момчето и започва разнасянето.
void DFS_pathToOneHouse(const Graph& g, int start, int end, vector<int>& path)
{
	vector<bool> visited(g.getVertexCount(), false); 
	stack<int> s;

	s.push(start);

	while (!s.empty())
	{
		int currentVertex = s.top();
		s.pop();

		if (currentVertex == end)
		{
			path.push_back(currentVertex);
			return;
		}

		if (visited[currentVertex])
			continue;

		path.push_back(currentVertex);
		visited[currentVertex] = true;

		vector<int> successors = g.getSuccessors(currentVertex);

		for (int i = 0; i < successors.size(); i++)
			s.push(successors[i]);
	}
}
void getPathsToAllHouses(const Graph& g, int start, const vector<int>& houses)
{
	for (int i = 0; i < houses.size(); i++)
	{
		vector<int> path;
		DFS_pathToOneHouse(g, start, houses[i], path);

		cout << "Delivered to house " << houses[i] << " at day " << i << endl;
		cout << "Path: " << "[ ";
		for (int i = 0; i < path.size(); i++)
			cout << path[i] << " ";
		cout << "]" << endl;
	}
}

// Задача 3: Разнасяне на вестници - Част 2
// Детето е доволно от резултата на алгоритъма ни обаче много се разкарва. Да се пренапише предната задача, 
// така че детето всеки ден да взима най - краткия път до всяка къща, ако предположим, че всеки път е с равна дължина.
void BFS_shortestPathToOneHouse(const Graph& g, int start, int end, vector<int>& shortestPath)
{
	vector<bool> visited(g.getVertexCount(), false);
	vector<int> predecessors(g.getVertexCount());
	queue<int> q;

	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int currentVertex = q.front();
		q.pop();

		if (currentVertex == end)
		{
			shortestPath.push_back(currentVertex);
			int currentPredecessor = predecessors[currentVertex];

			while (currentPredecessor != start)
			{
				shortestPath.push_back(currentPredecessor);
				currentPredecessor = predecessors[currentPredecessor];
			}

			shortestPath.push_back(start);
			reverse(shortestPath.begin(), shortestPath.end());
			return;
		}

		vector<int> successors = g.getSuccessors(currentVertex);
		for (int i = 0; i < successors.size(); i++)
		{
			if (visited[successors[i]])
				continue;
			visited[successors[i]] = true;

			q.push(successors[i]);
			predecessors[successors[i]] = currentVertex;
		}
	}
}
void getShortestPathsToAllHouses(const Graph& g, int start, const vector<int>& houses)
{
	for (int i = 0; i < houses.size(); i++)
	{
		vector<int> path;
		BFS_shortestPathToOneHouse(g, start, houses[i], path);

		cout << "Delivered to house " << houses[i] << " at day " << i << endl;
		cout << "Shortest path: " << "[ ";
		for (int i = 0; i < path.size(); i++)
			cout << path[i] << " ";
		cout << "]" << endl;
	}
}

// Задача 4: Разнасяне на вестници - Част 3
// Тъй като е придобило опит през последните няколко месеца, родителите му позовяват да раздава вестници до k на брой къщи всеки ден. 
// Да се модифицира алгоритъма така, че да не прекратява неговата разходка при първата нова къща, 
// а да намира най - много k на брой къщи всеки ден.
void getShortestPathsToAllHouses(const Graph& g, int start, stack<int>& houses, int k)
{
	int count = 0;

	while (!houses.empty())
	{
		int end = houses.size() - k;

		cout << "Delivered to houses:" << endl;

		for (int i = houses.size() - 1; i >= end && !houses.empty(); i--)
		{
			vector<int> path;
			BFS_shortestPathToOneHouse(g, start, houses.top(), path);

			cout << houses.top() << " ";
			houses.pop();

			cout << "with path: " << "[ ";
			for (int i = 0; i < path.size(); i++)
				cout << path[i] << " ";
			cout << "]" << endl;
		}

		cout << " at day " << ++count << endl;
	}
}

// Задача 5: Избиране на отговорници
// Имаме клас от n ученици. Трябва да изберем минимален брой отговорници на класа, така че тези отговорници да могат да информират 
// диреткно или косвено целия клас за важни новини и събития.
// Предоставя ни се информацията за това кой ученик с кои други ученици общува. 
// Един ученик можем да го броим за информиран ако от източника на информация има някаква редица от ученици, 
// които си общуват взаимно и тази редица завършва с този ученик.
//    Вход:
// Брой ученици n, последван от число m- брой общувания и на следващите m реда - наредени двойки от ученици, които си общуват.
//    Изход:
// Минималният брой отговорници на класа.
// The minimal count ot people in charge is the number of components in the graph of students.
void BFS(const Graph& g, int start, vector<bool>& visited)
{
	queue<int> q;

	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int currentVertex = q.front();
		q.pop();

		vector<int> successors = g.getSuccessors(currentVertex);
		for (int i = 0; i < successors.size(); i++)
		{
			if (visited[successors[i]])
				continue;
			visited[successors[i]] = true;

			q.push(successors[i]);
		}
	}
}
int getMinNumOfPeopleInCharge(const Graph& g)
{
	vector<bool> traversedVertices(g.getVertexCount(), false);
	int minNumOfPeopleInCharge = 0;

	for (int i = 0; i < traversedVertices.size(); i++)
	{
		if (!traversedVertices[i])
		{
			BFS(g, i, traversedVertices);
			minNumOfPeopleInCharge++;
		}
	}

	return minNumOfPeopleInCharge;
}

// Задача 6: Напишете функция, която приема граф, чиито върхове са от символи, и по подадена дума проверява дали има такъв път в графа.
bool DFS_containsPath(const GraphChar& g, char start, char end, const string& word)
{
	vector<char> visited(g.getVertexCount(), false);
	stack<char> s;

	s.push(start);
	int currentIndex = 0;

	while (!s.empty())
	{
		char currentVertex = s.top();
		s.pop();

		if (currentVertex == end && currentIndex == word.size() - 1)
			return true;

		if (visited[currentVertex] || currentVertex != word[currentIndex] - 'a')
			continue;

		currentIndex++;
		visited[currentVertex] = true;

		vector<char> successors = g.getSuccessors(currentVertex);
		for (int i = 0; i < successors.size(); i++)
			s.push(successors[i]);
	}
	return false;
}
bool checkIfPathExist(const GraphChar& g, const string& word)
{
	char start = word[0] - 'a';
	char end = word[word.size() - 1] - 'a';

	return DFS_containsPath(g, start, end, word);
}

// Задача 7: Напишете функция, която приема граф, чийто върхове са от числа. Функцията да връща сумата на всички върхове, които са на четно
// разстояние от стартовия и сумата на всички върхове, които са на нечетно разстояние.
void BFS_getSumsOfVertices(const Graph& g, int start, int& sumOfEvenDistVertices, int& sumOfOddDistVertices)
{
	vector<int> visited(g.getVertexCount(), false);
	queue<pair<int, int>> q;

	vector<int> successorsDistFromStart(g.getVertexCount(), 0);

	q.push(make_pair(start, 0));
	visited[start] = true;

	while (!q.empty())
	{
		pair<int,int> currentVertex = q.front();
		q.pop();

		if (currentVertex.second % 2)
			sumOfOddDistVertices += currentVertex.first;
		else
			sumOfEvenDistVertices += currentVertex.first;

		vector<int> successors = g.getSuccessors(currentVertex.first);

		for (int i = 0; i < successors.size(); i++)
		{
			if (visited[successors[i]])
				continue;
			visited[successors[i]] = true;

			q.push(make_pair(successors[i], currentVertex.second + 1));
		}
	}
}

// Задача 8: Напишете функция, която намира сумата на най- големите елементи на отделни свързани компоненти в граф.
int BFS_maxElInComponentOfGraph(const Graph& g, int start, vector<bool>& visited)
{
	queue<int> q;
	int maxVertex = start;

	q.push(start);
	visited[start] = true;

	while (!q.empty())
	{
		int currentVertex = q.front();
		q.pop();

		if (currentVertex > maxVertex)
			maxVertex = currentVertex;

		vector<int> successors = g.getSuccessors(currentVertex);
		for (int i = 0; i < successors.size(); i++)
		{
			if (visited[successors[i]])
				continue;
			visited[successors[i]] = true;

			q.push(successors[i]);
		}
	}

	return maxVertex;
}
int getSumOfMaxElInComponentOfGraph(const Graph& g)
{
	int sum = 0;

	vector<bool> visited(g.getVertexCount(), false);
	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i])
			continue;

		sum += BFS_maxElInComponentOfGraph(g, i, visited);
	}

	return sum;
}


// ЗАДАЧА- ГРАФ И ДЪРВО:
// Нека имаме ориентиран граф от символи g и двоично дърво от символи t. 
// Множеството от елементите на двете структури е едно и също, като в рамките на всяка една от структурите символите са уникални. 
// Напишете функция, която проверява дали съществува път от корена на дървото до листо, който да отговаря на път в графа, 
// и ако има такъв, да го извежда (ЗАБ.: достатъчно е да изведете само един път, който да отговаря на условието).
bool checkIfGraphContainsPathFromTree(Node<char>* root, GraphChar g)
{
	vector<string> paths;
	getWordsDFS(root, paths);

	for (int i = 0; i < paths.size(); i++)
	{
		if (checkIfPathExist(g, paths[i]))
			return true;
	}

	return false;
}


int main()
{
	
}
