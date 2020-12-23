#include <iostream>
#include <vector>
#include <string>
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
void print(Node<T>* root)
{
	if (root == nullptr)
		return;

	print(root->left);
	cout << root->data << " ";
	print(root->right);
}
template <typename T>
void free(Node<T>* root)
{
	if (root == nullptr)
		return;

	free(root->left);
	free(root->right);

	delete root;
}

// Задача 1: Да се напише функция, която приема двоично дърво и връща дали дадено число се съдържа в него.
template <typename T>
bool contains(Node<T>* root, T element)
{
	if (root == nullptr)
		return false;
	return root->data == element || contains(root->left, element) || contains(root->right, element);
}

// Задача 2: Да се напише функция, която приема двоично дърво и връща сумата на елементите в него.
template <typename T>
int sum(Node<T>* root)
{
	if (root == nullptr)
		return 0;

	return root->data + sum(root->left) + sum(root->right);
}

// Задача 3: Да се напише функция, която приема двоично дърво и връща най-големият елемент в него.
template <typename T>
T maxBT(Node<T>* root)
{
	if (root->left == nullptr && root->right == nullptr)
		return root->data;

	if (root->left != nullptr && root->right == nullptr)
		return max(root->data, maxBT(root->left));

	if (root->left == nullptr && root->right != nullptr)
		return max(root->data, maxBT(root->right));

	return max(root->data, max(maxBT(root->left), maxBT(root->right)));
}

// Задача 4: Да се напише функция, която приема двоично дърво и връща височината му.
template <typename T>
int height(Node<T>* root)
{
	if (root == nullptr)
		return -1;

	return 1 + max(height(root->left), height(root->right));
}

// Задача 5: Да се напише функция, която приема двоично дърво и връща броя на елементите му.
template <typename T>
int numOfElements(Node<T>* root)
{
	if (root == nullptr)
		return 0;
	return 1 + numOfElements(root->left) + numOfElements(root->right);
}

// Задача 6: Да се напише функция, която приема двоично дърво с n върха и проверява дали 
// числата от 1 до n се срещат точно веднъж в дървото.
bool markOccurrences(Node<int>* root, vector<bool>& nums, int n)
{
	if (root == nullptr)
		return true;

	if (root->data < 1 || root->data > n)
		return false;
	if (nums[root->data - 1])
		return false;

	nums[root->data - 1] = true;
	return markOccurrences(root->left, nums, n) && markOccurrences(root->right, nums, n);
}
bool isPermutation(Node<int>* root)
{
	int size = numOfElements(root);
	vector<bool> nums(size);

	return markOccurrences(root, nums, size);
}

// Задача 7: Да се напише функция, която приема двоично дърво, чиито елементи са символи и цяло число к 
// и отпечатва думата на к - тото ниво на дървото.
string word(Node<char>* root, int k)
{
	string wordOnLevel;

	if (root == nullptr)
		return "";
	if (k == 1)
	{
		wordOnLevel += (char)root->data;
		return wordOnLevel;
	}

	return word(root->left, k - 1) + word(root->right, k - 1);
}

// Задача 8: Да се напише функция, която приема двоично дърво и връща всички думи, които са получени от корена до някое листо.
void fillWords(Node<char>* root, vector<string>& v, string currentWord)
{
	currentWord += root->data;
	if (root->left == nullptr && root->right == nullptr)
	{
		v.push_back(currentWord);
		return;
	}

	if (root->left != nullptr)
		fillWords(root->left, v, currentWord);
	if (root->right != nullptr)
		fillWords(root->right, v, currentWord);
}

// Задача 9: Да се напише функция, която приема двоично дърво и връща сумата на листата.
template<typename T>
T sumOfLeaves(Node<T>* root)
{
	int sum = 0;
	if (root == nullptr)
		return 0;
	if (root->left == nullptr && root->right == nullptr)
		return root->data;

	return sumOfLeaves(root->left) + sumOfLeaves(root->right);
}



// Задача 10: Напишете функция, която обхожда дърво по следния начин - ляво - корен - дясно(Inorder Traversal).
template<typename T>
void inorderTraversal(Node<T>* root)
{
	printBT(root);
}

// Задача 11: Напишете функция, която приема указател към корена на дърво и цяло число n и принтира елементите, които се намират на ниво n.
template <typename T>
void printOnLevel(Node<T>* root, int n)
{
	if (root == nullptr)
		return;
	if (n == 1)
		cout << root->data;

	printOnLevel(root->left, n - 1);
	printOnLevel(root->right, n - 1);
}

// Задача 12: Напишете функция, която приема указател към корена на дърво и цяло число n и връща сумата на елементите, които се намират на ниво n.
template <typename T>
int sumOnLevel(Node<T>* root, int n)
{
	int sum = 0;

	if (root == nullptr)
		return 0;
	if (n == 1)
		return root->data;

	return sumOnLevel(root->left, n - 1) + sumOnLevel(root->right, n - 1);
}

