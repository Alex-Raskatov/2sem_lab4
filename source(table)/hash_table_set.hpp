#include "hash_table.hpp"

struct Set {
    hash_table Table;
};

Set set_new() {
    return Set{table_new()};
}

bool set_is_empty(Set const &set) {
    return table_is_empty(set.Table);
}

int set_example(Set const &set) {
    for (unsigned i = 0; i < set.Table.size; i++)
        if (set.Table.table[i] != nullptr)
            return set.Table.table[i]->data;
    return 0;
}

bool set_contains(Set const &set, int key) {
    return contains_element(set.Table, key);
}

Set& set_insert(Set &set, int key) {
    add_element(set.Table, key);
    if (set.Table.load_factor >= 0.6)
        expand_table(set.Table, set.Table.size*6 + 1);
    return set;
}

Set& set_remove(Set &set, int key) {
    remove_element(set.Table, key);
    if (set.Table.load_factor < 0.0000001) erase_table(set.Table);
    return set;
}

Set& set_erase(Set &set) {
    erase_table(set.Table);
    return set;
}