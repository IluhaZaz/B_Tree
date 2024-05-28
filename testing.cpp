#include "btree.cpp"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "set.cpp"
#include <gtest/gtest.h>
#include <algorithm>


TEST(Tests, InsertCheck) {

	vector<int> sizes{ 10, 250, 500, 1000, 2000, 5000, 7500, 10000, 15000, 20000, 25000, 30000, 35000 };

	for (const auto& size : sizes) {


		BTree<int> b(30);
		auto begin = std::chrono::steady_clock::now();
		for (int i = 0; i < size; i++) {
			b.insert(rand());
		}
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << elapsed_ms << " BTree" << endl;

		Set s;
		begin = std::chrono::steady_clock::now();
		for (int i = 0; i < size; i++) {
			s.insert(rand());
		}
		end = std::chrono::steady_clock::now();
		elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << elapsed_ms << " Set" << endl;

		vector<int> v;
		begin = std::chrono::steady_clock::now();
		for (int i = 0; i < size; i++) {
			v.push_back(rand());
		}
		end = std::chrono::steady_clock::now();
		elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << elapsed_ms << " vector" << endl;
	}
}

TEST(Tests, FindCheck) {

	vector<int> sizes{ 10, 250, 500, 1000, 2000, 5000, 7500, 10000, 15000, 20000, 25000, 30000, 35000 };
	for (const auto& size : sizes) {

		BTree<int> b(30);
		Set s;
		vector<int> v;

		vector<int> values;
		for (int i = 0; i < size; i++) {
			int r = rand();
			b.insert(r);
			s.insert(r);
			v.push_back(r);

			values.push_back(r);
		}

		auto begin = std::chrono::steady_clock::now();
		for (int i = 0; i < size; i++) {
			EXPECT_TRUE(b.find(values[i]));
		}
		auto end = std::chrono::steady_clock::now();
		auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << elapsed_ms << " BTree" << endl;

		begin = std::chrono::steady_clock::now();
		for (int i = 0; i < size; i++) {
			EXPECT_TRUE(s.contains(values[i]));
		}
		end = std::chrono::steady_clock::now();
		elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << elapsed_ms << " Set" << endl;

		begin = std::chrono::steady_clock::now();
		for (int i = 0; i < size; i++) {
			EXPECT_TRUE(std::find(v.begin(), v.end(), values[i]) != v.end());
		}
		end = std::chrono::steady_clock::now();
		elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
		std::cout << elapsed_ms << " Vector" << endl;
	}
}