// Задача 13: Напишете функция, която приема указател към корена на дърво и низ, съставен само от символите 'l', 'r', и принтира елемента, към
// който сочи низът (като 'l' означава дa търсим в текущото ляво поддърво, а 'r' - в дясното).
template <typename T>
void printElement(Node<T>* root, const char* path)
{
	if (path[0] == '\0')
		cout << root->data;

	if (path[0] == 'l')
		printElement(root->left, ++path);
	else if (path[0] == 'r')
		printElement(root->right, ++path);
}

// Задача 14: Напишете фунцкия, която приема указател към корена на дърво и цяло число x и връща низа, който сочи към него(като използваме
// условието от горната задача).
string getPath(Node<int>* root, int x, string word = "")
{
	if (root == nullptr)
		return "";
	if (x == root->data)
		return word;

	string res = getPath(root->left, x, word + "l");

	if (res != "")
		return res;
	else
		return getPath(root->right, x, word + "r");
}

// Задача 15: Напишете фунцкия, която приема указател към корена на дърво и променя дървото в неговата огледална форма.
template <typename T>
void mirror(Node<T>*& root)
{
	if (root == nullptr)
		return;

	if (root->left && root->right)
	{
		Node<T>* temp = root->left;
		root->left = root->right;
		root->right = temp;
	}
	else if (root->left && !root->right)
	{
		root->right = root->left;
		root->left = nullptr;
	}
	else if (root->right && !root->left)
	{
		root->left = root->right;
		root->right = nullptr;
	}

	mirror(root->left);
	mirror(root->right);
}

// Задача 16: Напишете фунцкия, която приема указател към корена на дърво и проверява дали то е двоично дърво за търсене(BST).
bool checkIfTreeIsBST(Node<int>* root, int min, int max)
{
	if (root == nullptr)
		return true;

	if (root->data < min || root->data > max)
		return false;

	return checkIfTreeIsBST(root->left, min, root->data - 1) && checkIfTreeIsBST(root->right, root->data + 1, max);
}
bool isBST(Node<int>* root)
{
	return checkIfTreeIsBST(root, INT_MIN, INT_MAX);
}

// Задача 17: Напишете функция, която по подадено двоично дърво от цели числа намира листото с най-голяма стойност.
int biggestValueLeaf(Node<int>* root)
{
	if (root == nullptr)
		return 0;
	if (!root->left && !root->right)
		return root->data;

	return max(biggestValueLeaf(root->left), biggestValueLeaf(root->right));
}

// Задача 18: Нека е дадено двоично наредено дърво от цели числа и цяло число x. 
// Напишете функция, която добавя дадената стойност на коректно място в дървото.
void insertAtBT(Node<int>* root, int x)
{
	if (x < root->data && !root->left)
	{
		root->left = new Node<int>(x);
		return;
	}
	else if (x > root->data && !root->right)
	{
		root->right = new Node<int>(x);
		return;
	}

	if (x < root->data)
		insertAtBT(root->left, x);
	else if (x > root->data)
		insertAtBT(root->right, x);
}

// Задача 19.1: Нека е дадено двоично наредено дърво от цели числа и две цели числа, които се съдържат в дървото - x, y. Намере LCA на x и y.
Node<int>* LCABST(Node<int>* root, int x, int y)
{
	if ((x < root->data && y > root->data) || (x > root->data && y < root->data))
		return root;

	if (x < root->data && y < root->data)
		return LCABST(root->left, x, y);
	else if (x > root->data && y > root->data)
		return LCABST(root->right, x, y);
}

// Задача 19.2: Ами ако дървото не е наредено ?
bool containsPath(Node<int>* root, int el)
{
	if (root == nullptr)
		return false;
	if (root->data == el)
		return true;

	return containsPath(root->left, el) || containsPath(root->right, el);
}
Node<int>* getLCABT(Node<int>* root, int x, int y, Node<int>*& LCA)
{
	if (root == nullptr)
		return LCA;

	if (containsPath(root, x) && (containsPath(root, y)))
		LCA = root;

	getLCABT(root->left, x, y, LCA);
	getLCABT(root->right, x, y, LCA);

	return LCA;
}
Node<int>* LCABT(Node<int>* root, int x, int y)
{
	Node<int>* LCA = root;
	getLCABT(root, x, y, LCA);

	return LCA;
}

