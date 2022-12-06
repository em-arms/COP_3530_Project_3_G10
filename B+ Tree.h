#ifndef BTREE_H
#define BTREE_H

#include <string>
#include <vector>
#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include "Hotel.h"

using namespace std;

size_t MAX_NODES = 3;

struct nameKey {
	string key;
	Hotel* data;
};

struct nameNode {
	bool isLeaf;
	nameKey* key;
	size_t size;
	nameNode** ptr;
	nameNode* parent;
	nameNode();
};

class nameBPTree {
	nameNode* root;
	void insertInternal(string, Hotel*, nameNode*, nameNode*);
	nameNode* findParent(nameNode*, nameNode*);

	public:
		nameBPTree();
		Hotel* search(string);
		void insert(Hotel*);
		void display(nameNode*);
		void displayCountry(nameNode*, string);
		void displayCity(nameNode*, string);
		nameNode* getRoot();
};



nameNode::nameNode() {
	key = new nameKey[MAX_NODES-1];
	isLeaf = false;
	for (int i = 0; i < MAX_NODES - 1; i++) {
		key[i].key = "";
	}
	ptr = new nameNode *[MAX_NODES + 1];
	for (int i = 0; i < MAX_NODES - 1; i++) {
		ptr[i] = nullptr;
	}
	parent = nullptr;
	size = 0;
}

nameBPTree::nameBPTree() {
	root = nullptr;
}

Hotel* nameBPTree::search(string x) {
	if (root == nullptr) {
		return nullptr;
	}
	else {
		nameNode* current = root;
		while (!current->isLeaf) {
			for (int i = 0; i < current->size; i++) {
				if (x.compare(current->key[i].key) < 0) {
					current = current->ptr[i];
					break;
				}
				if (i == (current->size) - 1) {
					current = current->ptr[i + 1];
					break;
				}
			}
		}
		for (int i = 0; i < current->size; i++) {
			if (current->key[i].key.compare(x) == 0) {
				return current->key[i].data;
			}
		}
	}
	return nullptr;
}


nameKey* item_insert(nameKey* arr, string data, int len, Hotel* h) {
	int index = 0;
	for (int i = 0; i < len; i++) {
		if (data.compare(arr[i].key) < 0) {
			index = i;
			break;
		}
		if (i == len - 1) {
			index = len;
			break;
		}
	}

	for (int i = len; i > index; i--) {
		arr[i] = arr[i - 1];
	}

	arr[index].key = data;
	arr[index].data = h;

	return arr;
}

nameNode* BPlusTreeRangeSearch(nameNode* node, Hotel* data) {
	if (node == nullptr) {
		return nullptr;
	}
	else {
		nameNode* current = node;

		while (!current->isLeaf) {
			for (int i = 0; i < current->size; i++) {
				if (data->getName().compare(current->key[i].key) < 0) {
					current = current->ptr[i];
					break;
				}
				if (i == (current->size) - 1) {
					current = current->ptr[i + 1];
					break;
				}
			}
		}
		return current;
	}
}

