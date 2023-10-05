#include <iostream>
#include <vector>
#include <chrono>

int recursive_sum(std::vector<int> list, int left, int right) {
    if (left == right)
        return list[left];

    int mid = (left + right) / 2;

    return recursive_sum(list, left, mid) + recursive_sum(list, mid + 1, right);
}

int tree_sum(std::vector<int> list) {
    int size = list.size();
    if (size == 0)
        return 0;
    return recursive_sum(list, 0, size - 1);
}

int sequential_sum(std::vector<int> list) {
    int sum = 0;
    for (int i = 0; i < list.size(); i++) {
        sum += list[i];
    }
    return sum;
}

float tree_time(std::vector<int> &v) {
    auto startTime = std::chrono::high_resolution_clock::now();
    tree_sum(v);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    return duration.count();
}

float sequential_time(std::vector<int> &v) {
    auto startTime = std::chrono::high_resolution_clock::now();
    sequential_sum(v);
    auto endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    return duration.count();
}

int main() {
    // Conclusion, do not use trees to sum numbers
    std::vector<int> listSizeData;
    std::vector<float> sequentialTimeData;
    std::vector<float> treeTimeData;

    for (int j = 0; j < 1; j++) {
        std::vector<int> testList;

        float durationT, durationS;
        int listSize = 100000;

        while (listSize < 1000000) {
            for (int i = testList.size(); i < listSize; ++i) {
                testList.push_back(i);
            }

            durationS = sequential_time(testList);
            durationT = tree_time(testList);

            listSize += 100000;

            listSizeData.push_back(listSize);
            sequentialTimeData.push_back(durationS);
            treeTimeData.push_back(durationT);

            std::cout << listSize << '\n';
            std::cout << durationS << '\n';
            std::cout << durationT << '\n' << '\n';
        }
        std::cout << j << "\n";
    }

    std::cout << "listSizeData" << ",";
    std::cout << "sequentialTimeData" << ",";
    std::cout << "treeTimeData" << "\n";

    // Write the data to the file as two columns
    for (size_t i = 0; i < listSizeData.size(); ++i) {
        std::cout << listSizeData[i] << ",";
        std::cout << sequentialTimeData[i] << ",";
        std::cout << treeTimeData[i]<< '\n';
    }

    // Conclusion, do not use trees to sum numbers
    return 0;
}
