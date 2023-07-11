#include <iostream>
#include <vector>

const int BOARD_SIZE = 9;
const int EMPTY_CELL = 0;

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

// Function to validate a Sudoku puzzle
bool validateSudoku(const std::vector<std::vector<int>>& board) {
    // Check each row and column
    for (int i = 0; i < BOARD_SIZE; i++) {
        std::vector<bool> rowCheck(BOARD_SIZE + 1, false);
        std::vector<bool> colCheck(BOARD_SIZE + 1, false);

        for (int j = 0; j < BOARD_SIZE; j++) {
            int numRow = board[i][j];
            int numCol = board[j][i];

            // Check row and column duplicates
            if (numRow != EMPTY_CELL) {
                if (rowCheck[numRow])
                    return false;
                rowCheck[numRow] = true;
            }

            if (numCol != EMPTY_CELL) {
                if (colCheck[numCol])
                    return false;
                colCheck[numCol] = true;
            }
        }
    }

    // Check each 3x3 box
    for (int i = 0; i < BOARD_SIZE; i += 3) {
        for (int j = 0; j < BOARD_SIZE; j += 3) {
            std::vector<bool> boxCheck(BOARD_SIZE + 1, false);

            for (int k = i; k < i + 3; k++) {
                for (int l = j; l < j + 3; l++) {
                    int num = board[k][l];

                    if (num != EMPTY_CELL) {
                        if (boxCheck[num])
                            return false;
                        boxCheck[num] = true;
                    }
                }
            }
        }
    }

    return true;
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

    // Validate the Sudoku puzzle
    if (validateSudoku(board)) {
        std::cout << "The Sudoku puzzle is valid." << std::endl;
    } else {
        std::cout << "The Sudoku puzzle is invalid." << std::endl;
    }

    return 0;
}