// Задача 20: Huffman coding
void getEncodedString(Node<char>* root, string& coding, string& toGet, int& index)
{
	if (!root->left && !root->right)
	{
		toGet += root->data;
		return;
	}

	if (coding[index] == '0')
		getEncodedString(root->left, coding, toGet, ++index);
	else
		getEncodedString(root->right, coding, toGet, ++index);

}
string readHuffmanEncoding(Node<char>* root, string coding)
{
	string strToGet = "";
	int index = 0;

	while (coding[index] != '\0')
		getEncodedString(root, coding, strToGet, index);

	return strToGet;
}

// Задача 21: Напишете функция, която проверява дали едно двоично дърво е балансирано по височина.
template <typename T>
bool isBalanced(Node<T>* root)
{
	if (abs(heightBT(root->left) - heightBT(root->right)) <= 1)
		return true;
	return false;
}



// Задача 22 (от контролно): Да се напише функция, която намира сумата на всички елементи на двоично наредено дърво от цели числа,
// които имат нечетен брой наследници в интервала [x, y] 
// (т.е. сумата на броя на елементите в лявото поддърво и броя на елементите в дясното поддърво в интервала [x, y] е нечетно число). 
// Нека x и y са параметри на функцията.
int numOfNodesInAnInterval(Node<int>* root, int start, int end)
{
	if (!root)
		return 0;

	if (root->data >= start && root->data <= end)
		return 1 + numOfNodesInAnInterval(root->left, start, end) + numOfNodesInAnInterval(root->right, start, end);

	else if (root->data <= start)
		return numOfNodesInAnInterval(root->right, start, end);

	else if (root->data >= end)
		return numOfNodesInAnInterval(root->left, start, end);
}
int sumOfNodesWithOddNumberOfChildren(Node<int>* root, int start, int end)
{
	if (!root)
		return 0;

	int numOfChildren = numOfNodesInAnInterval(root->left, start, end) + numOfNodesInAnInterval(root->right, start, end);

	if (numOfChildren % 2)
		return root->data +
		sumOfNodesWithOddNumberOfChildren(root->left, start, end) + sumOfNodesWithOddNumberOfChildren(root->right, start, end);

	return sumOfNodesWithOddNumberOfChildren(root->left, start, end) + sumOfNodesWithOddNumberOfChildren(root->right, start, end);
}


// Задача 23 (от контролно): Ниво L на двоично дърво съдържа всички възли на дървото, които се намират на разстояние L от корена на дървото
// (забележка: приемаме, че коренът е на ниво 0, преките му наследници са на ниво 1 и т.н.).
// Да се напише функция, която приема като параметри указатели към корените на две двоични дървета от цели числа
// и проверява дали е вярно, че елементите на всяко ниво L на едното дърво съвпадат с елементите на съответното ниво L на другото дърво.
bool areVectorsSame(vector<Node<int>*> nodes1, vector<Node<int>*> nodes2)
{
	for (int j = 0; j < nodes1.size(); j++)
	{
		bool isCorrect = false;
		for (int k = 0; k < nodes1.size(); k++)
		{
			if (nodes1[j]->data == nodes2[k]->data)
			{
				isCorrect = true;
				break;
			}
		}
		if (!isCorrect)
			return false;
	}

	return true;
}
void createNextVectors(vector<Node<int>*>& nodes1, vector<Node<int>*>& nodes2, vector<Node<int>*>& nodes1Next, vector<Node<int>*>& nodes2Next)
{
	for (int j = 0; j < nodes1.size(); j++)
	{
		if (nodes1[j]->left)
			nodes1Next.push_back(nodes1[j]->left);
		if (nodes1[j]->right)
			nodes1Next.push_back(nodes1[j]->right);

		if (nodes2[j]->left)
			nodes2Next.push_back(nodes2[j]->left);
		if (nodes2[j]->right)
			nodes2Next.push_back(nodes2[j]->right);
	}
	nodes1 = nodes1Next;
	nodes2 = nodes2Next;
}
bool sameOnLevel(Node<int>* root1, Node<int>* root2)
{
	int height1 = height(root1);
	int height2 = height(root2);
	if (height1 != height2)
		return false;

	vector<Node<int>*> nodes1;
	vector<Node<int>*> nodes2;
	vector<Node<int>*> nodes1Next;
	vector<Node<int>*> nodes2Next;

	nodes1.push_back(root1);
	nodes2.push_back(root2);

	for (int i = 0; i <= height1; i++)
	{
		if (!areVectorsSame(nodes1, nodes2))
			return false;

		createNextVectors(nodes1, nodes2, nodes1Next, nodes2Next);

		if (nodes1.size() != nodes2.size())
			return false;

		while (!nodes1Next.empty())
		{
			nodes1Next.pop_back();
			nodes2Next.pop_back();
		}
	}
	return true;
}


