//
// Created by caiop on 11/08/2023.
//
# include <vector>
# include "utils.cpp"

void bubble_sort(std::vector<int> &v) {
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


int main() {
    std::vector<int> v = generate_random_vector(6);

    print(v);

    bubble_sort(v);

    print(v);

    return 0;
}