#include <iostream>
#include <utility>
#include <vector>
#include <unordered_set>
#include <climits>
#include <queue>

class VectorTree {
private:
    std::vector<std::string> tree;
    unsigned capacity;

    void realoc_vector() {
        capacity *= 4;
        tree.resize(capacity);
    };

public:
    VectorTree() {
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
        std::string left = VectorTree::getLeftChildValue(index);
        std::string right = VectorTree::getRightChildValue(index);

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

        displayTree(VectorTree::getLeftChildIndex(index), depth + 1);
        displayTree(VectorTree::getRightChildIndex(index), depth + 1);
    };

    void breadthFirstSearchVector() {
        for (int i = 0; i < tree.size(); ++i) {
            if (!tree[i].empty())
                std::cout << tree[i];
        }
    }

    void breadthFirstSearchQueue() {
        std::queue<int> queue;
        queue.push(0);
        while (not queue.empty()) {
            auto front = queue.front();
            queue.pop();
            int leftChildIndex = VectorTree::getLeftChildIndex(front);
            int rightChildIndex = VectorTree::getRightChildIndex(front);
            std::cout << tree[front];
            if (!tree[leftChildIndex].empty())
                queue.push(leftChildIndex);
            if (!tree[rightChildIndex].empty())
                queue.push(rightChildIndex);
        }
    }

    void preOrder(int index = 0) {
        int leftChildIndex = VectorTree::getLeftChildIndex(index);
        int rightChildIndex = VectorTree::getRightChildIndex(index);

        std::cout << tree[index];
        if (!tree[leftChildIndex].empty())
            preOrder(leftChildIndex);
        if (!tree[rightChildIndex].empty())
            preOrder(rightChildIndex);
    }

    void inlineOrder(int index = 0) {
        int leftChildIndex = VectorTree::getLeftChildIndex(index);
        int rightChildIndex = VectorTree::getRightChildIndex(index);

        if (!tree[leftChildIndex].empty())
            inlineOrder(leftChildIndex);
        std::cout << tree[index];
        if (!tree[rightChildIndex].empty())
            inlineOrder(rightChildIndex);
    }

    void posOrder(int index = 0) {
        int leftChildIndex = VectorTree::getLeftChildIndex(index);
        int rightChildIndex = VectorTree::getRightChildIndex(index);

        if (!tree[leftChildIndex].empty())
            posOrder(leftChildIndex);
        if (!tree[rightChildIndex].empty())
            posOrder(rightChildIndex);
        std::cout << tree[index];
    }
};

class ArithmeticExpressionVector {
private:
    VectorTree tree;
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

        int left = VectorTree::getLeftChildIndex(index);
        int right = VectorTree::getRightChildIndex(index);
        buildTree(left, subexpression.substr(0, leastPriorityIndex));
        buildTree(right, subexpression.substr(leastPriorityIndex + 1, subexpression.size() - 1));
    };

public:
    std::string expression;

    explicit ArithmeticExpressionVector(const std::string &expression) {
        this->expression = expression;
        buildTree(0, expression);
    };

    void displayTree() {
        tree.displayTree();
        std::cout << std::endl;
    }

    void breadthFirstSearchQueue() {
        tree.breadthFirstSearchQueue();
        std::cout << std::endl;
    }

    void breadthFirstSearchVector() {
        tree.breadthFirstSearchVector();
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

    int height() {
        return tree.height(0);
    }

    int size() {
        return expression.size();
    }

    ~ArithmeticExpressionVector() = default;
};
