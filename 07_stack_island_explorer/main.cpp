#include <iostream>
#include <vector>
#include <sstream>

struct Coords {
    int x = -1, y = -1;

    Coords() = default;

    Coords(int x, int y) : x(x), y(y) {}
};

class Stack {
private:
    unsigned int currentSize;
    unsigned int capacity;
    Coords *stack;

public:
    Stack() {
        currentSize = 0;
        capacity = 10;
        stack = new Coords[capacity];
    };

    Coords top() {
        if (not empty())
            return stack[currentSize - 1];

        return {-1, -1};
    };

    void push_back(Coords x) {
        if (currentSize >= capacity) realoc_stack();
        stack[currentSize] = x;
        currentSize++;
    };

    Coords pop() {
        if (currentSize == 0) return {-1, -1};
        currentSize--;
        return stack[currentSize];
    };

    [[nodiscard]] unsigned int size() const {
        return currentSize;
    };

    void clear() {
        currentSize = 0;
    };

    void print() {
        for (int i = 0; i < currentSize; ++i) {
            std::cout << '(' << stack[i].x << ',' << stack[i].y << ')' << ' ';
        }
        std::cout << '\n';
    };

    [[nodiscard]] bool empty() const {
        return currentSize == 0;
    };

    ~Stack() {
        delete[] stack;
    };

private:
    void realoc_stack() {
        capacity *= 2;
        auto *aux_stack = new Coords[capacity];
        for (int i = 0; i < currentSize; ++i) {
            aux_stack[i] = stack[i];
        }
        delete[] stack;
        stack = aux_stack;
    };
};


void readInput(std::vector<std::vector<int>> &matrix) {
    std::string line;

    while (std::getline(std::cin, line) && line != "-1") {
        std::vector<int> row;
        int num;

        for (char c : line) {
            if (c != ' ') {
                num = c - '0';
                row.push_back(num);
            }
        }

        matrix.push_back(row);
    }
}

void printMatrix(std::vector<std::vector<int>> &matrix) {
    for (int y = 0; y < matrix.size(); ++y) {
        for (int x = 0; x < matrix[0].size(); ++x) {
            std::cout << matrix[y][x] << ' ';
        }
        std::cout << '\n';
    }
}

void createBaseIsland(std::vector<std::vector<int>> &matrix) {
    std::string charMatrix[] = {
            "0000000000",
            "0011000000",
            "0011000000",
            "0011000000",
            "0010000000",
            "0000001100",
            "0000011100",
            "0000000000",
            "0000000000",
            "0000000000",
    };
    for (int rowIndex = 0; rowIndex < 10; ++rowIndex) {
        std::vector<int> row;
        matrix.push_back(row);
        for (int charIndex = 0; charIndex < 10; ++charIndex) {
            int value = charMatrix[rowIndex][charIndex] - '0';
            matrix[rowIndex].push_back(value);
        }
    }
}


class Explorer {
private:
    std::vector<std::vector<int>> map;
    Stack coordsToExplore;
    std::vector<int> sizeIslands;
    int islandNumber;

    void checkIfNeedToBeExplored(Coords &coord) {
        if (coord.y >= map.size() || coord.x >= map[0].size())
            return;

        if (map[coord.y][coord.x] == 1) {
            coordsToExplore.push_back(coord);
            sizeIslands[islandNumber]++;
            map[coord.y][coord.x] = -1;
        }
    };

    void lookAround(Coords &currentCoord) {
        Coords rightCoord = Coords(currentCoord.x + 1, currentCoord.y);
        Coords leftCoord = Coords(currentCoord.x - 1, currentCoord.y);
        Coords upCoord = Coords(currentCoord.x, currentCoord.y - 1);
        Coords downCoord = Coords(currentCoord.x, currentCoord.y + 1);

        checkIfNeedToBeExplored(rightCoord);
        checkIfNeedToBeExplored(leftCoord);
        checkIfNeedToBeExplored(upCoord);
        checkIfNeedToBeExplored(downCoord);
    }

    void exploreIsland() {
        Coords currentCoord = coordsToExplore.pop();

        lookAround(currentCoord);
    };

    int getBiggerIsland() {
        int biggestIsland = 0;

        for (int sizeIsland: sizeIslands) {
            if (sizeIsland > biggestIsland)
                biggestIsland = sizeIsland;
        }

        return biggestIsland;
    }


public:
    Explorer(std::vector<std::vector<int>> &map) : map(map) {
        islandNumber = 0;
        sizeIslands.push_back(0);
    }

    int exploreSea() {

        for (int y = 0; y < map.size(); ++y) {
            for (int x = 0; x < map[0].size(); ++x) {
                if (map[y][x] == 1) {
                    coordsToExplore.push_back(Coords(x, y));

                    while (!coordsToExplore.empty()) {
                        exploreIsland();
                    }

                    //Check next island
                    islandNumber++;
                    sizeIslands.push_back(0);
                }
                map[y][x] = -1;
            }
        }

        return getBiggerIsland();
    };
};


int main() {
    std::vector<std::vector<int>> matrix;
    Stack stack;

    readInput(matrix);

    Explorer explorer = Explorer(matrix);

    std::cout << explorer.exploreSea();

    return 0;
}
