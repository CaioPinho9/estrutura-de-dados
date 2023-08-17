//
// Created by caiop on 16/08/2023.
//

#include <iostream>
#include <vector>

typedef struct Item {
    int value = 0;
    int weight = 0;
    int number_of_items = 0;
    double value_by_weight = 0;
} Item;

std::vector<Item> read() {
    std::vector<Item> list_of_items;
    int exit = 0;
    while (true) {
        Item item;
        std::cin >> item.value >> item.weight >> item.number_of_items;
        item.value_by_weight = static_cast<double>(item.value) / item.weight;
        exit = item.value + item.weight + item.number_of_items;
        if (exit == -3) {
            break;
        }
        list_of_items.push_back(item);
    }
    return list_of_items;
}

int main() {
    std::vector<Item> list_of_items;
    list_of_items = read();

    return 0;
}