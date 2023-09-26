//
// Created by caiop on 20/09/2023.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <unordered_map>

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

int hash_map_search(std::unordered_map<int, int> &map, int x) {
    return map[x];
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
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    return duration.count();
}

float sequencial_search_time(std::vector<int> &v, int x) {
    auto startTime = std::chrono::high_resolution_clock::now();
    sequencial_search(v, x);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    return duration.count();
}

float hash_map_search_time(std::unordered_map<int, int> &map, int x) {
    auto startTime = std::chrono::high_resolution_clock::now();
    hash_map_search(map, x);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    return duration.count();
}

int main() {
    std::vector<int> listSizeData;
    std::vector<float> positionData;
    std::vector<float> sequentialTimeData;
    std::vector<float> binaryTimeData;
    std::vector<float> mapTimeData;

    for (int j = 0; j < 10; j++) {
        std::vector<int> testList;
        std::unordered_map<int, int> testMap;

        float durationB, durationS, durationM;
        int listSize = 10000;

        float random = random_number(listSize - 1) / listSize;

        while (listSize < 10000000) {
            for (int i = testList.size(); i < listSize; ++i) {
                testList.push_back(i);
                testMap[i] = i;
            }

            int positionIndex = static_cast<int>(listSize * random);

            durationS = sequencial_search_time(testList, positionIndex);
            durationB = binary_search_time(testList, positionIndex);
            durationM = hash_map_search_time(testMap, positionIndex);

            listSize += 10000;

            listSizeData.push_back(listSize);
            positionData.push_back(random);
            sequentialTimeData.push_back(durationS);
            binaryTimeData.push_back(durationB);
            mapTimeData.push_back(durationM);
        }
        std::cout << j << "\n";
    }

    std::cout << "listSizeData" << ",";
    std::cout << "positionData" << ",";
    std::cout << "sequentialTimeData" << ",";
    std::cout << "binaryTimeData" << ",";
    std::cout << "mapTimeData" << "\n";

    // Write the data to the file as two columns
    for (size_t i = 0; i < listSizeData.size(); ++i) {
        std::cout << listSizeData[i] << ",";
        std::cout << positionData[i] << ",";
        std::cout << sequentialTimeData[i] << ",";
        std::cout << binaryTimeData[i] << ",";
        std::cout << mapTimeData[i] << "\n";
    }

    return 0;
}