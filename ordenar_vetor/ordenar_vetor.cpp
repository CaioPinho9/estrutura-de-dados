//
// Created by caiop on 09/08/2023.
//

#include <vector>
#include <iostream>

bool is_sorted(std::vector<int>& v) {
    for (unsigned int i = 0; i < v.size() - 1; i++) {
        if (&v[i] > &v[i + 1])
            return false;
    }
    return true;
}

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};

    for (auto x: v) {
        std::cout << x << ' ';
    }

    std::cout << '\n';

    std::cout << "Is sorted: " << is_sorted(v) << '\n';

    return 0;
}