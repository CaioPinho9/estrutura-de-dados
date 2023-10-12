#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>
#include <climits>

class Tree {
private:
    std::vector<std::string> tree;
    unsigned capacity;

    void realoc_vector() {
        capacity *= 4;
        tree.resize(capacity);
    };

public:
    Tree() {
        capacity = 100;
        tree.resize(capacity);
    };

    std::string &operator[](int index) {
        if (index >= tree.size()) {
            realoc_vector();
        }
        return tree[index];
    };

    static int parent(int index) {
        if (index == 0)
            return -1;

        return (index - 1) / 2;
    };

    static int getLeftChildIndex(int index) {
        return 2 * index + 1;
    };

    static int getRightChildIndex(int index) {
        return 2 * index + 2;
    };

    std::string getLeftChildValue(int index) {
        return tree[2 * index + 1];
    };

    std::string getRightChildValue(int index) {
        return tree[2 * index + 2];
    };

    int depth(int index) {
        if (index == 0)
            return 0;
        return 1 + depth(parent(index));
    }

    bool isLeaf(int index) {
        std::string left = Tree::getLeftChildValue(index);
        std::string right = Tree::getRightChildValue(index);

        return left.empty() && right.empty();
    }

    int height(int index) {
        if (isLeaf(index))
            return 0;

        int leftChildHeight = height(getLeftChildIndex(index));
        int rightChildHeight = height(getRightChildIndex(index));
        int maxChildHeight = std::max(leftChildHeight, rightChildHeight);

        return 1 + maxChildHeight;
    }

    void displayTree(int index = 0, int depth = 0) {
        if (tree[index].empty())
            return;

        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }

        std::cout << tree[index] << std::endl;

        displayTree(Tree::getLeftChildIndex(index), depth + 1);
        displayTree(Tree::getRightChildIndex(index), depth + 1);
    };

    void breadthFirstSearch() {
        for (int i = 0; i < tree.size(); ++i) {
            if (!tree[i].empty())
                std::cout << tree[i];
        }
    }

    void preOrder(int index = 0) {
        int leftChildIndex = Tree::getLeftChildIndex(index);
        int rightChildIndex = Tree::getRightChildIndex(index);

        std::cout << tree[index];
        if (!tree[leftChildIndex].empty())
            preOrder(leftChildIndex);
        if (!tree[rightChildIndex].empty())
            preOrder(rightChildIndex);
    }

    void inlineOrder(int index = 0) {
        int leftChildIndex = Tree::getLeftChildIndex(index);
        int rightChildIndex = Tree::getRightChildIndex(index);

        if (!tree[leftChildIndex].empty())
            inlineOrder(leftChildIndex);
        std::cout << tree[index];
        if (!tree[rightChildIndex].empty())
            inlineOrder(rightChildIndex);
    }

    void posOrder(int index = 0) {
        int leftChildIndex = Tree::getLeftChildIndex(index);
        int rightChildIndex = Tree::getRightChildIndex(index);

        if (!tree[leftChildIndex].empty())
            posOrder(leftChildIndex);
        if (!tree[rightChildIndex].empty())
            posOrder(rightChildIndex);
        std::cout << tree[index];
    }
};

class ArithmeticExpression {
private:
    Tree tree;
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

    void buildTree(int index, std::string subexpression) {
        tree[index] = subexpression;

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
                tree[index] = c;
            }
            if (thisPriority == 0)
                break;
        };

        int left = Tree::getLeftChildIndex(index);
        int right = Tree::getRightChildIndex(index);
        buildTree(left, subexpression.substr(0, leastPriorityIndex));
        buildTree(right, subexpression.substr(leastPriorityIndex + 1, subexpression.size() - 1));
    };

public:
    std::string expression;

    explicit ArithmeticExpression(const std::string &expression) {
        this->expression = expression;
        buildTree(0, expression);
    };

    void displayTree() {
        tree.displayTree();
        std::cout << std::endl;
    }

    void breadthFirstSearch() {
        tree.breadthFirstSearch();
        std::cout << std::endl;
    }

    void preOrder() {
        tree.preOrder();
        std::cout << std::endl;
    }

    void inlineOrder() {
        tree.inlineOrder();
        std::cout << std::endl;
    }

    void posOrder() {
        tree.posOrder();
        std::cout << std::endl;
    }
};

int main() {
    std::string expression = "A+B+C+D+E+F+G+H+I+J+K+L+M+N+O+P+Q+R+S+T+U+V+X+Y*Z";
//    std::cin >> expression;
    ArithmeticExpression arithmeticExpression(expression);

//    std::cout << expression << '\n';
//    std::cout << "displayTree:\n";
//    arithmeticExpression.displayTree();
//    std::cout << "breadthFirstSearch: ";
//    arithmeticExpression.breadthFirstSearch();
//    std::cout << "preOrder: ";
    arithmeticExpression.preOrder();
//    std::cout << "inlineOrder: ";
//    arithmeticExpression.inlineOrder();
//    std::cout << "posOrder: ";
    arithmeticExpression.posOrder();

    return 0;
}

