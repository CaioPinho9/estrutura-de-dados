//
// Created by caiop on 11/08/2023.
//
#include <vector>
//#include "utils.cpp"

void insertSort(std::vector<int> &v) {
    unsigned int n = v.size();
    int j;
    for (auto i = 1; i < n; ++i) {
        j = i - 1;
        auto pivot = v[i];
        while (j >= 0 and pivot < v[j]) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = pivot;
    }
}


//int main() {
//    unsigned int size = 50000;
//    std::vector<int> vector = generateRandomVector(size);
//    std::cout << "Tamanho: " << size << '\n';
//
//    std::cout << "Insert Sort:\n";
//    calculateSortingFunctionTime(insertSort, vector, false);
//
//    return 0;
//}