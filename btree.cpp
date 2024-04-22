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
		sort(_keys.begin(), _keys.end());
		return true;
	}

	void remove_child(BTreeNode<T>* child) {
		for (int i = 0; i < _children.size(); i++) {
			if (child == _children[i]) {
				_children.erase(_children.begin() + i);
			}
		}
	}

	void add_child(BTreeNode<T>* child) {
		bool inserted = 0;
		for (int i = 0; i < _children.size(); i++) {
			if (child->_keys[0] < _children[i]->_keys[0]) {
				_children.insert(_children.begin() + i, child);
				inserted = true;
				break;
			}
		}
		if (!inserted)
			_children.push_back(child);

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
			left->add_child(_children[i]);
		}
		for (auto& val : left->_children) {
			val->_parent = left;
		}


		BTreeNode<T>* right = new BTreeNode<T>();
		right->_parent = _parent;
		for (int i = key_size / 2 + 1; i < key_size; i++) {
			right->insert(_keys[i]);
		}

		for (int i = child_size / 2; i < child_size; i++) {
			right->add_child(_children[i]);
		}
		for (auto& val : right->_children) {
			val->_parent = right;
		}
		return pair<BTreeNode<T>*, BTreeNode<T>*>(left, right);
	}

	void remove(T key) {
		for (int i = 0; i < _keys.size(); i++) {
			if (_keys[i] == key) {
				_keys.erase(_keys.begin() + i);
				return;
			}
		}
	}

	pair<BTreeNode<T>*, BTreeNode<T>*> find_neighbours() {
		T val = _keys[0];
		int i = 0;
		int ch_size = _parent->_children.size();
		if(ch_size == 1)
			return pair(nullptr, nullptr);
		for (; i < ch_size; i++) {
			if (_parent->_children[i]->contains(val))
				break;
		}
		if (i == 0) {
			if (ch_size >= 2)
				return pair(nullptr, _parent->_children[i + 1]);
			return pair(nullptr, nullptr);
		}
		if (i == ch_size - 1) {
			if (ch_size >= 2)
				return pair(_parent->_children[i - 1], nullptr);
			return pair(nullptr, nullptr);
		}
		return pair(_parent->_children[i - 1], _parent->_children[i + 1]);
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

	//contains
	bool help_contains(T key, BTreeNode<T>* node) {
		if (node->_keys.empty())
			return false;
		for (int i = 0; i < node->_keys.size(); i++) {
			if (node->_keys[i] == key)
				return true;
			if (key < node->_keys[i]) {
				if(!node->_children.empty())
					return help_contains(key, node->_children[i]);
				return false;
			}
		}
		if (!node->_children.empty())
			return help_contains(key, node->_children.back());
		return false;
	}

	bool contains(T key) {
		return help_contains(key, _root);
	}
	//
	//split_node 
	void split_node(BTreeNode<T>* node) {
		if (node->_parent) {
			if (node->_parent->_keys.size() == 2 * _t - 1) {
				split_node(node->_parent);
			}
		}
		auto nodes = node->split_node();
		BTreeNode<T>* left = nodes.first;
		BTreeNode<T>* right = nodes.second;
		BTreeNode<T>* parent = node->_parent;
		bool new_root = false;
		if (!parent) {
			parent = new BTreeNode<T>();
			new_root = true;
		}
		parent->add_child(left);
		parent->add_child(right);
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
		if (contains(key))
			return false;
		BTreeNode<T>* to_ins = nullptr;
		if (!node)
			to_ins = find_node_to_ins(_root, key);
		else
			to_ins = node;
		if (to_ins->_keys.size() != 2 * _t - 1) {
			return to_ins->insert(key);
		}
		split_node(to_ins);
		if (node) {
			return insert(key, node->_parent);
		}
		return insert(key);
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

	void help_print_plus(BTreeNode<T>* node, int lvl) {
		for (int i = 0; i < lvl; i++) {
			cout << "|";
		}
		if (node->_parent) {
			cout << "(";
				for (auto val : node->_parent->_keys) {
					cout << val << " ";
				}
			cout << ")";
		}
		for (const auto val : node->_keys) {
			cout << val << " ";
		}
		cout << "\t";
		for (const auto n : node->_children) {
			help_print_plus(n, lvl + 1);
		}
	}

	void print(bool with_parents = true) {
		if (with_parents)
			help_print_plus(_root, 0);
		else
			help_print(_root, 0);
		cout << endl;
	}

	//print end

	//find
	T* help_find(BTreeNode<T>* node, T key) const{
		if (!node->contains(key) && node->_children.empty())
			return nullptr;
		int i = 0;
		for (; i < node->_keys.size(); i++) {
			if (key == node->_keys[i])
				return &node->_keys[i];
			if (key < node->_keys[i]) {
				return help_find(node->_children[i], key);
			}
		}
		return help_find(node->_children[i], key);
	}

	T* find(T key) const{
		return help_find(_root, key);
	}
	//
	//remove start
	BTreeNode<T>* help_find_node(BTreeNode<T>* node, T key) const {
		if (!node->contains(key) && node->_children.empty())
			return nullptr;
		int i = 0;
		for (; i < node->_keys.size(); i++) {
			if (key == node->_keys[i])
				return node;
			if (key < node->_keys[i]) {
				return help_find_node(node->_children[i], key);
			}
		}
		return help_find_node(node->_children[i], key);
	}

	BTreeNode<T>* find_node(T key) {
		return help_find_node(_root, key);
	}

	BTreeNode<T>* merge_nodes(BTreeNode<T>* left, BTreeNode<T>* right, bool with_children = false) {
		BTreeNode<T>* node = new BTreeNode<T>();
		for (const auto val : left->_keys) {
			node->_keys.push_back(val);
		}
		for (const auto val : right->_keys) {
			node->_keys.push_back(val);
		}
		if (with_children) {
			for (const auto child : left->_children) {
				node->_children.push_back(child);
			}
			for (const auto child : right->_children) {
				node->_children.push_back(child);
			}
		}
		return node;
	}


	void remove_from_leaf(T key, BTreeNode<T>* node) {
		if (node->_keys.size() != _t - 1) {
			node->remove(key);
			return;
		}
		auto pair = node->find_neighbours();
		BTreeNode<T>* left = pair.first;
		BTreeNode<T>* right = pair.second;
		if (right) {
			int par_ind = 0;
			for (; par_ind < node->_parent->_keys.size(); par_ind++) {
				if (key < node->_parent->_keys[par_ind])
					break;
			}
			if (right->_keys.size() != _t - 1) {
				T temp_r = right->_keys[0];
				right->remove(temp_r);
				T temp_p = node->_parent->_keys[par_ind];
				node->_parent->remove(temp_p);
				node->_parent->insert(temp_r);
				node->remove(key);
				node->insert(temp_p);
				return;
			}
			BTreeNode<T>* new_node = merge_nodes(node, right);
			new_node->remove(key);
			new_node->_parent = node->_parent;
			new_node->insert(node->_parent->_keys[par_ind]);
			node->_parent->remove(node->_parent->_keys[par_ind]);
			node->_parent->add_child(new_node);
			node->_parent->remove_child(right);
			node->_parent->remove_child(node);
			return;
		}
		if (left) {
			int par_ind = 0;
			T temp_l = left->_keys.back();
			for (; par_ind < node->_parent->_keys.size(); par_ind++) {
				if (temp_l < node->_parent->_keys[par_ind])
					break;
			}
			if (left->_keys.size() != _t - 1) {
				left->remove(temp_l);
				T temp_p = node->_parent->_keys[par_ind];
				node->_parent->remove(temp_p);
				node->_parent->insert(temp_l);
				node->remove(key);
				node->insert(temp_p);
				return;
			}
			BTreeNode<T>* new_node = merge_nodes(left, node);
			new_node->remove(key);
			new_node->_parent = node->_parent;
			new_node->insert(node->_parent->_keys[par_ind]);
			node->_parent->remove(node->_parent->_keys[par_ind]);
			node->_parent->add_child(new_node);
			node->_parent->remove_child(left);
			node->_parent->remove_child(node);
		}
	}

	void remove_from_middle_node(T key, BTreeNode<T>* node) {
		int pos = 0;
		for (; pos < node->_keys.size(); pos++) {
			if (node->_keys[pos] == key)
				break;
		}
		BTreeNode<T>* left = node->_children[pos];
		BTreeNode<T>* right = node->_children[pos + 1];

		if (left->_keys.size() != _t - 1) {
			node->remove(key);
			node->insert(left->_keys.back());
			return;
		}
		if (right->_keys.size() != _t - 1) {
			node->remove(key);
			node->insert(left->_keys[0]);
			return;
		}
		node->remove(key);
		BTreeNode<T>* new_node = merge_nodes(left, right, true);
		node->remove_child(left);
		node->remove_child(right);
		node->add_child(new_node);
	}

	void remove(T key) {
		BTreeNode<T>* to_del = find_node(key);
		if(!to_del)
			return;
		if (to_del == _root) {

		}
		if(to_del->_children.empty()) {
			remove_from_leaf(key, to_del);
			return;
		}
		remove_from_middle_node(key, to_del);
	}

	//remove end
};