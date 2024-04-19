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
			if (key < root->_keys[i]) {
				return find_node_to_ins(root->_children[i], key);
			}
		}
		return find_node_to_ins(root->_children[child_size - 1], key);
	}

	pair<BTreeNode<T>*, BTreeNode<T>*> split_node(BTreeNode<T>* node) {
		BTreeNode<T>* left = new BTreeNode<T>();
		left->_parent = node->_parent;
		int key_size = node->_keys.size();
		for (int i = 0; i < key_size/2; i++) {
			left->insert(node->_keys[i]);
		}
		int child_size = node->_children.size();
		for (int i = 0; i < child_size / 2; i++) {
			left->_children.push_back(node->_children[i]);
		}
		for (auto& val : left->_children) {
			val->_parent = left;
		}


		BTreeNode<T>* right = new BTreeNode<T>();
		right->_parent = node->_parent;
		for (int i = key_size/2 + 1; i < key_size; i++) {
			right->insert(node->_keys[i]);
		}

		for (int i = key_size / 2; i < child_size; i++) {
			right->_children.push_back(node->_children[i]);
		}
		for (auto& val : right->_children) {
			val->_parent = right;
		}
		return pair<BTreeNode<T>*, BTreeNode<T>*>(left, right);
	}


	bool insert(T key) {
		//empty tree
		if (!_root) {
			_root = new BTreeNode<T>();
			_root->insert(key);
			return true;
		}

		BTreeNode<T>* to_ins = find_node_to_ins(_root, key);
		if (!to_ins)
			return false;
		if (to_ins->_keys.size() != _t * 2 - 1) {
			return to_ins->insert(key);
		}
		//to_ins full
		auto nodes = split_node(to_ins);
		BTreeNode<T>* left = nodes.first;
		BTreeNode<T>* right = nodes.second;
		//	to_ins is root
		if (!left->_parent) {
			_root = new BTreeNode<T>();
			_root->insert(to_ins->_keys[_t - 1]);
			_root->_children.push_back(left);
			_root->_children.push_back(right);
			left->_parent = _root;
			right->_parent = _root;
			return this->insert(key);
		}
		//to_ins parent is not full
		if (to_ins->_parent->_keys.size() != 2 * _t - 1) {
			to_ins->_parent->insert(to_ins->_keys[_t - 1]);
			to_ins->_parent->_children.push_back(left);
			to_ins->_parent->_children.push_back(right);
			to_ins->_parent->remove_child(to_ins);
			return this->insert(key);
		}
		//to_ins parent is full
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