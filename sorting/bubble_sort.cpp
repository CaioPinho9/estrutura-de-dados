//
// Created by caiop on 11/08/2023.
//
# include <vector>
# include "utils.cpp"
# include <string>

void bubble_sort_while(std::vector<int> &v) {
    unsigned int n = v.size();
    bool mudou;
    do {
        mudou = false;
        for (int i = 1; i < n; ++i) {
            if (v[i - 1] > v[i]) {
                auto aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
                mudou = true;
            }
        }
    } while (mudou);
}

void bubble_sort_for(std::vector<int> &v) {
    unsigned int n = v.size();
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n; ++i) {
            if (v[i - 1] > v[i]) {
                auto aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
            }
        }
    }
}

void bubble_sort_optimized1(std::vector<int> &v) {
    unsigned int n = v.size();
    for (int j = 0; j < n; ++j) {
        for (int i = 1; i < n - j; ++i) {
            if (v[i - 1] > v[i]) {
                auto aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
            }
        }
    }
}

int main() {
    std::vector<int> v;

    print("Bubble Sort using while");
    v = generate_random_vector(6);
    print_vector(v);
    bubble_sort_while(v);
    print_vector(v);

    print("Bubble Sort using for");
    v = generate_random_vector(6);
    print_vector(v);
    bubble_sort_for(v);
    print_vector(v);

    print("Bubble Sort Optimizing 1");
    v = generate_random_vector(6);
    print_vector(v);
    bubble_sort_optimized1(v);
    print_vector(v);

    return 0;
}