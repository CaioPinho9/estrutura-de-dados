//
// Created by caiop on 16/08/2023.
//
#include <vector>
//#include "utils.cpp"

void selectionSort(std::vector<int> &v) {
    unsigned int n = v.size();
    for (int i = 0; i < n - 1; ++i) {
        unsigned int index_min = i;
        for (int j = i; j < n; ++j) {
            if (v[j] < v[index_min]) {
                index_min = j;
            }
        }
        auto aux = v[i];
        v[i] = v[index_min];
        v[index_min] = aux;
    }
}

//int main() {
//    std::vector<int> vector;
//    unsigned int size = 10000;
//    std::cout << "Selection Sort using while" << '\n';
//    vector = generateRandomVector(size);
//    printVector(vector);
//    selectionSort(vector);
//    printVector(vector);
//
//    std::cout << "Tamanho: " << size << '\n';
//
//    std::cout << "Selection Sort:\n";
//    calculateSortingFunctionTime(selectionSort, vector, false);
//
//    return 0;
//}