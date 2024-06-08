#pragma once
#include<iostream>
#include <random>
#include <string>
#include <chrono>
#include <cstdint>

using namespace std;

template<typename T>
class Node {
public:
    T data;
    Node<T>* left;
    Node<T>* right;
    Node(T value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

template<typename T>
class BinaryTree {
public:
    BinaryTree() {
        _root = nullptr;
    }

    ~BinaryTree() {
        clear(_root);
    }

    void print() {
        print(_root);
        std::cout << std::endl;
    }

    bool insert(T value) {
        return insert(_root, value);
    }

    bool contains(T value) {
        return contains(_root, value);
    }

    bool erase(T value) {
        return erase(_root, value);
    }

    Node<T>* get_root() const {
        return _root;
    }

    bool find(T value) {
        return find(_root, value);
    }

private:
    Node<T>* _root;

    Node<T>* copy(Node<T>* node) {
        if (node) {
            Node<T>* new_node = new Node<T>(node->data);
            new_node->left = copy(node->left);
            new_node->right = copy(node->right);
            return new_node;
        }
        return nullptr;
    }

    bool insert(Node<T>*& node, T value) {

        if (contains(value))
            return false;

        if (node == nullptr) {
            node = new Node<T>(value);
            return true;
        }
        if (value < node->data) {
            return insert(node->left, value);
        }
        else if (value > node->data) {
            return insert(node->right, value);
        }
        return false;
    }

    void print(Node<T>* node) {
        if (node) {
            print(node->left);
            std::cout << node->data << " ";
            print(node->right);
        }
    }

    void clear(Node<T>* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    bool contains(Node<T>* node, T value) {
        if (node == nullptr) {
            return false;
        }
        if (value < node->data) {
            return contains(node->left, value);
        }
        else if (value > node->data) {
            return contains(node->right, value);
        }
        return true;
    }

    bool erase(Node<T>*& node, T value) {
        if (node == nullptr) {
            return false;
        }
        if (value < node->data) {
            return erase(node->left, value);
        }
        else if (value > node->data) {
            return erase(node->right, value);
        }
        else {
            if (node->left == nullptr) {
                Node<T>* temp = node->right;
                delete node;
                node = temp;
            }
            else if (node->right == nullptr) {
                Node<T>* temp = node->left;
                delete node;
                node = temp;
            }
            else {
                Node<T>* temp = node->right;
                while (temp->left) {
                    temp = temp->left;
                }
                node->data = temp->data;
                erase(node->right, temp->data);
            }
            return true;
        }
    }
};
