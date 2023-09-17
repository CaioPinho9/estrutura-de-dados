//
// Created by caiop on 16/09/2023.
//

#include <iostream>

class Queue {
private:
    unsigned currentSize, head, tail, capacity;
    int *array;
public:
    Queue() {
        currentSize = 0;
        head = 0;
        tail = 0;
        capacity = 10;
        array = new int[capacity];
    }

    void queue(int x) {
        if ((tail + 1) % capacity == head)
            realoc_array();

        array[tail] = x;
        tail = (tail + 1) % capacity;
        currentSize++;
    }

    int enqueue() {
        int x = array[head];
        head = (head + 1) % capacity;
        currentSize--;
        return x;
    }

    int front() {
        return array[head];
    }

    int back() {
        return array[(tail - 1) % capacity];
    }

    unsigned size() const {
        return currentSize;
    }

    void print() {
        for (int i = 0; i < currentSize; ++i) {
            int x = enqueue();
            std::cout << x << ' ';
            queue(x);
        }
        std::cout << '\n';
    }

private:
    void realoc_array() {
        capacity *= 2;
        int *aux_array = new int[capacity];
        unsigned oldIndex = head;
        unsigned oldCapacity = capacity / 2;
        for (unsigned realIndex = 0; realIndex < currentSize; ++realIndex) {
            aux_array[realIndex] = array[oldIndex];
            oldIndex = (oldIndex + 1) % oldCapacity;
        }
        head = 0;
        tail = currentSize;
        delete[] array;
        array = aux_array;
    }

};

int main() {
    Queue queue;

    for (int i = 0; i < 10; i++) {
        queue.queue(i);
    }

    queue.enqueue();
    queue.enqueue();
    queue.enqueue();

    queue.print();

    for (int i = 0; i < 100; i++) {
        queue.queue(i);
        queue.print();
    }

    return 0;
}