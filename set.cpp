#pragma once
#include <algorithm> 
#include <iostream>
#include <vector>
#define max(a,b) (((a) > (b)) ? (a) : (b))

struct Node {
	int _val;
	Node* _left;
	Node* _right;

	Node(int val) :_val(val), _left(nullptr), _right(nullptr) {};
	Node(int val, Node* left, Node* right) :_val(val), _left(left), _right(right) {};
};

int compare(const void* x1, const void* x2)
{
	return (*(int*)x1 - *(int*)x2);
}

bool help_erase(Node*& node, int value) {
	if (node == nullptr) {
		return false;
	}
	if (value < node->_val) {
		return help_erase(node->_left, value);
	}
	else if (value > node->_val) {
		return help_erase(node->_right, value);
	}
	else {
		if (node->_left == nullptr) {
			Node* temp = node->_right;
			delete node;
			node = temp;
		}
		else if (node->_right == nullptr) {
			Node* temp = node->_left;
			delete node;
			node = temp;
		}
		else {
			Node* temp = node->_right;
			while (temp->_left) {
				temp = temp->_left;
			}
			node->_val = temp->_val;
			help_erase(node->_right, temp->_val);
		}
		return true;
	}
}
	

bool help_insert(int key, Node*& root) {
	if (root == nullptr) {
		root = new Node(key);
		return true;
	}
	if (root->_val == key) {
		return false;
	}
	if (key < root->_val) {
		help_insert(key, root->_left);
	}
	else {
		help_insert(key, root->_right);
	}
}

size_t remove_duplicates(int* data, size_t len) {
	int j = 1;
	for (int i = 1; i < len; i++) {
		if (data[i] != data[i - 1]) {
			data[j] = data[i];
			j++;
		}
	}
	return j;
}

size_t get_middle(size_t len) {
	if (len == 1)
		return 1;
	return (int)(len / 2);
}


void get_data(const Node* root, int*& buf) {
	if (root == nullptr) {
		return;
	}
	*buf = root->_val;
	buf++;
	get_data(root->_left, buf);
	get_data(root->_right, buf);
}

void remove_nodes(Node* root) {
	if (root == nullptr) {
		return;
	}
	remove_nodes(root->_left);
	remove_nodes(root->_right);
	delete root;
}


void help_print(Node* root) {

	if (root != nullptr) {
		help_print(root->_left);
		std::cout << root->_val << " ";
		help_print(root->_right);
	}
}


Node* copy_root(Node* root) {
	if (root) {
		Node* new_node = new Node(root->_val);
		new_node->_left = copy_root(root->_left);
		new_node->_right = copy_root(root->_right);
		return new_node;
	}
	return nullptr;
}

Node* find_node_parent(Node* root, int key) {
	if (root->_val == key) {
		return nullptr;
	}
	if (root->_left && key < root->_val) {
		if (root->_left->_val == key)
			return root;
		if (key < root->_left->_val)
			find_node_parent(root->_left, key);
		else if (root->_left) {
			if (key > root->_right->_val) {
				find_node_parent(root->_right, key);
			}
		}
	}
	else if (root->_right && key > root->_val) {
		if (root->_right->_val == key)
			return root;
		if (key > root->_right->_val)
			find_node_parent(root->_right, key);
	}
}

Node* find_node_and_parent(Node* root, int key, Node*& parent) {
	if (root == nullptr) {
		return nullptr;
	}
	if (root->_val == key) {
		return root;
	}
	parent = root;
	if (key < root->_val) {
		find_node_and_parent(root->_left, key, parent);
	}
	else {
		find_node_and_parent(root->_right, key, parent);
	}
}

class Set {
private:
	Node* _root;
public:
	size_t _len;
	Set() : _root(nullptr), _len(0) {};
	Set(const int* data, size_t len) {
		_root = nullptr;

		int l = 0;

		for (int i = 0; i < len; i++) {
			l += (int)this->insert(data[i]);
		}
		_len = l;
	}

	Set(const Set& s) {
		_root = copy_root(s._root);
		_len = s._len;
	}

	void get_data(const Node* root, int*& buf) {
		if (root == nullptr) {
			return;
		}
		*buf = root->_val;
		buf++;
		get_data(root->_left, buf);
		get_data(root->_right, buf);
	}

	int get_num_of_nodes(Node* root, int*& num) {
		if (root == nullptr) {
			return 0;
		}
		*num += 1;
		get_num_of_nodes(root->_left, num);
		get_num_of_nodes(root->_right, num);
	}

	Set(Node* root) {
		int* nums = new int(0);
		get_num_of_nodes(root, nums);
		_len = *nums;
		_root = copy_root(root);
	}

	~Set() {
		remove_nodes(_root);
	}


	void print() {
		std::cout << _root->_val << " ";
		help_print(_root->_left);
		help_print(_root->_right);
	}

	bool help_contains(Node* root, int key) {
		if (root == nullptr)
			return false;
		if (root->_val == key)
			return true;
		return help_contains(root->_left, key) || help_contains(root->_right, key);
	}

	bool contains(int key) {
		return help_contains(_root, key);
	}

	void operator=(const Set& s) {
		this->_len = s._len;
		Node* root = copy_root(s._root);
		this->_root = s._root;
	}

	bool insert(int key) {
		if (help_insert(key, _root)) {
			_len++;
			return true;
		}
		return false;
	}

	int* get_array() {
		int* buf = new int[_len];
		get_data(_root, buf);
		buf -= _len;
		qsort(buf, _len, sizeof(int), compare);
		return buf;
	}

	bool erase(int key) {
		return help_erase(_root, key);
	}
};

std::vector<int> get_copies(std::vector<int> data) {
	size_t len = data.size();
	Set s(data.data(), len);
	int* copies = new int[len - s._len];
	int j = 0;
	for (int i = 0; i < len; i++) {
		if (s.contains(data[i])) {
			s.erase(data[i]);
		}
		else {
			copies[j] = data[i];
			j++;
		}
	}
	std::vector<int>ans;
	for (int i = 0; i < j; i++)
		ans.push_back(copies[i]);
	return ans;
}