// Задача 24 (от контролно): Нека имаме двоично дърво от цели числа. Напишете функция, която приема такова дърво и пресмята сумата от елементите,
// които се намират на нечетно ниво и имат само десен наследник.
int sumOfNodesOnOddLevelsHelper(Node<int>* root, int level)
{
	if (root == nullptr)
		return 0;
	if (level % 2)
	{
		if (root->right && !root->left)
			return root->data;
	}

	return sumOfNodesOnOddLevelsHelper(root->left, level + 1) + sumOfNodesOnOddLevelsHelper(root->right, level + 1);
}
int sumOfNodesOnOddLevels(Node<int>* root)
{
	return sumOfNodesOnOddLevelsHelper(root, 0);
}


// Задача 25 (от контролно): Създайте(чрез включване) двоично наредено дърво от интервали от числа([a, b], a <= b).
// Наредбата в дървото да бъде по средната стойност на интервала. Намерете максималния интервал от дървото(спрямо описаната наредба в него),
// чието сечение с всеки един от другите интервали е непразно, или върнете[0, 0] ако такъв няма.
// Използвайте наредеността на дървото, където е удачно.
struct Interval
{
	int start;
	int end;

	Interval(int start, int end) : start(start), end(end) {}

	int getAverage()
	{
		return (start + end) / 2;
	}
};
struct NodeInterval
{
	Interval interval;

	NodeInterval* left;
	NodeInterval* right;

	NodeInterval(Interval interval) : interval(interval), left(nullptr), right(nullptr) {}
};

bool Intersection(Interval int1, Interval int2)
{
	return !(int1.end < int2.start || int1.start > int2.end);
}
bool noEmptyIntersection(NodeInterval* root, Interval interval)
{
	if (!root)
		return true;

	if (!Intersection(root->interval, interval))
		return false;

	return noEmptyIntersection(root->left, interval) && noEmptyIntersection(root->right, interval);
}

void getMaxIntervalHelper(NodeInterval* currRoot, NodeInterval*& currMax, NodeInterval* root)
{
	if (!currRoot)
		return;
	if (currMax)
		return;

	getMaxIntervalHelper(currRoot->right, currMax, root);

	if (!currMax && noEmptyIntersection(root, currRoot->interval))
	{
		currMax = currRoot;
		return;
	}

	getMaxIntervalHelper(currRoot->left, currMax, root);
}
Interval getMaxInterval(NodeInterval* root)
{
	NodeInterval* currMax = nullptr;
	getMaxIntervalHelper(root, currMax, root);

	if (currMax == nullptr)
		return Interval(0, 0);

	return currMax->interval;
}



int main()
{
	//Node<int>* root = new Node<int>(10);
	//Node<int>* n1 = new Node<int>(8);
	//Node<int>* n2 = new Node<int>(15);
	//Node<int>* n3 = new Node<int>(4);
	//Node<int>* n4 = new Node<int>(9);
	//Node<int>* n5 = new Node<int>(14);
	//Node<int>* n6 = new Node<int>(20);
	//Node<int>* n7 = new Node<int>(3);
	//Node<int>* n8 = new Node<int>(5);
	//Node<int>* n9 = new Node<int>(1);
	//root->left = n1;
	//root->right = n2;
	//n1->left = n3;
	//n1->right = n4;
	//n2->left = n5;
	//n2->right = n6;
	//n3->left = n7;
	//n3->right = n8;
	//n7->left = n9;

	//Node<char>* rootCHAR = new Node<char>('A');
	//Node<char>* n1c = new Node<char>('B');
	//Node<char>* n2c = new Node<char>('C');
	//Node<char>* n3c = new Node<char>('D');
	//Node<char>* n4c = new Node<char>('E');
	//Node<char>* n5c = new Node<char>('F');
	//Node<char>* n6c = new Node<char>('G');
	//Node<char>* n7c = new Node<char>('H');
	//Node<char>* n8c = new Node<char>('I');
	//Node<char>* n9c = new Node<char>('J');
	//rootCHAR->left = n1c;
	//rootCHAR->right = n2c;
	//n1c->left = n3c;
	//n1c->right = n4c;
	//n2c->left = n5c;
	//n2c->right = n6c;
	//n3c->left = n7c;
	//n3c->right = n8c;
	//n7c->left = n9c;

	NodeInterval* root = new NodeInterval({ 8,12 });
	NodeInterval* n1 = new NodeInterval({ 6,10 }); // Replace with {6,8} and getMaxInterval(root) will return {8,12}
	NodeInterval* n2 = new NodeInterval({ 10,20 });
	NodeInterval* n3 = new NodeInterval({ 7,12 });
	NodeInterval* n4 = new NodeInterval({ 11,18 });
	NodeInterval* n5 = new NodeInterval({ 10,30 });
	root->left = n1;
	root->right = n2;
	n1->right = n3;
	n2->left = n4;
	n2->right = n5;

	cout << getMaxInterval(root).start << " " << getMaxInterval(root).end;
}