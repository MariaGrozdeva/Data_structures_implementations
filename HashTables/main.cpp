#include "SeparateChainingHashTable.hpp"
#include "LinearProbingHashTable.hpp"
#include "DoubleHashingHashTable.hpp"

int main()
{
	SeparateChainingHashTable<string, int> phoneBook;

	phoneBook.put("Police", 166);
	phoneBook.put("Ambulance", 150);
	phoneBook.put("Fire Department", 160);

	for (auto it = phoneBook.begin(); it != phoneBook.end(); ++it)
		cout << "Key: " << (*it).key << ", Value: " << (*it).value << endl;
	cout << endl;

	DoubleHashingHashTable<string, string> capitals;
	capitals.put("Bulgaria", "Sofia");
	capitals.put("Russia", "Moscow");
	capitals.put("Germany", "Berlin");
	capitals.remove("Russia");

	for (auto it = capitals.begin(); it != capitals.end(); ++it)
		cout << "Key: " << (*it).key << ", Value: " << (*it).value << endl;
	cout << endl;
}