#include "btree.cpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(SetTests, NodeCheck) {
	BTree<int> a(2);
	a.insert(2);
	a.insert(1);
	a.insert(3);
	a.insert(0);
}