//
// Created by caiop on 16/08/2023.
//

#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <chrono>

typedef struct Item {
    int tag = 0;
    int value = 0;
    int weight = 0;
    int numberOfItems = 0;
    double valueByWeight = 0;
} Item;


typedef struct BackpackItem {
    int itemType = 0;
    int quantity = 0;
} BackpackItem;

void putInBackpack(
        Item &item, std::vector<BackpackItem> &backpack,
        unsigned int &backpackSize,
        unsigned int &backpackIndex,
        unsigned int smallestWeight
) {
    bool alreadyInBackpack = false;
    while (backpackSize >= item.weight and item.numberOfItems > 0) {
        if (not alreadyInBackpack) {
            backpackIndex++;
            backpack.emplace_back();
            backpack[backpackIndex].itemType = item.tag;
            alreadyInBackpack = true;
        }
        backpack[backpackIndex].quantity++;
        backpackSize -= item.weight;
        item.numberOfItems--;
    }
    if (backpackSize < smallestWeight) {
        return;
    }
}

void fillBackpackSelectionSort(
        std::vector<BackpackItem> &backpack,
        std::vector<Item> &listOfItems,
        unsigned int backpackSize
) {
    // Selection sort algorithm
    unsigned int backpackIndex = -1;
    unsigned int smallestWeight = std::numeric_limits<int>::infinity();

    unsigned int n = listOfItems.size();
    for (int i = 0; i < n; ++i) {
        unsigned int indexMax = i;
        for (int j = i; j < n; ++j) {
            bool swap = (listOfItems[j].valueByWeight > listOfItems[indexMax].valueByWeight) ||
                        (listOfItems[j].tag < listOfItems[indexMax].tag &&
                         listOfItems[j].valueByWeight == listOfItems[indexMax].valueByWeight);

            if (swap) {
                indexMax = j;
            }

            if (smallestWeight > listOfItems[j].weight) {
                smallestWeight = listOfItems[j].weight;
            }
        }
        auto bestItem = listOfItems[indexMax];
        listOfItems[indexMax] = listOfItems[i];
        listOfItems[i] = bestItem;

        putInBackpack(bestItem, backpack, backpackSize, backpackIndex, smallestWeight);
    }
};

void merge(std::vector<Item> &vector, int left, int mid, int right) {
    unsigned int const leftVectorSize = mid - left + 1;
    unsigned int const rightVectorSize = right - mid;

    std::vector<Item> leftVector(leftVectorSize, Item()), rightVector(rightVectorSize, Item());

    for (int i = 0; i < leftVectorSize; ++i) {
        leftVector[i] = vector[left + i];
    }
    for (int i = 0; i < rightVectorSize; ++i) {
        rightVector[i] = vector[mid + 1 + i];
    }

    unsigned int indexLeftVector = 0, indexRightVector = 0;
    int indexMergedVector = left;

    while (indexLeftVector < leftVectorSize and indexRightVector < rightVectorSize) {
        if (leftVector[indexLeftVector].valueByWeight >= rightVector[indexRightVector].valueByWeight) {
            vector[indexMergedVector] = leftVector[indexLeftVector];
            indexLeftVector++;
        } else {
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

void mergeSortRecursive(std::vector<Item> &vector, int begin, int end) {
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSortRecursive(vector, begin, mid);
    mergeSortRecursive(vector, mid + 1, end);
    merge(vector, begin, mid, end);
}

void mergeSort(std::vector<Item> &vector) {
    int vectorSize = vector.size() - 1;
    mergeSortRecursive(vector, 0, vectorSize);
}

void fillBackpackMergeSort(
        std::vector<BackpackItem> &backpack,
        std::vector<Item> &listOfItems,
        unsigned int backpackSize
) {
    unsigned int backpackIndex = -1;
    unsigned int smallestWeight = std::numeric_limits<int>::infinity();

    mergeSort(listOfItems);

    // Lowest weight possible
    for (auto item: listOfItems) {
        if (smallestWeight > item.weight) {
            smallestWeight = item.weight;
        }
    }

    for (Item item: listOfItems) {
        putInBackpack(item, backpack, backpackSize, backpackIndex, smallestWeight);
    }
};


std::vector<Item> readItems() {
    std::vector<Item> listOfItems;
    int exit;
    int tag = 0;
    while (true) {
        Item item;
        std::cin >> item.value >> item.weight >> item.numberOfItems;
        item.valueByWeight = static_cast<double>(item.value) / item.weight;
        item.tag = tag;
        tag++;
        exit = item.value + item.weight + item.numberOfItems;
        if (exit == -3) {
            break;
        }
        listOfItems.push_back(item);
    }

    return listOfItems;
}


void printBackpack(std::vector<BackpackItem> &backpack) {
    for (auto item: backpack) {
        std::cout << item.itemType << ' ' << item.quantity << '\n';
    }
}

std::vector<Item> generateItems(int numItems, int maxValue, int maxWeight) {
    std::vector<Item> items;

    std::srand(std::time(nullptr)); // Seed the random number generator

    for (int i = 0; i < numItems; ++i) {
        Item newItem;
        newItem.value = std::rand() % (maxValue + 1);
        newItem.weight = std::rand() % (maxWeight + 1);
        newItem.numberOfItems = std::rand() % 5 + 1; // Number of items can be between 1 and 5
        items.push_back(newItem);
    }

    return items;
}

void calculateBackpackProblem(
        void (*backpackProblem)(std::vector<BackpackItem> &, std::vector<Item> &, unsigned int),
        std::vector<BackpackItem> backpack,
        std::vector<Item> listOfItems,
        unsigned int backpackSize
) {
    auto start = std::chrono::system_clock::now();
    backpackProblem(backpack, listOfItems, backpackSize);
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
}

void calculate_benchmark() {
    int numItems = 10000;
    int maxValue = 100;
    int maxWeight = 50;
    unsigned int backpackSize = 200000;
    std::vector<BackpackItem> backpack;

    std::vector<Item> items = generateItems(numItems, maxValue, maxWeight);

    calculateBackpackProblem(fillBackpackMergeSort, backpack, items, backpackSize);

    backpack = std::vector<BackpackItem>(0, BackpackItem());
    calculateBackpackProblem(fillBackpackSelectionSort, backpack, items, backpackSize);

    printBackpack(backpack);
}

int main() {
    std::vector<BackpackItem> backpack;
    std::vector<Item> listOfItems;

//    listOfItems = readItems();
//
//    unsigned int backpackSize;
//    std::cin >> backpackSize;
//
//    fillBackpackMergeSort(backpack, listOfItems, backpackSize);

    calculate_benchmark();

    printBackpack(backpack);

    return 0;
}

