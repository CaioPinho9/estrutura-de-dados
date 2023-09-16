#include <iostream>
#include <cmath>
#include <cstdio>

unsigned int module(int dividend, unsigned int divisor) {
    while (dividend < 0) {
        dividend += divisor;
    }
    return dividend % divisor;
}

struct City {
    int tag;
    int x, y;
};

struct Node {
    City value;
    Node *next = nullptr;
};

class LinkedList {
private:
    Node *head;
    unsigned int _size;
public:
    LinkedList();

    Node *find(City x);

    Node *get(int pos);

    void insert(int pos, City x);

    void swap(int pos);

    void push_back(City x);

    void remove(int pos);

    unsigned int size();

    void clear();

    void print();

    ~LinkedList();

private:
    void insert(Node *p, Node *newElement);
};

LinkedList::LinkedList() {
    head = new Node;
    _size = 0;
};

LinkedList::~LinkedList() {
    delete head;
};

unsigned int LinkedList::size() {
    return _size;
}

void LinkedList::insert(int pos, City x) {
    Node *newNode = new Node;
    newNode->value = x;

    if (_size == 0) {
        head = newNode;
        head->next = head;
        _size = 1;
        return;
    }

    Node *pivot = head;
    bool isHead = false;
    if (pos == 0) {
        isHead = true;
        head = newNode;
        pos = _size;
    }
    for (int i = 1; i < pos; ++i) {
        pivot = pivot->next;
    }
    if (pos == _size and not isHead) {
        newNode->next = head;
    } else {
        newNode->next = pivot->next;
    }
    pivot->next = newNode;
    _size++;
}

void LinkedList::push_back(City x) {
    insert(_size, x);
}

void LinkedList::swap(int pos) {
    Node *pivot = head;
    bool isHead = false;
    if (module(pos, _size) == 0) {
        isHead = true;
        pos = _size;
    }

    for (int i = 1; i < pos; ++i) {
        pivot = pivot->next;
    }
    Node *before_target = pivot;
    Node *target_swap1 = before_target->next;
    Node *target_swap2 = target_swap1->next;

    target_swap1->next = target_swap2->next;
    target_swap2->next = target_swap1;
    before_target->next = target_swap2;

    if (isHead) {
        head = target_swap2;
    } else if (module(pos, _size) == _size - 1) {
        head = target_swap1;
    }
}

Node *LinkedList::find(City x) {
    Node *p = head;
    while (p != nullptr and (p->value.x != x.x or p->value.y != x.y)) {
        p = p->next;
    }
    return p;
}


Node *LinkedList::get(int pos) {
    Node *p = head;
    unsigned int realPos = module(pos, _size);
    for (int i = 0; i < realPos; ++i) {
        p = p->next;
    }
    return p;
}

void LinkedList::print() {
    Node *p = head;
    std::cout << '\n';
    for (int i = 0; i <= _size; ++i) {
        std::cout << p->value.tag << ": " << p->value.x << ", " << p->value.y << '\n';
        p = p->next;
    }
}

float distanceBetweenTwoCities(City &a, City &b) {
    return std::sqrt(std::pow((a.x - b.x), 2) + std::pow((a.y - b.y), 2));
}

float distanceBetweenFourCities(City &a, City &b, City &c, City &d) {
    float distance = 0;
    distance += distanceBetweenTwoCities(a, b);
    distance += distanceBetweenTwoCities(b, c);
    distance += distanceBetweenTwoCities(c, d);
    return distance;
}

LinkedList readItems() {
    LinkedList linkedList;
    int i = 0;
    while (true) {
        City city = City();
        city.tag = i;
        std::cin >> city.x >> city.y;
        if (city.x == -1) {
            break;
        }
        linkedList.push_back(city);
        i++;
    }

    return linkedList;
}

int main() {
    LinkedList linkedList = readItems();

    float oldDistance = 0;
    for (int i = 0; i < linkedList.size(); ++i) {
        Node *node = linkedList.get(i);
        City cityA = node->value;
        City cityB = node->next->value;
        oldDistance += distanceBetweenTwoCities(cityA, cityB);
    }

    printf("%.2f\n", oldDistance);

    float bestDistance = oldDistance;
    float newDistance;
    bool distanceImproved;

    do {
        for (int i = 0; i < linkedList.size(); ++i) {
            Node *node = linkedList.get(i - 1);
            City cityA = node->value;
            City cityB = node->next->value;
            City cityC = node->next->next->value;
            City cityD = node->next->next->next->value;

            float distance1 = distanceBetweenFourCities(cityA, cityB, cityC, cityD);
            float distance2 = distanceBetweenFourCities(cityA, cityC, cityB, cityD);

            if (distance1 > distance2) {
                linkedList.swap(i);
            }
        }
        newDistance = 0;
        for (int i = 0; i < linkedList.size(); ++i) {
            Node *node = linkedList.get(i);
            City cityA = node->value;
            City cityB = node->next->value;
            newDistance += distanceBetweenTwoCities(cityA, cityB);
        }
        distanceImproved = bestDistance > newDistance;
        bestDistance = newDistance;
    } while (distanceImproved);
    printf("%.2f\n", newDistance);
    return 0;
}
