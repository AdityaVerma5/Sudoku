#include <iostream>
#include <vector>

const int BOARD_SIZE = 9;
const int EMPTY_CELL = 0;

// Function to print the Sudoku board
void printBoard(const std::vector<std::vector<int>>& board) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == EMPTY_CELL)
                std::cout << ". ";
            else
                std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if a move is valid
bool isValidMove(const std::vector<std::vector<int>>& board, int row, int col, int num) {
    // Check if the number already exists in the same row or column
    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board[row][i] == num || board[i][col] == num)
            return false;
    }

    // Check if the number already exists in the 3x3 box
    int boxStartRow = (row / 3) * 3;
    int boxStartCol = (col / 3) * 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[boxStartRow + i][boxStartCol + j] == num)
                return false;
        }
    }

    return true;
}

// Function to find an empty cell on the board
bool findEmptyCell(const std::vector<std::vector<int>>& board, int& row, int& col) {
    for (row = 0; row < BOARD_SIZE; row++) {
        for (col = 0; col < BOARD_SIZE; col++) {
            if (board[row][col] == EMPTY_CELL)
                return true;
        }
    }
    return false;
}

// Sudoku solver function using backtracking
bool solveSudoku(std::vector<std::vector<int>>& board) {
    int row, col;

    // Check if the Sudoku board is fully filled
    if (!findEmptyCell(board, row, col))
        return true;

    // Try placing a number (1-9) in the empty cell
    for (int num = 1; num <= 9; num++) {
        if (isValidMove(board, row, col, num)) {
            // If the move is valid, place the number in the cell
            board[row][col] = num;

            // Recursively call the solver function
            if (solveSudoku(board))
                return true;

            // If the solver function returns false, undo the current move
            board[row][col] = EMPTY_CELL;
        }
    }

    // Trigger backtracking
    return false;
}

int main() {
    std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE));

    // Input the Sudoku board from the user
    std::cout << "Enter the Sudoku board (use 0 or . for empty cells):" << std::endl;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cin >> board[i][j];
        }
    }

    // Solve the Sudoku puzzle
    if (solveSudoku(board)) {
        std::cout << "Sudoku solved successfully!" << std::endl;
        std::cout << "Solution:" << std::endl;
        printBoard(board);
    } else {
        std::cout << "No solution exists for the given Sudoku puzzle." << std::endl;
    }

    return 0;
}