void nameBPTree::insert(Hotel* thing) {
	if (root == nullptr) {
		root = new nameNode;
		root->key[0].key = thing->getName();
		root->key[0].data = thing;
		root->isLeaf = true;
		root->size = 1;
	}
	else {
		nameNode* current = root;
		current = BPlusTreeRangeSearch(current, thing);

		if (current->size < (MAX_NODES - 1)) {
			current->key = item_insert(current->key, thing->getName(), current->size, thing);
			current->size++;
			current->ptr[current->size] = current->ptr[current->size - 1];
			current->ptr[current->size - 1] = nullptr;
		}
		else {
			nameNode* newLeaf = new nameNode;
			newLeaf->isLeaf = true;
			newLeaf->parent = current->parent;

			nameKey* virtualNode = new nameKey[current->size + 1];
			for (int i = 0; i < current->size; i++) {
				virtualNode[i].key = current->key[i].key;
				virtualNode[i].data = current->key[i].data;
			}

			virtualNode = item_insert(virtualNode, thing->getName(), current->size, thing);

			current->size = (MAX_NODES) / 2;
			if ((MAX_NODES) % 2 == 0) {
				newLeaf->size = (MAX_NODES) / 2;
			}
			else {
				newLeaf->size = (MAX_NODES) / 2 + 1;
			}

			for (int i = 0; i < current->size; i++) {
				current->key[i].key = virtualNode[i].key;
				current->key[i].data = virtualNode[i].data;
			}
			for (int i = 0; i < newLeaf->size; i++) {
				newLeaf->key[i].key = virtualNode[current->size + i].key;
				newLeaf->key[i].data = virtualNode[current->size + i].data;
			}
			current->ptr[current->size] = newLeaf;
			newLeaf->ptr[newLeaf->size] = current->ptr[MAX_NODES - 1];
			current->ptr[MAX_NODES - 1] = nullptr;

			delete[] virtualNode;

			string parKey = newLeaf->key[0].key;
			Hotel* parData = newLeaf->key[0].data;

			if (current->parent == nullptr) {
				nameNode* newRoot = new nameNode;
				current->parent = newRoot;
				newLeaf->parent = newRoot;

				newRoot->key[0].key = parKey;
				newRoot->key[0].data = parData;
				newRoot->size++;

				newRoot->ptr[0] = current;
				newRoot->ptr[1] = newLeaf;

				newRoot->isLeaf = false;

				root = newRoot;
			}
			else {
				insertInternal(parKey, parData, current->parent, newLeaf);
			}
		}
	}
}





nameNode** child_insert(nameNode** child_arr, nameNode* child, int len, int index) {
	for (int i = len; i > index; i--) {
		child_arr[i] = child_arr[i - 1];
	}
	child_arr[index] = child;
	return child_arr;
}

int find_index(nameKey* arr, string data, int len) {
	int index = 0;
	for (int i = 0; i < len; i++) {
		if (data.compare(arr[i].key) < 0) {
			index = i;
			break;
		}
		if (i == len - 1) {
			index = len;
			break;
		}
	}
	return index;
}

nameNode* child_item_insert(nameNode* node, string data, nameNode* child, Hotel* h) {
	int item_index = 0;
	int child_index = 0;
	for (int i = 0; i < node->size; i++) {
		if (data.compare(node->key[i].key) < 0) {
			item_index = i;
			child_index = i + 1;
			break;
		}
		if (i == node->size - 1) {
			item_index = node->size;
			child_index = node->size + 1;
			break;
		}
	}
	for (int i = node->size; i > item_index; i--) {
		node->key[i].key = node->key[i - 1].key;
		node->key[i].data = node->key[i - 1].data;
	}
	for (int i = node->size + 1; i > child_index; i--) {
		node->ptr[i] = node->ptr[i - 1];
	}

	node->key[item_index].key = data;
	node->key[item_index].data = h;
	node->ptr[child_index] = child;

	return node;
}
/*
int i = 0;
while (x.compare(current->key[i].key) > 0 && i < current->size)
	i++;
for (int j = current->size; j > i; j--) {
	current->key[j].key = current->key[j - 1].key;
	current->key[j].data = current->key[j - 1].data;
}
for (int j = current->size + 1; j > i + 1; j--) {
	current->ptr[j] = current->ptr[j - 1];
}
current->key[i].key = x;
current->key[i].data = y;
current->ptr[i + 1] = child;
*/

