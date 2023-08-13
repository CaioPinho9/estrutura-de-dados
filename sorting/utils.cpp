//
// Created by caiop on 11/08/2023.
//
#include <cstdlib>
#include <vector>
#include <iostream>
#include <chrono>

void print_vector(std::vector<int> &v) {
    unsigned int n = v.size();
    for (int i = 0; i < n; ++i) {
        auto item = v[i];
        std::cout << item;
        if (i != n - 1) {
            std::cout << ',' << ' ';
        }
    }
    std::cout << '\n' << '\n';

}

std::vector<int> generate_random_vector(unsigned int vector_size) {
    std::vector<int> vector = {};
    for (int i = 0; i < vector_size; ++i) {
        auto n = rand() % 1000;
        vector.push_back(n);
    }
    return vector;
}

void knuth_shuffle(std::vector<int> &v) {
    srand(time(NULL)); // A different seed each time
    int n = v.size();
    for (int i = --n; i > 0; i--) {
        // Pick a random index from 0 to i:
        int j = rand() % (i + 1);

        //
        auto aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}

void calculate_sorting_function_time(
        void (*sorting_function)(std::vector<int> &),
        unsigned int size,
        bool print_vectors
) {
    std::vector<int> vector = generate_random_vector(size);
    if (print_vectors) print_vector(vector);

    auto start = std::chrono::system_clock::now();
    sorting_function(vector);
    auto end = std::chrono::system_clock::now();

    // Calculate the duration in milliseconds
    auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (duration_ms >= 1000) {
        // Convert duration to seconds if it's longer than one second
        double duration_sec = static_cast<double>(duration_ms) / 1000.0;
        std::cout << duration_sec << "s\n\n";
    } else {
        std::cout << duration_ms << "ms\n\n";
    }

    if (print_vectors) print_vector(vector);
}