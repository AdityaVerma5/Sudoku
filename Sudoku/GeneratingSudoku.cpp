#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

const int BOARD_SIZE = 9;
const int EMPTY_CELL = 0;
const int NUM_DIGITS = 9;
const int BLANK_SPACES = 50; // Number of blank spaces in the generated puzzle

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

// Function to generate a random Sudoku puzzle with blank spaces
void generateSudoku(std::vector<std::vector<int>>& board) {
    // Initialize the board with empty cells
    board.assign(BOARD_SIZE, std::vector<int>(BOARD_SIZE, EMPTY_CELL));

    // Generate a random permutation of digits
    std::vector<int> digits(NUM_DIGITS);
    for (int i = 0; i < NUM_DIGITS; i++)
        digits[i] = i + 1;

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(digits.begin(), digits.end(), rng);

    // Fill the main diagonal of each 3x3 box with the shuffled digits
    for (int i = 0; i < BOARD_SIZE; i += 3) {
        for (int j = 0; j < BOARD_SIZE; j += 3) {
            int index = 0;
            for (int k = i; k < i + 3; k++) {
                for (int l = j; l < j + 3; l++) {
                    board[k][l] = digits[index];
                    index = (index + 1) % NUM_DIGITS;
                }
            }
        }
    }

    // Randomly remove digits to create blank spaces
    std::vector<std::pair<int, int>> blankPositions;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            blankPositions.push_back(std::make_pair(i, j));
        }
    }

    std::shuffle(blankPositions.begin(), blankPositions.end(), rng);

    for (int i = 0; i < BLANK_SPACES; i++) {
        int row = blankPositions[i].first;
        int col = blankPositions[i].second;
        board[row][col] = EMPTY_CELL;
    }
}

int main() {
    std::vector<std::vector<int>> board(BOARD_SIZE, std::vector<int>(BOARD_SIZE));

    // Generate a Sudoku puzzle with blank spaces
    generateSudoku(board);

    // Print the generated puzzle
    std::cout << "Generated Sudoku Puzzle:" << std::endl;
    printBoard(board);

    return 0;
}
