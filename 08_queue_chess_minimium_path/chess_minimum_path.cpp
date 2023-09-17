//
// Created by caiop on 16/09/2023.
//

#include <iostream>
#include <unordered_map>
#include <vector>

// Defines a square as a pair (row, col):
struct Square {
    unsigned row;
    unsigned col;

    Square() = default;

    Square(unsigned r, unsigned c) {
        row = r;
        col = c;
    }
};


class Queue {
private:
    unsigned currentSize, head, tail, capacity;
    Square *array;
public:
    Queue() {
        currentSize = 0;
        head = 0;
        tail = 0;
        capacity = 30;
        array = new Square[capacity];
    }

    void push(Square x) {
        if ((tail + 1) % capacity == head)
            realoc_array();

        array[tail] = x;
        tail = (tail + 1) % capacity;
        currentSize++;
    }

    Square pop() {
        Square x = array[head];
        head = (head + 1) % capacity;
        currentSize--;
        return x;
    }

    Square front() {
        return array[head];
    }

    Square back() {
        return array[(tail - 1) % capacity];
    }

    unsigned size() const {
        return currentSize;
    }

    bool empty() const {
        return currentSize == 0;
    }

    void print() {
        for (int i = 0; i < currentSize; ++i) {
            Square x = pop();
            std::cout << '(' << x.col << ',' << x.row << ')';
            push(x);
        }
        std::cout << '\n';
    }

private:
    void realoc_array() {
        capacity *= 2;
        auto *aux_array = new Square[capacity];
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


class ChessBoard {
private:
    int board[8][8] = {
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1,
            -1, -1, -1, -1, -1, -1, -1, -1
    };
    unsigned int _sz = 8;
public:
    unsigned int size() const {
        return _sz;
    }

    int *operator[](unsigned i) {
        /* Enables the use of [] operator for ChessBoard objects */
        return board[i];
    }

};

std::ostream &operator<<(std::ostream &out, ChessBoard &board) {
    /* Enables the use of std::cout << board
     * to print the board.
     * May be used for debugging.
     */
    for (auto i = 0u; i < board.size(); ++i) {
        for (auto j = 0u; j < board.size(); ++j) {
            out << board[i][j] << ' ';
        }
        out << '\n';
    }
    return out;
}

bool square_valid(const Square &s, const ChessBoard &board) {
    // Since weare using unsigned for the squares,there is no need to check
    // whether values are >=0.
    unsigned n = board.size();
    return s.row < n and s.col < n;
}

std::vector<Square> getPossibleMoves(const Square &square, const ChessBoard &board) {
    // Returns all the possible moves of a knight according to its current position
    std::vector<Square> possiblePositions;

    // The move os a knight is always 2 in one direction and 1 in the other
    // So we loop around all combinations between -2 and 2 for both directions
    // The sum of the absolute values needs to be 3
    for (int i = -2; i <= 2; ++i) {
        for (int j = -2; j <= 2; ++j) {
            if (abs(i) + abs(j) == 3) {
                Square newSquare = Square(square.row + i, square.col + j);

                if (square_valid(newSquare, board))
                    possiblePositions.push_back(newSquare);
            }
        }
    }
    return possiblePositions;
}

unsigned get_knight_path_length(const Square &origin, const Square &dest) {
    //The solution goes here...
    ChessBoard distancesBoard;
    Queue Q;
    distancesBoard[origin.col][origin.row] = 0;
    Q.push(origin);
    while (not Q.empty()) {
        auto thisSquare = Q.front();
        std::vector<Square> possibleMoves = getPossibleMoves(thisSquare, distancesBoard);
        Q.pop();
        for (auto possiblePos: possibleMoves) {
            if (distancesBoard[possiblePos.col][possiblePos.row] == -1) {
                distancesBoard[possiblePos.col][possiblePos.row] = distancesBoard[thisSquare.col][thisSquare.row] + 1;
                Q.push(possiblePos);
            }
            // Returns early arriving at destination
            if (possiblePos.col == dest.col and possiblePos.row == dest.row)
                return distancesBoard[dest.col][dest.row];
        }
    }
    return -1;
}

int main() {
    //Used to map the squares as char to indices of the board
    std::unordered_map<char, unsigned> table = {
            {'a', 0},
            {'b', 1},
            {'c', 2},
            {'d', 3},
            {'e', 4},
            {'f', 5},
            {'g', 6},
            {'h', 7}
    };
    char icol, ocol;
    unsigned irow, orow;
    std::cin >> icol >> irow;
    std::cin.ignore(1);
    //Skip the '\n' char at the input;
    std::cin >> ocol >> orow;
    Square origin(irow - 1, table[icol]);
    Square dest(orow - 1, table[ocol]);
    unsigned nmoves = get_knight_path_length(origin, dest);
    std::cout << "Movimentos: " << nmoves << '\n';
    return 0;
}