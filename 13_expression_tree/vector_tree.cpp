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
        if (capacity > 30000000)
            throw std::exception("to big capacity");
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

    int depth(int index) {
        if (index == 0)
            return 0;
        return 1 + depth(parent(index));
    }

    bool isLeaf(int index) {
        if (index > capacity)
            return true;

        bool left = !nodeExists(VectorTree::getLeftChildIndex(index));
        bool right = !nodeExists(VectorTree::getLeftChildIndex(index));

        return left && right;
    }

    int height(int index) {
        if (isLeaf(index))
            return 0;

        int leftChildHeight = height(getLeftChildIndex(index));
        int rightChildHeight = height(getRightChildIndex(index));
        int maxChildHeight = std::max(leftChildHeight, rightChildHeight);

        return 1 + maxChildHeight;
    }

    bool nodeExists(int index) {
        return index < capacity and !tree[index].empty();
    }

    void displayTree(int index = 0, int depth = 0) {
        if (tree[index].empty())
            return;

        for (int i = 0; i < depth; i++) {
            std::cout << "  ";
        }

        std::cout << tree[index] << std::endl;

        int leftChildIndex = VectorTree::getLeftChildIndex(index);
        int rightChildIndex = VectorTree::getRightChildIndex(index);
        if (nodeExists(leftChildIndex))
            displayTree(leftChildIndex, depth + 1);
        if (nodeExists(rightChildIndex))
            displayTree(rightChildIndex, depth + 1);
    };

    void breadthFirstSearchVector() {
        for (int i = 0; i < tree.size(); ++i) {
            if (nodeExists(i))
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
            if (nodeExists(leftChildIndex))
                queue.push(leftChildIndex);
            if (nodeExists(rightChildIndex))
                queue.push(rightChildIndex);
        }
    }

    void preOrder(int index = 0) {
        int leftChildIndex = VectorTree::getLeftChildIndex(index);
        int rightChildIndex = VectorTree::getRightChildIndex(index);

        std::cout << tree[index];
        if (nodeExists(leftChildIndex))
            preOrder(leftChildIndex);
        if (nodeExists(rightChildIndex))
            preOrder(rightChildIndex);
    }

    void inlineOrder(int index = 0) {
        int leftChildIndex = VectorTree::getLeftChildIndex(index);
        int rightChildIndex = VectorTree::getRightChildIndex(index);

        if (nodeExists(leftChildIndex))
            inlineOrder(leftChildIndex);
        std::cout << tree[index];
        if (nodeExists(rightChildIndex))
            inlineOrder(rightChildIndex);
    }

    void posOrder(int index = 0) {
        int leftChildIndex = VectorTree::getLeftChildIndex(index);
        int rightChildIndex = VectorTree::getRightChildIndex(index);

        if (nodeExists(leftChildIndex))
            posOrder(leftChildIndex);
        if (nodeExists(rightChildIndex))
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
        tree = VectorTree();
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
};
