//
// Created by caiop on 20/10/2023.
//
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

template<typename TKey, typename TValue>
class Node;

template<typename TKey, typename TValue>
class LinkedBinaryTree {
public:
    Node<TKey, TValue> *root;


    LinkedBinaryTree() {
        root = nullptr;
    }

    void insert(TKey key) {
        root = _insert(root, key, key, new bool(true));
        print_plot_string(&Node<int, int>::print_key);
    }

    void insert(TKey key, TValue value) {
        root = _insert(root, key, value, new bool(true));
    }

    bool is_empty() {
        return root == nullptr;
    }


    Node<TKey, TValue> *find(TKey key) {
        return _find(root, key);
    }

    void remove(TKey key) {
        _remove(find(key));
    }

    unsigned height() {
        return _height(root);
    }

    Node<TKey, TValue> *min() const {
        auto node = root;
        while (node->_left != nullptr) {
            node = node->_left;
        }
        return node;
    }

    Node<TKey, TValue> *max() const {
        auto node = root;
        while (node->_right != nullptr) {
            node = node->_right;
        }
        return node;
    }

    std::list<TKey> get_preorder() {
        std::list<TKey> nodes;
        _get_preorder(root, nodes);
        return nodes;
    }

    std::list<TKey> get_inorder() {
        std::list<TKey> nodes;
        _get_inorder(root, nodes);
        return nodes;
    }

    std::list<TKey> get_postorder() {
        std::list<TKey> nodes;
        _get_posorder(root, nodes);
        return nodes;
    }

    void print_plot_string(void (Node<TKey, TValue>::*_printFunction)()) {
        std::cout << '\"';
        std::queue<Node<TKey, TValue> *> queue;

        queue.push(root);
        unsigned max_height = height();
        std::vector<Node<TKey, TValue> *> nodes_to_delete;

        while (!queue.empty()) {
            auto currentNode = queue.front();
            queue.pop();
            if (currentNode == nullptr)
                continue;

            if (currentNode->_key == INT32_MIN) {
                std::cout << "# ";
            } else {
                (currentNode->*_printFunction)();
            }

            auto left = currentNode->_left;
            auto right = currentNode->_right;

            if (left == nullptr && max_height != currentNode->_height) {
                left = new Node<TKey, TValue>(INT32_MIN);
                left->_height = currentNode->_height + 1;
                nodes_to_delete.push_back(left);
            }
            if (right == nullptr && max_height != currentNode->_height) {
                right = new Node<TKey, TValue>(INT32_MIN);
                right->_height = currentNode->_height + 1;
                nodes_to_delete.push_back(right);
            }

            queue.push(left);
            queue.push(right);
        }
        for (auto node: nodes_to_delete) {
            auto parent = node->_parent;
            if (parent && parent->_left == node) {
                parent->_left = nullptr;
            }
            if (parent && parent->_right == node) {
                parent->_right = nullptr;
            }
            delete node;
        }
        std::cout << "\"," << std::endl;
    }

    void print_nodes(std::list<TKey> nodes) {
        for (auto value: nodes) {
            std::cout << std::to_string(value) << " ";
        }
        std::cout << std::endl;
    }

    ~LinkedBinaryTree() = default;

private:
    Node<TKey, TValue> *_insert(Node<TKey, TValue> *pivot, TKey key, TValue value, bool *new_height) {
        if (pivot == nullptr) {
            auto newNode = new Node<TKey, TValue>(key, value, nullptr, nullptr, pivot);
            *new_height = true;
            return newNode;
        }
        pivot->_size++;
        if (key <= pivot->_key) {
            pivot->_left = _insert(pivot->_left, key, value, new_height);
            return _rebalance_left(pivot, new_height);
        } else {
            pivot->_right = _insert(pivot->_right, key, value, new_height);
            return _rebalance_right(pivot, new_height);
        }
    }

    Node<TKey, TValue> *_rebalance_left(Node<TKey, TValue> *pivot, bool *new_height) {
        if (!*new_height)
            return pivot;

        if (pivot->_bf == +1) {
            pivot->_bf = 0;
            *new_height = false;
            return pivot;
        } else if (pivot->_bf == 0) {
            pivot->_bf = -1;
            *new_height = true;
            return pivot;
        }

        if (pivot->_left->_bf == -1) {
            pivot = _right_rotate(pivot);
            pivot->_right->_bf = 0;
        } else {
            pivot->_left = _left_rotate(pivot->_left);
            pivot = _right_rotate(pivot);
            if (pivot->_bf == +1) {
                pivot->_left->_bf = -1;
                pivot->_right->_bf = 0;
            } else if (pivot->_bf == -1) {
                pivot->_left->_bf = 0;
                pivot->_right->_bf = 1;
            } else {
                pivot->_left->_bf = pivot->_right->_bf = 0;
            }
        }
        pivot->_bf = 0;
        *new_height = false;
        return pivot;
    }

    Node<TKey, TValue> *_rebalance_right(Node<TKey, TValue> *pivot, bool *new_height) {
        if (!*new_height)
            return pivot;

        if (pivot->_bf == -1) {
            pivot->_bf = 0;
            *new_height = false;
            return pivot;
        } else if (pivot->_bf == 0) {
            pivot->_bf = +1;
            *new_height = true;
            return pivot;
        }

        if (pivot->_right->_bf == +1) {
            pivot = _left_rotate(pivot);
            pivot->_left->_bf = 0;
        } else {
            pivot->_right = _right_rotate(pivot->_right);
            pivot = _left_rotate(pivot);
            if (pivot->_bf == -1) {
                pivot->_right->_bf = +1;
                pivot->_left->_bf = 0;
            } else if (pivot->_bf == +1) {
                pivot->_right->_bf = 0;
                pivot->_left->_bf = 1;
            } else {
                pivot->_right->_bf = pivot->_left->_bf = 0;
            }
        }
        pivot->_bf = 0;
        *new_height = false;
        return pivot;
    }

