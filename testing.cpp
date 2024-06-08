#include "btree.cpp"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include "bin_tree.cpp"
#include <algorithm>
#include <fstream>


void main() {
	{
		vector<int> sizes{ 10, 250, 500, 1000, 2000, 5000, 7500, 10000, 15000, 20000, 25000, 30000, 35000, 70000 };

		std::ofstream file;
		file.open("C:\\b_tree\\insert.txt");

		for (const auto& size : sizes) {

			BTree<int> b(30);
			auto begin = std::chrono::steady_clock::now();
			for (int i = 0; i < size; i++) {
				b.insert(rand());
			}
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << elapsed_ms << " BTree for " << size << " values" << endl;
			file << elapsed_ms.count() << " ";

			BinaryTree<int> s;
			begin = std::chrono::steady_clock::now();
			for (int i = 0; i < size; i++) {
				s.insert(rand());
			}
			end = std::chrono::steady_clock::now();
			elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << elapsed_ms << " Set for " << size << " values" << endl;
			file << elapsed_ms.count() << " ";

			vector<int> v;
			begin = std::chrono::steady_clock::now();
			for (int i = 0; i < size; i++) {
				v.push_back(rand());
			}
			end = std::chrono::steady_clock::now();
			elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << elapsed_ms << " vector for " << size << " values" << endl;
			file << elapsed_ms.count() << " ";
		}
		file.close();
	}

	{
		std::ofstream file;
		file.open("C:\\b_tree\\search.txt");

		vector<int> sizes{ 10, 250, 500, 1000, 2000, 5000, 7500, 10000, 15000, 20000, 25000, 30000, 35000 };
		for (const auto& size : sizes) {

			BTree<int> b(30);
			BinaryTree<int> s;
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
				b.find(values[i]);
			}
			auto end = std::chrono::steady_clock::now();
			auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << elapsed_ms << " BTree for " << size << " values" << endl;
			file << elapsed_ms.count() << " ";

			begin = std::chrono::steady_clock::now();
			for (int i = 0; i < size; i++) {
				s.contains(values[i]);
			}
			end = std::chrono::steady_clock::now();
			elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << elapsed_ms << " Set for " << size << " values" << endl;
			file << elapsed_ms.count() << " ";

			begin = std::chrono::steady_clock::now();
			for (int i = 0; i < size; i++) {
				std::find(v.begin(), v.end(), values[i]);
			}
			end = std::chrono::steady_clock::now();
			elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
			std::cout << elapsed_ms << " Vector for " << size << " values" << endl;
			file << elapsed_ms.count() << " ";
		}
	}
}
