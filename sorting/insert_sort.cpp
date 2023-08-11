//
// Created by caiop on 11/08/2023.
//
# include <vector>
# include "utils.cpp"

void insert_sort(std::vector<int> &v) {
    unsigned int n = v.size();
    int j;
    for (auto i = 1; i < n; ++i) {
        j = i - 1;
        auto pivot = v[i];
        while (j >= 0 and pivot < v[j]) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = pivot;
    }
}


int main() {
    std::vector<int> v = generate_random_vector(6);

    print(v);

    insert_sort(v);

    print(v);

    return 0;
}