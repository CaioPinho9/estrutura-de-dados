#include <string>
#include <fstream>
#include <iostream>
#include <unordered_set>
#include <functional>
#include <filesystem>
#include <vector>
#include <chrono>

#define SIZE 8

class ChessBoard {
private:
    char board[SIZE][SIZE]{
            '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '.',
            '.', '.', '.', '.', '.', '.', '.', '.'
    };
    unsigned _sz = SIZE;

public:

    ChessBoard() = default;

    ChessBoard(std::string filename) {
        std::ifstream fd(filename);
        if (fd.is_open()) {
            std::string _char;
            unsigned count = 0;
            fd >> _char;
            while (fd) {
                board[count / size()][count % size()] = _char[0];
                fd.ignore(1); // Skip a space;
                ++count;
                fd >> _char;
            }
        }
    }

    char *operator[](unsigned i) {
        /* Enables the use of [] operator for ChessBoard objects
         */
        return board[i];
    }

    unsigned size() const {
        return _sz;
    }

    char get(unsigned i, unsigned j) const {
        return board[i][j];
    }

    unsigned get_npieces() const {
        unsigned count = 0;
        for (unsigned i = 0; i < size(); ++i) {
            for (unsigned j = 0; j < size(); ++j) {
                if (board[i][j] != '.') {
                    ++count;
                }
            }
        }
        return count;
    }

protected:
    friend bool operator==(const ChessBoard &board1, const ChessBoard &board2);
};


std::ostream &operator<<(std::ostream &out, const ChessBoard &board) {
    /* Enables the use of std::cout << board
     * to print the board. May be used for debugging.
     */
    for (auto i = 0u; i < board.size(); ++i) {
        for (auto j = 0u; j < board.size(); ++j) {
            out << board.get(i, j) << ' ';
        }
        out << '\n';
    }
    return out;
}

bool operator==(const ChessBoard &board1, const ChessBoard &board2) {
    for (unsigned i = 0; i < board1.size(); ++i) {
        for (unsigned j = 0; j < board1.size(); ++j) {
            if (board1.get(i, j) != board2.get(i, j)) {
                return false;
            }
        }
    }
    return true;
}

// struct chess_hash{
//     std::size_t operator() (const ChessBoard& board) const{
// 	return board.get_npieces();
//     }
// };


struct chess_hash {
    std::size_t operator()(const ChessBoard &board) const {
        // Preencha essa função. Ela deve retornar um valor inteiro positivo
        // que representa a função hash para um tabuleiro de xadrez.
        size_t hash = 0;
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                int c = board.get(x, y);
                int a = x ^ 1;
                int b = y ^ 1;

                hash += c * a * a * b * (a + b);
            }
        }
        return hash;
    }
};

std::vector <ChessBoard> load_boards(const std::string &_folder) {
    std::vector <ChessBoard> boards;
    boards.reserve(100000);
    std::filesystem::path folder(_folder);
    std::filesystem::directory_iterator directory_iterator(folder);
    unsigned count = 0;
    for (const auto &filename: directory_iterator) {
        if (filename.path().extension() == ".tab") {
            boards.push_back(ChessBoard(filename.path()));
            ++count;
        }
    }
    return boards;
}


void run_experiment(const std::string &folder_all,
                    const std::string &folder_candidates) {
    std::cout << "Loading the boards...\n";
    auto allboards = load_boards(folder_all);
    std::cout << "Running the experiments...\n";
    auto candbards = load_boards(folder_candidates);

    std::unordered_set <ChessBoard, chess_hash> allboards_set;
    std::unordered_set <ChessBoard, chess_hash> candboards_set;

    std::cout << "Read boards for base = " << allboards.size() << '\n'
              << "Read boards for search = " << candbards.size() << '\n';
    auto start_insertions = std::chrono::system_clock::now();
    for (const auto &b: allboards) {
        allboards_set.insert(b);
    }
    auto end_insertions = std::chrono::system_clock::now();
    std::cout << "Tempo para as insercoes\n";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end_insertions - start_insertions).count()
              << "ms\n";

    auto candboards = load_boards(folder_candidates);
    start_insertions = std::chrono::system_clock::now();
    for (const auto &b: candboards) {
        allboards_set.find(b);
    }
    end_insertions = std::chrono::system_clock::now();
    std::cout << "Tempo para as buscas\n";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end_insertions - start_insertions).count()
              << "ms\n";
}


int main() {
    run_experiment("../dataset/all", "../dataset/candidates");
    return 0;
}
