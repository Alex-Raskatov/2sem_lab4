#include <iostream>
#include "AVL_tree_set.h"
#include <random>

//insert and contains
bool test1 (Set &test_set) {

    int seed = 1001;
    std::default_random_engine rnd(seed);
    std::uniform_int_distribution<int> dstr(1, 1000);
    int a[100];
    for (int i = 0; i < 10; i++) {
        a[i] = dstr(rnd);
        set_insert(test_set, a[i]);
    }

    for (int i = 0; i < 10; i++) {
        if (!set_contains(test_set, a[i])) return false;
        if (set_contains(test_set, -a[i])) return false;
    }

    return true;
}

bool test2 (Set &test_set) {

    int seed = 1001;
    std::default_random_engine rnd(seed);
    std::uniform_int_distribution<int> dstr(1, 1000);
    int a[100];
    for (int i = 0; i < 10; i++) {
        a[i] = dstr(rnd);
        set_insert(test_set, a[i]);
    }

    for (int i = 0; i < 10; i++) {
        set_remove(test_set, a[i]);
        set_remove(test_set, -a[i]);
        if (set_contains(test_set, a[i]))
            return false;
    }

    return set_is_empty(test_set);
}



int main() {
    Set set = set_new();                                                                                                //создание пустого
    Set &test_set = set;
    std::cout << "1: " << ((set_is_empty( test_set) == true) ? "OK" : "ERROR") << std::endl;                        //проверка на пустоту пустого
    std::cout << "2: " << (test1(test_set) ? "OK" : "ERROR") << std::endl;                                            //проверка вставки и поиска
    std::cout << "3: " << (!set_is_empty( test_set) ? "OK" : "ERROR") << std::endl;                                 //проверка на пустоту непустого
    std::cout << "4: " << (set_contains(test_set, set_example(test_set)) ? "OK" : "ERROR") << std::endl;   //проверка выбора элемента
    set_erase(test_set);                                                                                           //опустошение
    std::cout << "5: " << (set_is_empty( test_set) ? "OK" : "ERROR") << std::endl;                                  //проверка на пустоту после опустошения (т.е. проверка опустошения)
    std::cout << "6: " << (test2(test_set) ? "OK" : "ERROR") << std::endl;                                            //проверка удаления по значению
    //std::cout << "7: " << (set_contains(test_set, set_example(test_set)) ? "OK" : "ERROR") << std::endl;   //проверка выбора элемента из пустого
    return 0;
}