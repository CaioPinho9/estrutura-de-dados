//
// Created by caiop on 18/08/2023.
//
#include <vector>


void merge(std::vector<int> &vector, int left, int mid, int right) {
    unsigned int const leftVectorSize = mid - left + 1;
    unsigned int const rightVectorSize = right - mid;

    std::vector<int> leftVector(leftVectorSize, 0), rightVector(rightVectorSize, 0);

    for (int i = 0; i < leftVectorSize; ++i) {
        leftVector[i] = vector[left + i];
    }
    for (int i = 0; i < rightVectorSize; ++i) {
        rightVector[i] = vector[mid + 1 + i];
    }

    unsigned int indexLeftVector = 0, indexRightVector = 0;
    int indexMergedVector = left;

    while (indexLeftVector < leftVectorSize and indexRightVector < rightVectorSize) {
        if (leftVector[indexLeftVector] <= rightVector[indexRightVector]) {
            vector[indexMergedVector] = leftVector[indexLeftVector];
            indexLeftVector++;
        }
        if (rightVector[indexRightVector] < leftVector[indexLeftVector]) {
            vector[indexMergedVector] = rightVector[indexRightVector];
            indexRightVector++;
        }
        indexMergedVector++;
    }

    while (indexLeftVector < leftVectorSize) {
        vector[indexMergedVector] = leftVector[indexLeftVector];
        indexLeftVector++;
        indexMergedVector++;
    }

    while (indexRightVector < rightVectorSize) {
        vector[indexMergedVector] = rightVector[indexRightVector];
        indexRightVector++;
        indexMergedVector++;
    }
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

