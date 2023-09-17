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
            std::cout << x;
            queue(x);
        }
        std::cout << '\n';
    }

private:
    void realoc_array() {
        capacity *= 2;
        int *aux_array = new int[capacity];
        unsigned oldIndex = head;
        for (unsigned realIndex = 0; realIndex < currentSize; ++realIndex) {
            aux_array[realIndex] = array[oldIndex % capacity];
            oldIndex++;
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

    std::cout << queue.back()<< '\n';
    std::cout << queue.front()<< '\n';

    queue.enqueue();
    std::cout << queue.front()<< '\n';
    queue.enqueue();
    std::cout << queue.front()<< '\n';
    queue.enqueue();
    std::cout << queue.front()<< '\n';

    for (int i = 0; i < 10; i++) {
        queue.queue(i);
    }

    queue.print();

    return 0;
}