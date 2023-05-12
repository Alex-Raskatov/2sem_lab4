#include "linked_list.h"
#include <cstddef>

union hash_union {
    int a;
    unsigned b;
};

unsigned hash(int key) {
    hash_union h = {key};
    return h.b;
}

struct hash_table {
    LinkedList **table = nullptr;
    float load_factor = 0;
    std::size_t size = 0;
};

hash_table table_new(std::size_t size = 100) {
    LinkedList **table = new LinkedList*[size];
    for (std::size_t i = 0; i < size; i++) {
        table[i] = nullptr;
    }
    return  hash_table{table, 0.f, size};
}

void erase_table(hash_table &Table) {
    for (std::size_t i = 0; i < Table.size; i++) {
        erase(Table.table[i]);
        Table.table[i] = nullptr;
    }
    Table.load_factor = 0.f;
}

bool table_is_empty (hash_table const &Table) {
    return Table.load_factor == 0;
}

bool contains_element (hash_table const &Table, int key) {
    unsigned idx = hash(key) % Table.size;
    LinkedList *head = Table.table[idx];
    bool found = false;
    while (nullptr != head && !found) {
        found = (head->data == key);
        head = head->next;
    }
    return found;
}

void add_element(hash_table &Table, int key) {
    unsigned idx = hash(key) % Table.size;
    LinkedList *head = Table.table[idx];
    bool found = false;
    while (nullptr != head && !found) {
        found = (head->data == key);
        head = head->next;
    }
    if (!found) {
        Table.table[idx] = insert_after(head, key);
        Table.load_factor += 1.f/Table.size;
    }
}

void remove_element(hash_table &Table, int key) {
    unsigned idx = hash(key) % Table.size;
    Table.table[idx] = remove_value(Table.table[idx], key);
    Table.load_factor -= 1.f/Table.size;
}

void expand_table(hash_table &Table, std::size_t new_size) {
    hash_table new_table = table_new(new_size);
    for (std::size_t i = 0; i < Table.size; i++) {
        LinkedList *head = Table.table[i];
        while (head != nullptr) {
            add_element(new_table, head->data);
            head = head->next;
        }
    }
    erase_table(Table);
    Table = new_table;
}

