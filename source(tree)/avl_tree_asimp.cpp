#include <iostream>
#include "AVL_tree_set.h"
#include <random>
#include <fstream>
#include <chrono>

int main() {
    std::ofstream file("data.txt");
    Set new_set = set_new();
    Set &set = new_set;

    int seed = 1003;
    std::default_random_engine rnd(seed);
    std::uniform_int_distribution<int> dstr(1, 10000000);

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    int start = 0, stop = 10000000, step = 1;

    for (int i = start; i < stop; i += step) {
        auto begin = std::chrono::steady_clock::now();
        set_insert(set, dstr(rnd));
        auto end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        if (i % 1000 == 0 and i > 10000)
            file << i << " " << time_span.count() << '\n';
    }

    file.close();
    set_erase(set);
    return 0;
}