#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

//Node to store the data (Linked List)
class Node {
public:
	string key;
	int value;
	Node(string key, int value)
	{
		this->key = key;
		this->value = value;
	}
};

//LRU Cache Data Structure
class LRUCache {
public:
	int maxSize;
	list<Node> l;
	unordered_map<string, list<Node>::iterator>m;

	LRUCache(int maxSize) {
		this->maxSize = maxSize > 1 ? maxSize : 1;
	}

	void insertKeyValue(string key, int value) {
		//2 cases
		if (m.count(key) != 0) {
			//replace the old value and update
			auto it = m[key];
			it->value = value;
		}
		else
		{
			//check if cache is full or not
			//remove the least recently used item from the cache
			if (l.size() == maxSize) {
				Node last = l.back();
				m.erase(last.key); //removes from the hashmap
				l.pop_back(); //removes from the LinkedList
			}

			Node n(key, value);
			l.push_front(n);
			m[key] = l.begin();
		}

	}
	int*getValue(string key) {
		//
		if (m.count(key) != 0) {
			auto it = m[key];

			int value = it->value;

			l.push_front(*it);
			l.erase(it);


			m[key] = l.begin();
			return &l.begin()->value;
		}
		return NULL;
	}

	string mostRecentKey() {
		return l.front().key;
	}
};



int main() {
	LRUCache lru(3);
	lru.insertKeyValue("CR7", 7);
	lru.insertKeyValue("LM10", 10);
	lru.insertKeyValue("NJR", 11);

	cout << lru.mostRecentKey() << endl;

	lru.insertKeyValue("CR7", 12);
	cout << lru.mostRecentKey() << endl;

	lru.insertKeyValue("KDB", 13);
	int *orders = lru.getValue("CR7");
	if (orders != NULL)
	{
		cout << "Order of CR7" << *orders << endl;
	}

}