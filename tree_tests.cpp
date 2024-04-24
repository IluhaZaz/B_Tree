#include "btree.cpp"
#include <gtest/gtest.h>
#include <iostream>

using namespace std;

TEST(BTreeTests, InsertCheck) {
	vector<int> v;
	v.push_back(3);
	v.push_back(0);
	v.push_back(1);
	v.push_back(3);
	v.push_back(5);
	v.push_back(2);
	v.push_back(6);
	v.push_back(4);
	v.push_back(8);
	v.push_back(9);
	v.push_back(7);
	v.push_back(-2);
	v.push_back(-1);
	v.push_back(-2);
	v.push_back(3);
	v.push_back(-3);
	BTree<int> a(3);
	for (auto i: v) {
		a.insert(i);
		a.print();
	}
}

TEST(BTreeTests, InsertCheck2) {
	vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	BTree<int> a(2);
	for (auto i : v) {
		a.insert(i);
		a.print();
	}
	v.clear();
	for (int i = 0; i < 10; i++)
		v.push_back(-i);

	for (auto i : v) {
		a.insert(i);
		a.print();
	}
}

TEST(BTreeTests, FindCheck) {
	vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	BTree<int> a(2);
	for (auto i : v) {
		a.insert(i);
	}
	for (int i = 0; i < 10; i++)
		EXPECT_FALSE(a.find(i) == nullptr);
	EXPECT_EQ(a.find(-3), nullptr);
	EXPECT_EQ(a.find(10), nullptr);
	EXPECT_EQ(a.find(-221), nullptr);
	EXPECT_EQ(a.find(90), nullptr);
}

TEST(BTreeTests, ContainsCheck) {
	vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	BTree<int> a(2);
	for (auto i : v) {
		a.insert(i);
	}
	for (int i = 0; i < 10; i++)
		EXPECT_TRUE(a.contains(i));
	EXPECT_FALSE(a.contains(-10));
	EXPECT_FALSE(a.contains(90));
	EXPECT_FALSE(a.contains(-21));
	EXPECT_FALSE(a.contains(10));
}

TEST(BTreeTests, RemoveCheck) {
	vector<int> v;
	for (int i = 0; i < 10; i++)
		v.push_back(i);
	BTree<int> a(3);
	for (auto i : v) {
		a.insert(i);
	}
	v.clear();
	for (int i = 0; i < 10; i++)
		v.push_back(-i);

	for (auto i : v) {
		a.insert(i);
	}
	a.print();
	a.remove(-8);
	a.print();
	a.remove(-5);
	a.print();
	a.remove(3);
	a.print();
	a.remove(-2);
	a.print();
	a.remove(9);
	a.print();
	a.remove(4);
	a.print();
}

TEST(BTreeTests, RemoveCheck2) {
	vector<int> v;
	for (int i = 0; i < 15; i++)
		v.push_back(i);
	BTree<int> a(2);
	for (auto i : v) {
		a.insert(i);
	}
	a.print();
	a.remove(2);
	a.print();
}