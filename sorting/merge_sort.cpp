//
// Created by caiop on 18/08/2023.
//
#include <vector>


void merge(std::vector<int> &vector, int left, int mid, int right) {
    int const leftVectorSize = mid - left + 1;
    int const rightVectorSize = right - mid;

    std::vector<int> leftVector(leftVectorSize, 0), rightVector(rightVectorSize, 0);

    for (int i = 0; i < leftVectorSize; ++i) {
        leftVector[i] = vector[left + i];
    }
    for (int i = 0; i < rightVectorSize; ++i) {
        leftVector[i] = vector[mid + 1 + i];
    }

    int indexLeftVector = 0, indexRightVector = 0;
    int indexMergedVector = left;


}

void mergeSortRecursive(std::vector<int> &vector, int begin, int end) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSortRecursive(vector, begin, mid);
    mergeSortRecursive(vector, mid + 1, end);
    merge(vector, begin, mid, end);
}


void mergeSort(std::vector<int> &vector) {
    int vectorSize = vector.size() - 1;
    mergeSortRecursive(vector, 0, vectorSize);
}

