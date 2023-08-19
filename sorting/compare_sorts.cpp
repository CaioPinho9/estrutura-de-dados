//
// Created by caiop on 16/08/2023.
//
#include <vector>
#include "insert_sort.cpp"
#include "bubble_sort.cpp"
#include "selection_sort.cpp"
#include "merge_sort.cpp"
#include "utils.cpp"

int main() {
    unsigned int size = 50000;
    std::vector<int> vector = generateRandomVector(size);
    std::cout << "Tamanho: " << size << '\n';

    std::cout << "Insert Sort:\n";
    calculateSortingFunctionTime(insertSort, vector, false);

    std::cout << "Bubble Sort:\n";
    calculateSortingFunctionTime(bubbleSortOptimized2, vector, false);

    std::cout << "Selection Sort:\n";
    calculateSortingFunctionTime(selectionSort, vector, false);

    std::cout << "Merge Sort:\n";
    calculateSortingFunctionTime(mergeSort, vector, false);
    return 0;
}