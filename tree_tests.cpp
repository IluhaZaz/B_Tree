#include "btree.cpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(BTreeTests, InsertCheck) {
	BTree<int> a(2);
	for (int i = 0; i < 10; i++) {
		a.insert(i);
		a.print();
	}
}