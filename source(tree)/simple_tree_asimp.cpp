#include <iostream>
#include "simple_tree_set.h"
#include <random>
#include <fstream>
#include <chrono>

int main() {
    std::ofstream file("simple_tree_insert_random_data.txt");
    Set new_set = set_new();
    Set &set = new_set;

    int seed = 1003;
    std::default_random_engine rnd(seed);
    std::uniform_int_distribution<int> dstr(1, 10000);

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();

    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    int start = 0, stop = 1000000, step = 1;

    for (int i = start; i < stop; i += step) {
        auto begin = std::chrono::steady_clock::now();
        set_insert(set, dstr(rnd));
        auto end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

        if (i % 1000 == 0 and i > 10)
            file << i << " " << time_span.count() << '\n';
    }

    file.close();
    set_erase(set);
    return 0;
}
