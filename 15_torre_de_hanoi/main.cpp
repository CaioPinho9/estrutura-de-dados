#include <iostream>

int hanoi(int disks, char origin, char aux, char dest) {
    if (disks == 0)
        return 1;
    int recursion = 0;
    recursion += hanoi(disks - 1, origin, dest, aux);

    std::cout << origin << "->" << dest << std::endl;

    recursion += hanoi(disks - 1, aux, origin, dest);
    return recursion;
};

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::cout << hanoi(5, 'A', 'B', 'C') << std::endl;
    return 0;
}

