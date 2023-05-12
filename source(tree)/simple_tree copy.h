struct Tree{
    Tree *left = nullptr;
    Tree *right = nullptr;
    int data;
};

Tree* tree_new() {
    return nullptr;
}

bool tree_is_empty(Tree *root) {
    if (root == nullptr) return true;
    return false;
}

int tree_example(Tree const *root) {
    return root->data;
}

bool tree_conteins(Tree const *root, int key) {
    if (root == nullptr) return false;
    auto tmp = root;
    bool result = false;
    while (tmp != nullptr) {
        if (key > tmp->data) tmp = tmp->left;
        else if (key < tmp->data) tmp = tmp->right;
        else if (key == tmp->data) {
            result = true;
            break;
        }
    }
    return result;
}

Tree* tree_insert (Tree *root, int key) {
    auto new_node = new Tree{nullptr, nullptr, key};
    if (root == nullptr) return new_node;
    if (key < root->data) {
        if (root->right == nullptr) return root->right = new_node;
        return tree_insert(root->right, key);
    }
    else {
        if (root->left == nullptr) return root->left = new_node;
        return tree_insert(root->left, key);
    }
}

Tree* tree_remove (Tree *root, int key) {
    if (tree_conteins(root, key) == false) return root;
    else {
        auto tmp = root;
        auto prev_tmp = root;
        while (true) {
            if (key > tmp->data) tmp = tmp->left;
            else if (key < tmp->data) tmp = tmp->right;
            else if (key == tmp->data) {
                break;
            }
            prev_tmp = tmp;
        }
        if (tmp != root) {
            if (tmp->left == nullptr and tmp->right == nullptr) {
                if (prev_tmp->left == tmp) prev_tmp->left = nullptr;
                if (prev_tmp->right == tmp) prev_tmp->right = nullptr;
                delete tmp;
            }
            else if (tmp->left == nullptr) {
                if (prev_tmp->left == tmp) prev_tmp->left = tmp->right;
                if (prev_tmp->right == tmp) prev_tmp->right = tmp->right;
                delete tmp;
            }
            else if (tmp->right == nullptr) {
                if (prev_tmp->left == tmp) prev_tmp->left = tmp->left;
                if (prev_tmp->right == tmp) prev_tmp->right = tmp->left;
                delete tmp;
            }
            else {
                auto tmp_1 = tmp->left;
                auto prev_tmp_1 = tmp;
                while (tmp_1->right != nullptr) {
                    tmp_1 = tmp_1->right;
                    prev_tmp_1 = prev_tmp_1->right;
                }
                //потомки tmp
                prev_tmp_1->right = nullptr;
                if (prev_tmp->right == tmp) prev_tmp->right = tmp_1;
                if (prev_tmp->left == tmp) prev_tmp->left = tmp_1;
                delete tmp;
            }
        }
        else {
            if (tmp->left == nullptr and tmp->right == nullptr) {
                delete tmp;
                root = nullptr;
            }
            else if (tmp->left == nullptr) {
                root = root->right;
                delete tmp;
            }
            else if (tmp->right == nullptr) {
                root = root->left;
                delete tmp;
            }
            else {
                auto tmp_1 = tmp->left;
                auto prev_tmp_1 = tmp;
                while (tmp_1->right != nullptr) {
                    tmp_1 = tmp_1->right;
                    prev_tmp_1 = prev_tmp_1->right;
                }
                //потомки tmp
                prev_tmp_1->right = nullptr;
                if (prev_tmp->right == tmp) prev_tmp->right = tmp_1;
                if (prev_tmp->left == tmp) prev_tmp->left = tmp_1;
                delete tmp;
            }
        }
    }
    return root;
}

Tree* tree_erase (Tree *root) {
    if (root == nullptr) return nullptr;
    if (root->left != nullptr and root->right != nullptr) {
        tree_erase(root->left);
        tree_erase(root->right);
        root->left = nullptr;
        root->right = nullptr;
    }
    else if (root->left == nullptr and root->right != nullptr) {
        tree_erase(root->right);
        root->left = nullptr;
        root->right = nullptr;
    }
    else if (root->left != nullptr and root->right == nullptr) {
        tree_erase(root->left);
        root->left = nullptr;
        root->right = nullptr;
    }
    delete root;
    return nullptr;
}