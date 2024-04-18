#pragma once

#include <vector>
#include <algorithm>

using namespace std;


template <typename T>
class BTreeNode {
private:

public:
	vector<T> _keys;
	vector<BTreeNode<T>*> _children;
	BTreeNode<T>* _parent;

	BTreeNode() {
		_keys = vector<T>(0);
		_children = vector<BTreeNode<T>*>(0);
		_parent = nullptr;
	}
};


template <typename T>
class BTree {
private:
	BTreeNode<T>* _root;
	int _t;
public:
	BTree() : _root(nullptr) {};
	BTree(int t) : _root(nullptr), _t(t) {};

	//insert
	BTreeNode<T>* find_node_to_ins(BTreeNode<T>* root, T key) {
		int child_size = root->_children.size();
		if (child_size == 0) {
			return root;
		}
		for (int i = 0; i < root->_keys.size(); i++) {
			if (root->_keys[i] == key) {
				return nullptr;
			}
			if (key < root->_keys[i]) {
				return find_node_to_ins(root->_children[i], key);
			}
		}
		return find_node_to_ins(root->_children[child_size - 1], key);
	}

	void split_node(BTreeNode<T>* node) {

	}


	bool insert(T key) {
		if (!_root) {
			_root = new BTreeNode<T>();
			_root->_keys.push_back(key);
			return true;
		}
		BTreeNode<T>* to_ins = find_node_to_ins(_root, key);
		if (to_ins->_keys.size() < 2 * _t - 1) {
			to_ins->_keys.push_back(key);
			return true;
		}
		
	}

	//insert end
};