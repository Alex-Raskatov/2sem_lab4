#include "AVL_tree.h"

struct Set {
    AVL_tree *root;
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