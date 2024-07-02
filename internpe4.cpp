#include <iostream>
#include <vector>

const int ROWS = 6;  // Number of rows in the board
const int COLS = 7;  // Number of columns in the board

// Function to print the game board
void printBoard(const std::vector<std::vector<char> > &board) {
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS; ++c) {
            std::cout << "| " << board[r][c] << " ";
        }
        std::cout << "|\n";
    }
    for (int c = 0; c < COLS; ++c) {
        std::cout << "----";
    }
    std::cout << "-\n";
    for (int c = 0; c < COLS; ++c) {
        std::cout << "  " << c << " ";
    }
    std::cout << "\n";
}

// Function to check if a move is valid
bool isValidMove(const std::vector<std::vector<char> > &board, int col) {
    return col >= 0 && col < COLS && board[0][col] == ' ';
}

// Function to make a move for the current player
bool makeMove(std::vector<std::vector<char> > &board, int col, char player) {
    if (!isValidMove(board, col)) return false;
    for (int r = ROWS - 1; r >= 0; --r) {
        if (board[r][col] == ' ') {
            board[r][col] = player;
            return true;
        }
    }
    return false;
}

// Function to check if the current player has won
bool checkWin(const std::vector<std::vector<char> > &board, char player) {
    // Check horizontal, vertical, and diagonal (both directions) win conditions
    for (int r = 0; r < ROWS; ++r) {
        for (int c = 0; c < COLS - 3; ++c) {
            if (board[r][c] == player && board[r][c + 1] == player && 
                board[r][c + 2] == player && board[r][c + 3] == player) {
                return true;
            }
        }
    }

    for (int r = 0; r < ROWS - 3; ++r) {
        for (int c = 0; c < COLS; ++c) {
            if (board[r][c] == player && board[r + 1][c] == player && 
                board[r + 2][c] == player && board[r + 3][c] == player) {
                return true;
            }
        }
    }

    for (int r = 0; r < ROWS - 3; ++r) {
        for (int c = 0; c < COLS - 3; ++c) {
            if (board[r][c] == player && board[r + 1][c + 1] == player && 
                board[r + 2][c + 2] == player && board[r + 3][c + 3] == player) {
                return true;
            }
        }
    }

    for (int r = 3; r < ROWS; ++r) {
        for (int c = 0; c < COLS - 3; ++c) {
            if (board[r][c] == player && board[r - 1][c + 1] == player && 
                board[r - 2][c + 2] == player && board[r - 3][c + 3] == player) {
                return true;
            }
        }
    }

    return false;
}

// Function to check if the board is full
bool isBoardFull(const std::vector<std::vector<char> > &board) {
    for (int c = 0; c < COLS; ++c) {
        if (board[0][c] == ' ') {
            return false;
        }
    }
    return true;
}

int main() {
    std::vector<std::vector<char> > board(ROWS, std::vector<char>(COLS, ' '));
    char players[2] = {'X', 'O'};  // Player symbols
    int currentPlayer = 0;  // Index to keep track of the current player
    bool gameWon = false;  // Flag to check if the game is won

    while (!gameWon && !isBoardFull(board)) {
        printBoard(board);
        int move;
        std::cout << "Player " << players[currentPlayer] << ", enter your move (0-" << COLS-1 << "): ";
        std::cin >> move;

        if (makeMove(board, move, players[currentPlayer])) {
            if (checkWin(board, players[currentPlayer])) {
                gameWon = true;
            } else {
                currentPlayer = (currentPlayer + 1) % 2;  // Switch player
            }
        } else {
            std::cout << "Invalid move. Try again.\n";
        }
    }

    printBoard(board);

    if (gameWon) {
        std::cout << "Player " << players[currentPlayer] << " wins!\n";
    } else {
        std::cout << "It's a draw!\n";
    }

    return 0;
}
