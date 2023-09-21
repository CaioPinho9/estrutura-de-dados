//
// Created by caiop on 20/09/2023.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

int sequencial_search(std::vector<int> &v, int x) {
    for (int i = 0; i < v.size(); i++) {
        if (v[i] == x)
            return i;
    }
}

int binary_search(std::vector<int> &v, int x) {
    int e = 0, d = v.size();
    while (e < d - 1) {
        int m = (e + d) / 2;
        if (v[m] < x) {
            e = m;
        } else {
            d = m;
        }
    }
    return d;
}

float random_number(int max_value) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, max_value); // Adjust the range as needed
    return distribution(gen);
}

float binary_search_time(std::vector<int> &v, int x) {
    auto startTime = std::chrono::high_resolution_clock::now();
    binary_search(v, x);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    return duration.count();
}

float sequencial_search_time(std::vector<int> &v, int x) {
    auto startTime = std::chrono::high_resolution_clock::now();
    sequencial_search(v, x);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    return duration.count();
}

double calculateMean(const std::vector<int> &vec) {
    if (vec.empty()) {
        return 0.0; // Handle the case where the vector is empty to avoid division by zero.
    }

    int sum = 0;
    for (int num: vec) {
        sum += num;
    }

    return static_cast<double>(sum) / vec.size();
}

int main() {
    std::vector<int> list_of_list_sizes;
    std::vector<float> list_of_x_values;

    for (int j = 0; j < 1000; j++) {
        std::vector<int> randomIntegers;

        int durationB, durationS, list_size = 1000;

        float random = random_number(list_size - 1) / list_size;

        do {
            for (int i = randomIntegers.size(); i < list_size; ++i) {
                randomIntegers.push_back(i);
            }

            durationS = sequencial_search_time(randomIntegers, static_cast<int>(list_size * random));
            durationB = binary_search_time(randomIntegers, static_cast<int>(list_size * random));

            list_size += 100;
        } while (durationS <= durationB);
        std::cout << j << ": " << list_size << " x: " << random << "\n";
        list_of_list_sizes.push_back(list_size);
        list_of_x_values.push_back(random);
    }

    std::cout << '\n' << calculateMean(list_of_list_sizes) << '\n';

    std::cout << "list_size" << "," << "local_of_x" << std::endl;

    // Write the data to the file as two columns
    for (size_t i = 0; i < list_of_list_sizes.size(); ++i) {
        std::cout << list_of_list_sizes[i] << "," << list_of_x_values[i] << std::endl;
    }

    return 0;
}