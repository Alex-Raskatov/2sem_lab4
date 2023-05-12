#include <iostream>
#include "simple_tree.h"

struct Set {
    Tree *root;
};

Set set_new() {
    return Set{nullptr};
}

bool set_is_empty(Set const &set) {
    return emptyNode(set.root);
}

int set_example(Set const &set) {
    return exampleNode(set.root);
}

bool set_contains(Set const &set, int key) {
    return containsNode(set.root, key);
}

Set& set_insert(Set &set, int key) {
    set.root = insertNode(set.root, key);
    return set;
}

Set& set_remove(Set &set, int key) {
    set.root = deleteNode(set.root, key);
    return set;
}

Set& set_erase(Set &set) {
    erase(set.root);
    set.root = nullptr;
    return set;
}

void printPreOrder(Tree *root) {
  if (root != nullptr) {
    std::cout << root->key << " ";
    printPreOrder(root->left);
    printPreOrder(root->right);
  }
}