    Node<TKey, TValue> *_right_rotate(Node<TKey, TValue> *node) {
        auto aux = node->_left;
        node->_left = aux->_right;
        aux->_right = node;

        if (node == root)
            root = aux;

        return aux;
    }

    Node<TKey, TValue> *_left_rotate(Node<TKey, TValue> *node) {
        auto aux = node->_right;
        node->_right = aux->_left;
        aux->_left = node;

        if (node == root)
            root = aux;

        return aux;
    }

    void _remove(Node<TKey, TValue> *node) {
        if (node == nullptr)
            return;

        auto left = node->_left;
        auto right = node->_right;

        if (left == nullptr && right == nullptr) {
            auto parent = node->_parent;
            if (node->_key <= parent->_key) {
                parent->_left = nullptr;
            } else {
                parent->_right = nullptr;
            }
            delete node;
        } else if (left == nullptr) {
            auto parent = node->_parent;

            if (node->_key <= parent->_key) {
                parent->_left = right;
            } else {
                parent->_right = right;
            }
            right->_parent = parent;

            delete node;
        } else {
            node->_size--;
            auto cursor = node->_right;

            while (cursor->_left != nullptr) {
                cursor->_size--;
                cursor = cursor->_left;
            }

            auto cursor_key = cursor->_key;
            auto cursor_value = cursor->_value;

            _remove(cursor);
            node->_key = cursor_key;
            node->_value = cursor_value;
        }
    }

    unsigned _height(Node<TKey, TValue> *node) {
        if (node == nullptr)
            return 0;

        auto left = node->_left;
        auto right = node->_right;

        unsigned height = std::max(_height(left), _height(right)) + 1;
        node->_height = height;

        return height;
    }

    Node<TKey, TValue> *_find(Node<TKey, TValue> *node, TKey key) {
        if (node == nullptr)
            return nullptr;

        auto currentKey = node->_key;

        if (currentKey == key) {
            return node;
        } else if (key <= currentKey) {
            return _find(node->_left, key);
        } else {
            return _find(node->_right, key);
        }
    }

    void _get_preorder(Node<TKey, TValue> *node, std::list<TKey> &nodes) {
        if (node == nullptr)
            return;

        auto left = node->_left;
        auto right = node->_right;

        nodes.push_back(node->_key);
        _get_preorder(left, nodes);
        _get_preorder(right, nodes);
    }

    void _get_posorder(Node<TKey, TValue> *node, std::list<TKey> &nodes) {
        if (node == nullptr)
            return;

        auto left = node->_left;
        auto right = node->_right;

        _get_posorder(left, nodes);
        _get_posorder(right, nodes);
        nodes.push_back(node->_key);
    }

    void _get_inorder(Node<TKey, TValue> *node, std::list<TKey> &nodes) {
        if (node == nullptr)
            return;

        auto left = node->_left;
        auto right = node->_right;

        _get_inorder(left, nodes);
        nodes.push_back(node->_key);
        _get_inorder(right, nodes);
    }
};


template<typename TKey, typename TValue>
class Node {
private:
    Node *_parent{};
    Node *_left{};
    Node *_right{};
    unsigned _size = 1;
    unsigned _height = 0;
    unsigned _bf = 0;
    TKey _key;
    TValue _value;

public:
    Node() = default;

    // We are using the list initializer of the parameters.
    Node(TKey __k) :
            _key(__k), _left(nullptr), _right(nullptr) {}

    Node(TKey __k, Node *__left, Node *__right, Node *__parent) :
            _key(__k), _left(__left), _right(__right), _parent(__parent) {}

    Node(TKey __k, TValue __value, Node *__left, Node *__right, Node *__parent) :
            _key(__k), _value(__value), _left(__left), _right(__right), _parent(__parent) {}

    TKey get_key() const { return _key; };

    TKey get_value() const { return _value; };

    unsigned get_size() const { return _size; };

    unsigned get_height() const { return _height; };

    void print_key() {
        std::cout << _key << " ";
    }

    void print_value() {
        std::cout << _value << " ";
    }

    void print_bf() {
        std::cout << _bf << " ";
    }

    void print_height() {
        std::cout << _height << " ";
    }

    Node *parent() const {
        return _parent;
    };

    Node *left() const {
        return _left;
    };

    Node *right() const {
        return _right;
    };

    friend class LinkedBinaryTree<TKey, TValue>;
};

std::vector<int> read() {
    std::vector<int> myVector;
    std::string line;
    int value;

    // Read a line to get the value
    if (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        if (iss >> value) {
            // Use a for loop to read and append values
            for (int i = 0; i < value; i++) {
                int inputValue;
                if (std::cin >> inputValue) {
                    myVector.push_back(inputValue);
                }
            }
        }
    }
    return myVector;
}

int main() {
//    std::vector<int> items = {50, 20, 75, 10, 40, 60, 80, 15, 55, 65, 100, 120};
    LinkedBinaryTree<int, int> T;
    std::vector<int> items = read();
    for (const auto &i: items) {
        T.insert(i);
    }

    for (const auto &x: T.get_preorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    for (const auto &x: T.get_inorder()) {
        std::cout << x << ' ';
    }

    std::cout << std::endl;
    for (const auto &x: T.get_postorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    return -1;
};