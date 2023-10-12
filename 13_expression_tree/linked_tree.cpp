//
// Created by caiop on 12/10/2023.
//
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>
#include <climits>
#include <functional>
#include <queue>

struct Node {
    std::string value;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
};

class LinkedTree {
private:
    Node *root;
    unsigned _size;
public:
    LinkedTree() {
        root = new Node;
        _size = 0;
    };

    Node *getRoot() {
        return root;
    }

    void insertLeftChild(Node *parent, std::string c) {
        parent->left = new Node;
        parent->left->parent = parent;
        parent->left->value = c;
        ++_size;
    };

    void insertRightChild(Node *parent, std::string c) {
        parent->right = new Node;
        parent->right->parent = parent;
        parent->right->value = c;
        ++_size;
    };

    static Node *parent(Node *child) {
        return child->parent;
    };

    static Node *getLeftChildNode(Node *parent) {
        return parent->left;
    };

    static Node *getRightChildNode(Node *parent) {
        return parent->right;
    };

    unsigned size() {
        return _size;
    };

    int depth(Node *child) {
        if (child == nullptr)
            return 0;
        return 1 + depth(parent(child));
    }

    bool isLeaf(Node *node) {
        return node->left == nullptr && node->right == nullptr;
    }

    int height(Node *node) {
        if (isLeaf(node))
            return 0;

        int leftChildHeight = height(getLeftChildNode(node));
        int rightChildHeight = height(getRightChildNode(node));
        int maxChildHeight = std::max(leftChildHeight, rightChildHeight);

        return 1 + maxChildHeight;
    }

    void displayTree(Node *node, int depth = 0) {
        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }

        std::cout << node->value << std::endl;

        if (isLeaf(node))
            return;

        displayTree(LinkedTree::getLeftChildNode(node), depth + 1);
        displayTree(LinkedTree::getRightChildNode(node), depth + 1);
    };

    static void printNode(Node *node) {
        std::cout << node->value;
    }

    static void breadthFirstSearch(Node *node, const std::function<void(Node *)> &processFunc = printNode) {
        std::queue<Node *> queue;
        queue.push(node);
        while (not queue.empty()) {
            auto front = queue.front();
            queue.pop();
            processFunc(front);
            if (front->left != nullptr)
                queue.push(front->left);
            if (front->right != nullptr)
                queue.push(front->right);
        }
    }

    void preOrder(Node *node, const std::function<void(Node *)> &processFunc = printNode) {
        Node *leftChild = LinkedTree::getLeftChildNode(node);
        Node *rightChild = LinkedTree::getRightChildNode(node);

        processFunc(node);
        if (leftChild != nullptr)
            preOrder(leftChild, processFunc);
        if (rightChild != nullptr)
            preOrder(rightChild, processFunc);
    }

    void inlineOrder(Node *node, const std::function<void(Node *)> &processFunc = printNode) {
        Node *leftChild = LinkedTree::getLeftChildNode(node);
        Node *rightChild = LinkedTree::getRightChildNode(node);

        if (leftChild != nullptr)
            inlineOrder(leftChild, processFunc);
        processFunc(node);
        if (rightChild != nullptr)
            inlineOrder(rightChild, processFunc);
    }

    void posOrder(Node *node, const std::function<void(Node *)> &processFunc = printNode) {
        Node *leftChild = LinkedTree::getLeftChildNode(node);
        Node *rightChild = LinkedTree::getRightChildNode(node);

        if (leftChild != nullptr)
            posOrder(leftChild, processFunc);
        if (rightChild != nullptr)
            posOrder(rightChild, processFunc);
        processFunc(node);
    }

    static void deleteNode(Node *node) {
        delete node;
    }

    ~LinkedTree() {
        posOrder(root, deleteNode);
    };

};

class ArithmeticExpressionLinked {
private:
    LinkedTree tree;
    std::vector<std::unordered_set<char>> priorityOrder = {
            {'-', '+'}, // Least priority
            {'*', '/'}
    };

    int checkPriority(char c) {
        for (int i = 0; i < priorityOrder.size(); ++i) {
            if (priorityOrder[i].count(c) > 0)
                return i;
        }
        return priorityOrder.size();
    };

    void buildTree(Node *node) {
        std::string subexpression = node->value;

        if (subexpression.size() <= 1)
            return;

        // Priority value, char index, char value
        int leastPriorityValue = INT_MAX;
        int leastPriorityIndex = -1;

        for (int i = subexpression.size() - 1; i >= 0; --i) {
            char c = subexpression[i];
            int thisPriority = checkPriority(c);
            if (thisPriority < leastPriorityValue) {
                leastPriorityValue = thisPriority;
                leastPriorityIndex = i;
                node->value = c;
            }
            if (thisPriority == 0)
                break;
        };

        linkedTree.insertLeftChild(node, subexpression.substr(0, leastPriorityIndex));
        linkedTree.insertRightChild(node, subexpression.substr(leastPriorityIndex + 1, subexpression.size() - 1));
        buildTree(LinkedTree::getLeftChildNode(node));
        buildTree(LinkedTree::getRightChildNode(node));
    };

public:
    std::string expression;
    LinkedTree linkedTree;

    explicit ArithmeticExpressionLinked(const std::string &expression) {
        this->expression = expression;
        linkedTree.getRoot()->value = expression;
        buildTree(linkedTree.getRoot());
    };

    void displayTree() {
        tree.displayTree(linkedTree.getRoot());
        std::cout << std::endl;
    }

    void breadthFirstSearch() {
        LinkedTree::breadthFirstSearch(linkedTree.getRoot());
        std::cout << std::endl;
    }

    void preOrder() {
        tree.preOrder(linkedTree.getRoot());
        std::cout << std::endl;
    }

    void inlineOrder() {
        tree.inlineOrder(linkedTree.getRoot());
        std::cout << std::endl;
    }

    void posOrder() {
        tree.posOrder(linkedTree.getRoot());
        std::cout << std::endl;
    }

    int height() {
        return tree.height(linkedTree.getRoot());
    }

    int size() {
        return expression.size();
    }

    ~ArithmeticExpressionLinked() = default;
};
