//
// Created by caiop on 11/08/2023.
//
#include <vector>
#include "utils.cpp"

void bubbleSortWhile(std::vector<int> &v) {
    unsigned int n = v.size();
    bool mudou;
    do {
        mudou = false;
        for (int i = 1; i < n; ++i) {
            if (v[i - 1] > v[i]) {
                auto aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
                mudou = true;
            }
        }
    } while (mudou);
}

void bubbleSortFor(std::vector<int> &v) {
    unsigned int n = v.size();
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n; ++i) {
            if (v[i - 1] > v[i]) {
                auto aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
            }
        }
    }
}

void bubbleSortOptimized1(std::vector<int> &v) {
    unsigned int n = v.size();
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n - j; ++i) {
            if (v[i - 1] > v[i]) {
                auto aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
            }
        }
    }
}

void bubbleSortOptimized2(std::vector<int> &v) {
    unsigned int n, j, i, pos_ult_inv, lim_dir;
    n = v.size();
    lim_dir = n;
    for (j = 0; j < n; ++j) {
        pos_ult_inv = 0;
        for (i = 1; i < lim_dir or i < n - j; ++i) {
            if (v[i - 1] > v[i]) {
                auto aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
                pos_ult_inv = i;
            }
        }
        lim_dir = pos_ult_inv;
    }
}

int main() {
//    std::unsorted_vector<int> vector;
//    unsigned int size = 100000;
//    std::cout << "Bubble Sort using while" << '\n';
//    vector = generateRandomVector(size);
//    printVector(vector);
//    bubbleSortWhile(vector);
//    printVector(vector);
//
//    std::cout << "Bubble Sort using for" << '\n';
//    vector = generateRandomVector(size);
//    printVector(vector);
//    bubbleSortFor(vector);
//    printVector(vector);
//
//    std::cout << "Bubble Sort Optimizing 1" << '\n';
//    vector = generateRandomVector(size);
//    printVector(vector);
//    bubbleSortOptimized1(vector);
//    printVector(vector);
//
//    std::cout << "Bubble Sort Optimizing 2" << '\n';
//    vector = generateRandomVector(size);
//    printVector(vector);
//    bubbleSortOptimized2(vector);
//    printVector(vector);

    unsigned int size = 50000;
    std::cout << "Tamanho: " << size << '\n';

//    std::cout << "Bubble Sort using while:\n";
//    calculateSortingFunctionTime(bubbleSortWhile, unsorted_vector, false);
//    std::cout << "Bubble Sort using for:\n";
//    calculateSortingFunctionTime(bubbleSortFor, unsorted_vector, false);
    std::cout << "Bubble Sort Optimizing 1:\n";
    calculateSortingFunctionTime(bubbleSortOptimized1, size, false);
    std::cout << "Bubble Sort Optimizing 2:\n";
    calculateSortingFunctionTime(bubbleSortOptimized2, size, false);

    return 0;
}