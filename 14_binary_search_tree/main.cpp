//
// Created by caiop on 20/10/2023.
//
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <queue>

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
        _insert(&root, key, nullptr);
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
        while (node->left() != nullptr) {
            node = node->left();
        }
        return node;
    }

    Node<TKey, TValue> *max() const {
        auto node = root;
        while (node->right() != nullptr) {
            node = node->right();
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

    void print_plot_string() {
        std::cout << "BFS:\n";
        std::queue<Node<TKey, TValue> *> queue;

        queue.push(root);
        unsigned max_height = height();

        while (!queue.empty()) {
            auto currentNode = queue.front();
            queue.pop();
            if (currentNode == nullptr)
                break;

            if (currentNode->get_key() == INT32_MIN) {
                std::cout << "# ";
            } else {
                std::cout << currentNode->get_key() << " ";
            }

            auto left = currentNode->left();
            auto right = currentNode->right();

            if (left == nullptr && max_height - 1 != currentNode->_height) {
                left = new Node<int, int>(INT32_MIN);
                left->_height = currentNode->_height + 1;
            }
            if (right == nullptr && max_height - 1 != currentNode->_height) {
                right = new Node<int, int>(INT32_MIN);
                right->_height = currentNode->_height + 1;
            }

            queue.push(left);
            queue.push(right);
        }
        std::cout << std::endl;
    }

    void print_node(Node<TKey, TValue> *node) {
        std::cout << node->get_key() << std::endl;
    }

    void print_nodes(std::list<TKey> nodes) {
        for (auto value: nodes) {
            std::cout << std::to_string(value) << " ";
        }
        std::cout << std::endl;
    }

    ~LinkedBinaryTree() = default;

private:
    void _insert(Node<TKey, TValue> **node, TKey key, Node<TKey, TValue> *parent) {
        if (*node == nullptr) {
            auto *newNode = new Node<TKey, TValue>(key, nullptr, nullptr, parent);
            if (parent != nullptr)
                newNode->_height = parent->_height + 1;
            *node = newNode;
            return;
        }
        (*node)->_size++;
        if (key <= (*node)->get_key()) {
            _insert(&((*node)->_left), key, *node);
        } else {
            _insert(&((*node)->_right), key, *node);
        }
    }

    void _remove(Node<TKey, TValue> *node) {
        if (node == nullptr)
            return;

        auto left = node->left();
        auto right = node->right();

        if (left == nullptr && right == nullptr) {
            auto parent = node->parent();
            if (node->get_key() <= parent->get_key()) {
                parent->_left = nullptr;
            } else {
                parent->_right = nullptr;
            }
            delete node;
        } else if (left == nullptr) {
            auto parent = node->parent();

            if (node->get_key() <= parent->get_key()) {
                parent->_left = right;
            } else {
                parent->_right = right;
            }
            right->_height = node->_height;
            right->_parent = parent;

            delete node;

            _decrease_height(right->left());
            _decrease_height(right->right());
        } else {
            node->_size--;
            auto cursor = node->right();

            while (cursor->left() != nullptr) {
                cursor->_size--;
                cursor = cursor->left();
            }

            auto cursor_key =cursor->_key;
            auto cursor_value =cursor->_value;

            _remove(cursor);
            node->_key = cursor_key;
            node->_value = cursor_value;
        }
    }

    unsigned _height(Node<TKey, TValue> *node) {
        if (node == nullptr)
            return 0;

        auto left = node->left();
        auto right = node->right();

        return std::max(_height(left), _height(right)) + 1;
    }

    Node<TKey, TValue> *_find(Node<TKey, TValue> *node, TKey key) {
        if (node == nullptr)
            return nullptr;

        auto currentKey = node->get_key();

        if (currentKey == key) {
            return node;
        } else if (key <= currentKey) {
            return _find(node->left(), key);
        } else {
            return _find(node->right(), key);
        }
    }

    void _get_preorder(Node<TKey, TValue> *node, std::list<TKey> &nodes) {
        if (node == nullptr)
            return;

        auto left = node->left();
        auto right = node->right();

        nodes.push_back(node->get_key());
        _get_preorder(left, nodes);
        _get_preorder(right, nodes);
    }

    void _get_posorder(Node<TKey, TValue> *node, std::list<TKey> &nodes) {
        if (node == nullptr)
            return;

        auto left = node->left();
        auto right = node->right();

        _get_posorder(left, nodes);
        _get_posorder(right, nodes);
        nodes.push_back(node->get_key());
    }

    void _get_inorder(Node<TKey, TValue> *node, std::list<TKey> &nodes) {
        if (node == nullptr)
            return;

        auto left = node->left();
        auto right = node->right();

        _get_inorder(left, nodes);
        nodes.push_back(node->get_key());
        _get_inorder(right, nodes);
    }

    void _decrease_height(Node<TKey, TValue> *node) {
        if (node == nullptr)
            return;

        node->_height--;

        _decrease_height(node->left());
        _decrease_height(node->right());
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
    TKey _key;
    TValue _value;

public:
    Node() = default;

    // We are using the list initializer of the parameters.
    Node(TKey _k) :
            _key(_k), _left(nullptr), _right(nullptr) {}

    Node(TKey _k, Node *__left, Node *__right, Node *__parent) :
            _key(_k), _left(__left), _right(__right), _parent(__parent) {}

    TKey get_key() const { return _key; };

    TKey get_value() const { return _value; };

    TKey get_size() const { return _size; };

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

int main() {
    std::vector<int> items = {50, 20, 75, 10, 40, 60, 80, 15, 55, 65, 100, 120};
    LinkedBinaryTree<int, int> T;
    for (const auto &i: items) {
        T.insert(i);
    }

    T.print_plot_string();

    std::cout << "Pre-order:\n";
    for (const auto &x: T.get_preorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    std::cout << "In-order:\n";
    for (const auto &x: T.get_inorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::cout << "Post-order:\n";
    for (const auto &x: T.get_postorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::cout << "Max = " << T.max()->get_key() << std::endl;
    std::cout << "Min = " << T.min()->get_key() << std::endl;

    std::cout << "Removing 65\n";
    T.remove(65);
    T.print_plot_string();
    std::cout << "Pre-order:\n";
    for (const auto &x: T.get_preorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    std::cout << "In-order:\n";
    for (const auto &x: T.get_inorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::cout << "Post-order:\n";
    for (const auto &x: T.get_postorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::cout << "Removing 80\n";
    T.remove(80);
    T.print_plot_string();
    std::cout << "Pre-order:\n";
    for (const auto &x: T.get_preorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    std::cout << "In-order:\n";
    for (const auto &x: T.get_inorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::cout << "Post-order:\n";
    for (const auto &x: T.get_postorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    std::cout << "Removing 75\n";
    T.remove(75);
    T.print_plot_string();
    std::cout << "Pre-order:\n";
    for (const auto &x: T.get_preorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;
    std::cout << "In-order:\n";
    for (const auto &x: T.get_inorder()) {
        std::cout << x << ' ';
    }

    std::cout << std::endl;
    std::cout << "Post-order:\n";
    for (const auto &x: T.get_postorder()) {
        std::cout << x << ' ';
    }
    std::cout << std::endl;

    return -1;
};