#include <iostream>

struct Tree {
    int key;
    Tree *left = nullptr;
    Tree *right = nullptr;
};

Tree *newNode(int key) {
    Tree *node = new Tree{key, nullptr, nullptr};
    return node;
}

bool emptyNode(Tree *node) {
    return node == nullptr;
}

int exampleNode (Tree *root) {
    return root->key;
}

bool containsNode(Tree *root, int key) {
    auto temp = root;
    while (temp != nullptr) {
        if (key < temp->key)
            temp = temp->left;
        else if (key > temp->key)
            temp = temp->right;
        else
            return true;        
    }
    return false;
}

Tree *insertNode(Tree *node, int key) {
    // поиск места вставки и рекурсивная вставка
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    return node;
}

Tree *minValueNode(Tree *node) {
    Tree *current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

Tree *deleteNode(Tree *root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Tree *temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Tree *temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    return root;
}

void erase(Tree *root) {
    if (root != nullptr) {
        erase(root->left);
        erase(root->right);
        delete root;
    }
}
