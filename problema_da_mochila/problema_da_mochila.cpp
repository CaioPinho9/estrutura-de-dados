//
// Created by caiop on 16/08/2023.
//

#include <iostream>
#include <vector>
#include <limits>

typedef struct Item {
    int tag = 0;
    int value = 0;
    int weight = 0;
    int numberOfItems = 0;
    double valueByWeight = 0;
} Item;

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

typedef struct BackpackItem {
    int itemType = 0;
    int quantity = 0;
} BackpackItem;

//void selectionSort(std::vector<int> &v) {
//    unsigned int n = v.size();
//    for (int i = 0; i < n - 1; ++i) {
//        unsigned int index_min = i;
//        for (int j = i; j < n; ++j) {
//            if (v[j] < v[index_min]) {
//                index_min = j;
//            }
//        }
//        auto aux = v[i];
//        v[i] = v[index_min];
//        v[index_min] = aux;
//    }
//}

void fillBackpack(std::vector<BackpackItem> &backpack, std::vector<Item> &listOfItems, unsigned int backpackSize) {
    // Selection sort algorithm
    unsigned int backpackIndex = 0;
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

        bool itemFitInside = false;
        while (backpackSize >= bestItem.weight and bestItem.numberOfItems > 0) {
            if (backpack.size() < backpackIndex + 1) {
                backpack.emplace_back();
                backpack[backpackIndex].itemType = bestItem.tag;
            }
            backpack[backpackIndex].quantity++;
            backpackSize -= bestItem.weight;
            bestItem.numberOfItems--;
            itemFitInside = true;
        }
        if (backpackSize < smallestWeight) {
            return;
        }
        if (itemFitInside) {
            backpackIndex++;
        }
    }

};

int main() {
    unsigned int backpackSize;
    std::vector<BackpackItem> backpack;
    std::vector<Item> listOfItems;
    listOfItems = readItems();
    std::cin >> backpackSize;
    fillBackpack(backpack, listOfItems, backpackSize);

    return 0;
}