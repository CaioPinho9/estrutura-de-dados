//
// Created by caiop on 11/08/2023.
//
#include <cstdlib>
#include <vector>
#include <iostream>
#include <chrono>

void printVector(std::vector<int> &v) {
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

std::vector<int> generateRandomVector(unsigned int vector_size) {
    std::vector<int> vector = {};
    for (int i = 0; i < vector_size; ++i) {
        auto n = rand() % 10;
        vector.push_back(n);
    }
    return vector;
}

void knuthShuffle(std::vector<int> &v) {
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

void calculateSortingFunctionTime(
        void (*sortingFunction)(std::vector<int> &),
        std::vector<int> vector,
        bool printVectors
) {
    if (printVectors) printVector(vector);

    auto start = std::chrono::system_clock::now();
    sortingFunction(vector);
    auto end = std::chrono::system_clock::now();

    // Calculate the duration in milliseconds
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    if (durationMs >= 1000) {
        // Convert duration to seconds if it's longer than one second
        double duration_sec = static_cast<double>(durationMs) / 1000.0;
        std::cout << duration_sec << "s\n\n";
    } else {
        std::cout << durationMs << "ms\n\n";
    }

    if (printVectors) printVector(vector);
}