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

	bool insert(T key) {
		for (const auto val : _keys) {
			if (val == key)
				return false;
		}
		_keys.push_back(key);
		return true;
	}

	void remove_child(BTreeNode<T>* child) {
		for (int i = 0; i < _children.size(); i++) {
			if (child == _children[i]) {
				_children.erase(_children.begin() + i);
			}
		}
	}

	pair<BTreeNode<T>*, BTreeNode<T>*> split_node() {
		BTreeNode<T>* left = new BTreeNode<T>();
		left->_parent = _parent;
		int key_size = _keys.size();
		for (int i = 0; i < key_size / 2; i++) {
			left->insert(_keys[i]);
		}
		int child_size = _children.size();
		for (int i = 0; i < child_size / 2; i++) {
			left->_children.push_back(_children[i]);
		}
		for (auto& val : left->_children) {
			val->_parent = left;
		}


		BTreeNode<T>* right = new BTreeNode<T>();
		right->_parent = _parent;
		for (int i = key_size / 2 + 1; i < key_size; i++) {
			right->insert(_keys[i]);
		}

		for (int i = key_size / 2; i < child_size; i++) {
			right->_children.push_back(_children[i]);
		}
		for (auto& val : right->_children) {
			val->_parent = right;
		}
		return pair<BTreeNode<T>*, BTreeNode<T>*>(left, right);
	}
};


template <typename T>
class BTree {
private:
	
public:
	BTreeNode<T>* _root;
	int _t;

	BTree() : _root(new BTreeNode<T>()) {};
	BTree(int t) : _root(new BTreeNode<T>()), _t(t) {};

	//split_node 
	void split_node(BTreeNode<T>* node) {
		auto nodes = node->split_node();
		BTreeNode<T>* left = nodes.first;
		BTreeNode<T>* right = nodes.second;
		BTreeNode<T>* parent = node->_parent;
		bool new_root = false;
		if (!parent) {
			parent = new BTreeNode<T>();
			new_root = true;
		}
		parent->_children.push_back(left);
		parent->_children.push_back(right);
		parent->remove_child(node);
		if (new_root) {
			_root = parent;
			left->_parent = parent;
			right->_parent = parent;
		}
		insert(node->_keys[_t - 1], parent);
	}
	//
	//insert

	BTreeNode<T>* find_node_to_ins(BTreeNode<T>* root, T key) {
		int child_size = root->_children.size();
		if (child_size == 0) {
			return root;
		}
		for (int i = 0; i < root->_keys.size(); i++) {
			if (key < root->_keys[i]) {
				return find_node_to_ins(root->_children[i], key);
			}
		}
		return find_node_to_ins(root->_children[child_size - 1], key);
	}


	bool insert(T key, BTreeNode<T>* node = nullptr) {
		BTreeNode<T>* to_ins = nullptr;
		if (!node)
			to_ins = find_node_to_ins(_root, key);
		else
			to_ins = node;
		if (to_ins->_keys.size() != 2 * _t - 1) {
			return to_ins->insert(key);
		}
		split_node(to_ins);
		to_ins = find_node_to_ins(_root, key);
		return to_ins->insert(key);
	}

	//insert end

	//print start

	void help_print(BTreeNode<T>* node, int lvl) {
		for (int i = 0; i < lvl; i++) {
			cout << "|";
		}
		for (const auto val : node->_keys) {
			cout << val << " ";
		}
		cout << "\t";
		for (const auto n : node->_children) {
			help_print(n, lvl + 1);
		}
	}

	void print() {
		help_print(_root, 0);
		cout << endl;
	}

	//print end
};