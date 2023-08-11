//
// Created by caiop on 11/08/2023.
//
# include <cstdlib>
# include <vector>
# include <iostream>

void print(std::vector<int> &v) {
    for (auto x: v) {
        std::cout << x << '\n';
    }
    std::cout << '\n';

}

std::vector<int> generate_random_vector(unsigned int vector_size) {
    std::vector<int> vector = {};
    for (int i = 0; i < vector_size; ++i) {
        auto n = rand() % 10;
        vector.push_back(n);
    }
    return vector;
}

void knuth_shuffle(std::vector<int> &v) {
    srand(time(NULL)); // A different seed each time
    int n = v.size();
    for (int i = --n; i > 0; i--) {
        // Pick a random index from 0 to i:
        int j = rand() % (i + 1);

        //
        auto aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
}