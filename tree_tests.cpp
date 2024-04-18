#include "btree.cpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(BTreeTests, NodeByIterCheck) {
	vector<int> v;
	for (int i = 0; i < 6; i++) {
		v.push_back(i);
	}
	BTreeNode<int> a(v.begin(), v.begin() + 3);
}

TEST(BTreeTests, InsertCheck) {
	BTree<int> a(2);
	a.insert(2);
	a.insert(1);
	a.insert(3);
	a.insert(0);
	a.insert(0);
	a.print();
}