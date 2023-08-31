#include <iostream>

struct Node {
    int value;
    Node *next = nullptr;
};

class LinkedList {
private:
    Node *head;
    unsigned int _size;
public:
    LinkedList();

    Node *find(int x);

    void insert(unsigned int pos, int x);

    void swap(unsigned int pos);

    void remove(unsigned int pos);

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

void LinkedList::insert(unsigned int pos, int x) {
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

void LinkedList::swap(unsigned int pos) {
    Node *pivot = head;
    bool isHead = false;
    if (pos % _size == 0) {
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
    } else if (pos % _size == _size - 1) {
        head = target_swap1;
    }
}

Node *LinkedList::find(int x) {
    Node *p = head;
    while (p != nullptr and p->value != x) {
        p = p->next;
    }
    return p;
}

void LinkedList::print() {
    Node *p = head;
    for (int i = 0; i <= _size; ++i) {
        std::cout << p->value;
        p = p->next;
    }
    std::cout << '\n';
}

int main() {
    LinkedList linkedList = LinkedList();
    for (int i = 0; i < 10; ++i) {
        linkedList.insert(i, i);
    }

    linkedList.print();

    linkedList.swap(9);

    linkedList.print();

    return 0;
}
