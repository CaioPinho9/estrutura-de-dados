//
// Created by caiop on 25/10/2023.
//
#include <iostream>

float power(float x, int n) {
    if (n == 1)
        return x;

    if (n < 0)
        return 1 / power(x, -n);

    float aux = power(x, n / 2);

    aux = aux * aux;

    if (n % 2 == 0)
        return aux;
    return x * aux;
}

int main() {
    std::cout << power(2, -3) << std::endl;
    return 0;
}

