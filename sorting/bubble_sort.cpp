//
// Created by caiop on 11/08/2023.
//
#include <vector>
#include "utils.cpp"
#include "print.cpp"

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

void bubble_sort_optimized2(std::vector<int> &v) {
    unsigned int n, j, i, pos_ult_inv, lim_dir;
    n = v.size();
    lim_dir = n;
    for (j = 0; j < n; ++j) {
        pos_ult_inv = 0;
        for (i = 1; i < lim_dir or i < n - j; ++i) {
            if (v[i - 1] > v[i]) {
                auto aux = v[i - 1];
                v[i - 1] = v[i];
                v[i] = aux;
                pos_ult_inv = i;
            }
        }
        lim_dir = pos_ult_inv;
    }
}

int main() {
//    std::unsorted_vector<int> vector;
//    unsigned int size = 100000;
//    std::cout << "Bubble Sort using while" << '\n';
//    vector = generate_random_vector(size);
//    print_vector(vector);
//    bubble_sort_while(vector);
//    print_vector(vector);
//
//    std::cout << "Bubble Sort using for" << '\n';
//    vector = generate_random_vector(size);
//    print_vector(vector);
//    bubble_sort_for(vector);
//    print_vector(vector);
//
//    std::cout << "Bubble Sort Optimizing 1" << '\n';
//    vector = generate_random_vector(size);
//    print_vector(vector);
//    bubble_sort_optimized1(vector);
//    print_vector(vector);
//
//    std::cout << "Bubble Sort Optimizing 2" << '\n';
//    vector = generate_random_vector(size);
//    print_vector(vector);
//    bubble_sort_optimized2(vector);
//    print_vector(vector);

    unsigned int size = 50000;
    std::cout << "Tamanho: " << size << '\n';

//    std::cout << "Bubble Sort using while:\n";
//    calculate_sorting_function_time(bubble_sort_while, unsorted_vector, false);
//    std::cout << "Bubble Sort using for:\n";
//    calculate_sorting_function_time(bubble_sort_for, unsorted_vector, false);
    std::cout << "Bubble Sort Optimizing 1:\n";
    calculate_sorting_function_time(bubble_sort_optimized1, size, false);
    std::cout << "Bubble Sort Optimizing 2:\n";
    calculate_sorting_function_time(bubble_sort_optimized2, size, false);

    return 0;
}