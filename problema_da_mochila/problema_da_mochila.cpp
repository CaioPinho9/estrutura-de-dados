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

void fillBackpack(std::vector<BackpackItem> &backpack, std::vector<Item> &listOfItems, unsigned int backpackSize) {
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

        bool alreadyInBackpack = false;
        while (backpackSize >= bestItem.weight and bestItem.numberOfItems > 0) {
            if (not alreadyInBackpack) {
                backpackIndex++;
                backpack.emplace_back();
                backpack[backpackIndex].itemType = bestItem.tag;
                alreadyInBackpack = true;
            }
            backpack[backpackIndex].quantity++;
            backpackSize -= bestItem.weight;
            bestItem.numberOfItems--;
        }
        if (backpackSize < smallestWeight) {
            return;
        }
    }

};

void printBackpack(std::vector<BackpackItem> &backpack) {
    for (auto item: backpack) {
        std::cout << item.itemType << ' ' << item.quantity << '\n';
    }
}

int main() {
    std::vector<BackpackItem> backpack;
    std::vector<Item> listOfItems;

    listOfItems = readItems();

    unsigned int backpackSize;
    std::cin >> backpackSize;

    fillBackpack(backpack, listOfItems, backpackSize);

    printBackpack(backpack);

    return 0;
}