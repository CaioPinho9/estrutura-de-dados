//
// Created by caiop on 27/08/2023.
//

#include <iostream>

class MyVector {
private:
    unsigned int currentSize;
    unsigned int capacity;
    int *vector;
public:
    MyVector();

    int find(int x);

    void insert(int x, unsigned int pos);

    void remove(int x);

    unsigned int size() const;

    void clear();

    void print();

    ~MyVector();

private:
    void realoc_array();
};

MyVector::MyVector() {
    currentSize = 0;
    capacity = 10;
    vector = new int[capacity];
}

int MyVector::find(int x) {
    for (auto i = 0; i < currentSize; i++) {
        if (vector[i] == x) {
            return i;
        }
    }
    return -1;
}

void MyVector::insert(int x, unsigned int pos) {
    if (currentSize >= capacity) realoc_array();
    for (auto i = currentSize; i > pos; i--) {
        vector[i] = vector[i - 1];
    }
    vector[pos] = x;
    currentSize++;
}

void MyVector::remove(int x) {
    int pos = find(x);
    if (pos == -1) return;
    if (currentSize == 0) return;
    for (auto i = pos; i < currentSize - 1; i++) {
        vector[i] = vector[i + 1];
    }
    currentSize--;
}

unsigned int MyVector::size() const {
    return currentSize;
}

void MyVector::clear() {
    currentSize = 0;
}

void MyVector::print() {
    for (int i = 0; i < currentSize; ++i) {
        std::cout << vector[i] << ' ';
    }
    std::cout << '\n';
}

MyVector::~MyVector() {
    delete[] vector;
}

void MyVector::realoc_array() {
    capacity *= 2;
    int *aux_vector = new int[capacity];
    for (int i = 0; i < currentSize; ++i) {
        aux_vector[i] = vector[i];
    }
    delete[] vector;
    vector = aux_vector;
}


int main() {
    MyVector v = MyVector();
    for (int i = 0; i < 12; ++i) {
        v.insert(i, i);
    }
    v.print();
    std::cout << v.find(5) << '\n';
    v.remove(5);
    std::cout << v.find(5) << '\n';
    v.print();
    return 0;
}