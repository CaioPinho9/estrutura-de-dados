//
// Created by caiop on 16/08/2023.
//
#include <vector>
#include "utils.cpp"

void selectionSort(std::vector<int> &v) {
    unsigned int n = v.size();
    for (int i = 0; i < n; ++i) {
        unsigned int minumumValue = 0;
        for (int j = 0; j < n - i; ++j) {

        }
    }
}

int main() {
    std::vector<int> vector;
    unsigned int size = 100000;
    std::cout << "Selection Sort using while" << '\n';
    vector = generateRandomVector(size);
    printVector(vector);
    selectionSort(vector);
    printVector(vector);

    std::cout << "Tamanho: " << size << '\n';

    std::cout << "Bubble Sort using while:\n";
    calculateSortingFunctionTime(selectionSort, size, false);

    return 0;
}