#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

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


	bool contains(T key) {
		for (const auto val : _keys) {
			if (key == val) {
				return true;
			}
		}
		return false;
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

	BTreeNode<T>* help_find_parent(BTreeNode<T>* parent, BTreeNode<T>* to_find) {
		for (auto val& : parent->_children) {
			if (val == to_find) {
				return parent;
			}
		}
		return 
	}

	BTreeNode<T>* find_parent(BTreeNode<T>* node) {
		return help_find_parent(_root, node);
	}


	BTreeNode<T>* half_node(BTreeNode<T>* p, char side) {
		BTreeNode<T>* res = new BTreeNode<T>();
		int start, end;
		int child_size = p->_children.size();
		if (side == 'l') {
			start = 0;
			end = _t - 1;

			res->_children = vector<BTreeNode<T>*>(p->_children.begin(), p->_children.begin() + child_size / 2);
		}
		else if (side == 'r') {
			start = _t;
			end = 2 * _t - 1;

			res->_children = vector<BTreeNode<T>*>(p->_children.begin() + child_size / 2, p->_children.end());
		}
		res->_keys = vector<T>(p->_keys.begin() + start, p->_keys.begin() + end);
		res->_parent = p->_parent;
		return res;
	}


	BTreeNode<T>* find_node_to_ins(BTreeNode<T>* root, T key) {
		int child_size = root->_children.size();
		if (child_size == 0) {
			if (root->contains(key)) {
				return nullptr;
			}
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

	void split_node(BTreeNode<T>*& node) {
		BTreeNode<T>* parent = node->_parent;
		if (!parent) {
			BTreeNode<T>* new_root = new BTreeNode<T>();
			new_root->_keys.push_back(node->_keys[_t - 1]);
			BTreeNode<T>* l_node = half_node(node, 'l');
			BTreeNode<T>* r_node = half_node(node, 'r');
			new_root->_children.push_back(l_node);
			new_root->_children.push_back(r_node);
			l_node->_parent = new_root;
			r_node->_parent = new_root;
			_root = new_root;
			node = new_root
		}
		else {
			if (parent->_keys.size() == 2 * _t - 1) {
				split_node(parent);
				delete parent;
			}
			BTreeNode<T>* l_node = half_node(node, 'l');
			BTreeNode<T>* r_node = half_node(node, 'r');
			parent->_keys.push_back(node->_keys[_t - 1]);
			sort(node->_keys.begin(), node->_keys.end());
			parent->_children.push_back(l_node);
			parent->_children.push_back(r_node);
			l_node->_parent = parent;
			r_node->_parent = parent;
			for (int i = 0; i < parent->_children.size(); i++) {
				if (parent->_children[i] == node) {
					parent->_children.erase(parent->_children.begin() + i);
					break;
				}
			}
		}
	}


	bool insert(T key) {
		if (!_root) {
			_root = new BTreeNode<T>();
			_root->_keys.push_back(key);
			sort(_root->_keys.begin(), _root->_keys.end());
			return true;
		}
		BTreeNode<T>* to_ins = find_node_to_ins(_root, key);
		if (!to_ins) {
			return false;
		}
		if (to_ins->_keys.size() < 2 * _t - 1) {
			to_ins->_keys.push_back(key);
			sort(to_ins->_keys.begin(), to_ins->_keys.end());
			return true;
		}
		split_node(to_ins);
		delete to_ins;
		return this->insert(key);
	}

	//insert end

	//print start

	void help_print(BTreeNode<T>* node) {
		for (const auto val : node->_keys) {
			cout << val << " ";
		}
		cout << "\t";
		for (const auto n : node->_children) {
			help_print(n);
		}
	}

	void print() {
		help_print(_root);
		cout << endl;
	}

	//print end
};