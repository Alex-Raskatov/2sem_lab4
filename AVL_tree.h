struct AVL_tree {
    int key;
    AVL_tree *left = nullptr;
    AVL_tree *right = nullptr;
    int height;
};


int height(AVL_tree *node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int max(int a, int b) {
    if (a >= b) return a;
    return b;
}

AVL_tree *newNode(int key) {
    AVL_tree *node = new AVL_tree{key, nullptr, nullptr, 1};
    return node;
}

bool emptyNode(AVL_tree *node) {
    if (node == nullptr)
        return true;
    else
        return false;;
}

int exampleNode (AVL_tree *root) {
    return root->key;
}

bool containsNode(AVL_tree *root, int key) {
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

// правый поворот
AVL_tree *rightRotate(AVL_tree *node) {
    AVL_tree *left_node = node->left;
    AVL_tree *tmp = left_node->right;

    left_node->right = node;
    node->left = tmp;

    node->height = max(height(node->left), height(node->right)) + 1;
    left_node->height = max(height(left_node->left), height(left_node->right)) + 1;

    return left_node;
}

// левый поворот
AVL_tree *leftRotate(AVL_tree *node) {
    AVL_tree *right_node = node->right;
    AVL_tree *tmp = right_node->left;

    right_node->left = node;
    node->right = tmp;

    node->height = max(height(node->left), height(node->right)) + 1;
    right_node->height = max(height(right_node->left), height(right_node->right)) + 1;

    return right_node;
}

int getBalance(AVL_tree *node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}


AVL_tree *insertNode(AVL_tree *node, int key) {
    // поиск места вставки и рекурсивная вставка
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insertNode(node->left, key);
    else if (key > node->key)
        node->right = insertNode(node->right, key);
    else
        return node;

    // балансировка дерева
    node->height = 1 + max(height(node->left),height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVL_tree *minValueNode(AVL_tree *node) {
    AVL_tree *current = node;

    while (current->left != nullptr)
        current = current->left;

    return current;
}

AVL_tree *deleteNode(AVL_tree *root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            AVL_tree *temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            AVL_tree *temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = deleteNode(root->right, temp->key);
        }
    }

    // балансировка дерева
    root->height = 1 + max(height(root->left),
                height(root->right));

    int balance = getBalance(root);
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void erase(AVL_tree *root) {
    if (root->left != nullptr && root->left != nullptr) {
        erase(root->left);
        erase(root->right);
        delete root;
        root = nullptr;
    } else if (root->left != nullptr) {
        erase(root->left);
        delete root;
        root = nullptr;
    } else if (root->right != nullptr) {
        erase(root->right);
        delete root;
        root = nullptr;
    } else {
        delete root;
        root = nullptr;
    }
}