void nameBPTree::insertInternal(string x, Hotel* y, nameNode* cur, nameNode* child) {
	nameNode* current = cur;
	if (current->size < (MAX_NODES - 1)) {
		current = child_item_insert(current, x, child, y);
		current->size++;
	}
	else {
		nameNode* newInternal = new nameNode;
		newInternal->parent = current->parent;

		nameKey* virtualData = new nameKey[current->size + 1];
		nameNode** virtualPtr = new nameNode*[current->size + 2];

		for (int i = 0; i < current->size; i++) {
			virtualData[i] = current->key[i];
			virtualData[i] = current->key[i];
		}

		virtualData = item_insert(virtualData, x, current->size, y);

		for (int i = 0; i < current->size + 1; i++) {
			virtualPtr[i] = current->ptr[i];
		}

		virtualPtr[current->size + 1] = nullptr;
		virtualPtr = child_insert(virtualPtr, child, current->size + 1, find_index(virtualData, x, current->size + 1));
		
		current->size = (MAX_NODES) / 2;

		if ((MAX_NODES) % 2 == 0) {
			newInternal->size = (MAX_NODES) / 2 - 1;
		}
		else {
			newInternal->size = (MAX_NODES) / 2;
		}
		
		for (int i = 0; i < current->size; i++) {
			current->key[i].key = virtualData[i].key;
			current->key[i].data = virtualData[i].data;
		}
		current->ptr[current->size] = virtualPtr[current->size];

		for (int i = 0; i < newInternal->size; i++) {
			newInternal->key[i].key = virtualData[current->size + i + 1].key;
			newInternal->ptr[i] = virtualPtr[current->size + i + 1];
			newInternal->ptr[i]->parent = newInternal;
		}
		newInternal->ptr[newInternal->size] = virtualPtr[current->size + newInternal->size + 1];
		newInternal->ptr[newInternal->size]->parent = newInternal;

		string parKey = virtualData[MAX_NODES / 2].key;
		Hotel* parData = virtualData[MAX_NODES / 2].data;

		delete[] virtualData;
		delete[] virtualPtr;
		
		if (current->parent == nullptr) {
			nameNode* newRoot = new nameNode;

			current->parent = newRoot;
			newInternal->parent = newRoot;
			newRoot->key[0].key = parKey;
			newRoot->key[0].data = parData;
			newRoot->size++;

			newRoot->ptr[0] = current;
			newRoot->ptr[1] = newInternal;

			newRoot->isLeaf = false;

			root = newRoot;
		}
		else {
			insertInternal(parKey, parData, current->parent, newInternal);
		}
	}
}


nameNode* nameBPTree::findParent(nameNode* current, nameNode* child) {
	nameNode* parent;
	if (current->isLeaf || (current->ptr[0])->isLeaf) {
		return NULL;
	}
	for (int i = 0; i < current->size + 1; i++) {
		if (current->ptr[i] == child) {
			parent = current;
			return parent;
		}
		else {
			parent = findParent(current->ptr[i], child);
			if (parent != NULL)
				return parent;
		}
	}
	return NULL;
}

void nameBPTree::display(nameNode* current) {
	if (current != NULL) {
		for (int i = 0; i < current->size; i++) {
			cout << current->key[i].key << " ";
			if (current->isLeaf) {
				cout << "(Leaf)";
			}
			cout << " | ";
		}
		cout << endl;
		if (current->isLeaf != true) {
			for (int i = 0; i < current->size + 1; i++) {
				display(current->ptr[i]);
			}
		}
	}
}

void nameBPTree::displayCountry(nameNode* current, string country) {
	if (current != NULL) {
		for (int i = 0; i < current->size; i++) {
			if (current->isLeaf && country.compare(current->key[i].data->getCountry()) == 0) {
				cout << current->key[i].data->getName() << endl;
			}
		}
		if (current->isLeaf != true) {
			for (int i = 0; i < current->size + 1; i++) {
				displayCountry(current->ptr[i], country);
			}
		}
	}
}

void nameBPTree::displayCity(nameNode* current, string city) {
	if (current != NULL) {
		for (int i = 0; i < current->size; i++) {
			if (current->isLeaf && city.compare(current->key[i].data->getCity()) == 0) {
				cout << current->key[i].data->getName() << endl;
			}
		}
		if (current->isLeaf != true) {
			for (int i = 0; i < current->size + 1; i++) {
				displayCity(current->ptr[i], city);
			}
		}
	}
}

nameNode* nameBPTree::getRoot() {
	return root;
}

#endif