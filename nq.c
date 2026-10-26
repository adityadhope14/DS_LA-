#include <stdio.h>
#include <stdbool.h>

#define MAX 20

int board[MAX][MAX];
int N;
int totalSolutions = 0;
int totalRecursiveCalls = 0;
int totalBacktracks = 0;

// Helper function to print indentation based on recursion depth (row)
void printIndent(int depth) {
    for (int i = 0; i < depth; i++) {
        printf("  | ");
    }
}

// Function to print the N x N chessboard and Queen positions appealingly
void printSolution() {
    totalSolutions++;
    printf("\n========================================================\n");
    printf("              👑 COMBINATION / SOLUTION #%d 👑\n", totalSolutions);
    printf("========================================================\n");

    // 1. Print exact coordinates of each Queen (1-based indexing for readability)
    printf("\n📍 Queen Positions (Row, Column):\n");
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            if (board[r][c] == 1) {
                printf("   -> Queen %d is placed at Row %d, Column %d  [Pos: (%d, %d)]\n",
                       r + 1, r + 1, c + 1, r + 1, c + 1);
            }
        }
    }

    // 2. Print the visual N x N Board
    printf("\n📋 Visual %d x %d Chessboard:\n\n", N, N);

    // Print column headers
    printf("      ");
    for (int c = 0; c < N; c++) {
        printf(" C%-2d", c + 1);
    }
    printf("\n");

    // Print top border
    printf("     +");
    for (int c = 0; c < N; c++) {
        printf("---+");
    }
    printf("\n");

    // Print each row
    for (int r = 0; r < N; r++) {
        printf("  R%-2d|", r + 1);
        for (int c = 0; c < N; c++) {
            if (board[r][c] == 1) {
                printf(" Q |"); // Queen placed here
            } else {
                printf(" . |"); // Empty space
            }
        }
        printf("\n");

        // Print row separator border
        printf("     +");
        for (int c = 0; c < N; c++) {
            printf("---+");
        }
        printf("\n");
    }
    printf("========================================================\n\n");
}

// Function to check if a Queen can be safely placed at board[row][col]
bool isSafe(int row, int col) {
    int i, j;

    // Check vertically above in the same column
    for (i = 0; i < row; i++) {
        if (board[i][col] == 1)
            return false;
    }

    // Check upper-left diagonal
    for (i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1)
            return false;
    }

    // Check upper-right diagonal
    for (i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1)
            return false;
    }

    return true; // Position is safe
}

// Recursive function to place Queens row by row
void solveNQueens(int row) {
    totalRecursiveCalls++;

    // Print the recursive call entry
    printIndent(row);
    printf("[Recursive Call #%d] Entering solveNQueens(Row %d)\n",
           totalRecursiveCalls, row + 1);

    // Base Case: If all N Queens are placed (row reaches N), print the board!
    if (row == N) {
        printIndent(row);
        printf("🎉 Base Case Reached! All %d Queens placed safely.\n", N);
        printSolution();
        return;
    }

    // Try placing a Queen in each column of the current row
    for (int col = 0; col < N; col++) {
        printIndent(row);
        printf("-> Trying Queen %d at (Row %d, Col %d)... ", row + 1, row + 1, col + 1);

        if (isSafe(row, col)) {
            printf("SAFE! Placing Queen %d.\n", row + 1);
            board[row][col] = 1; // Place Queen

            // Recursive call to place the next Queen in the next row
            solveNQueens(row + 1);

            // Backtrack: Remove the Queen to explore other combinations
            board[row][col] = 0;
            totalBacktracks++;
            printIndent(row);
            printf("<< [Backtrack] Removed Queen %d from (Row %d, Col %d) to find more combinations.\n",
                   row + 1, row + 1, col + 1);
        } else {
            printf("CONFLICT (Attacked by an earlier Queen).\n");
        }
    }

    printIndent(row);
    printf("[Return] Finished trying all columns for Row %d.\n", row + 1);
}

int main() {
    printf("========================================================\n");
    printf("           👑 N-QUEENS SOLVER (WITH TRACE) 👑\n");
    printf("========================================================\n");
    printf("Enter the number of Queens / Board Size N (e.g., 5): ");
    scanf("%d", &N);

    if (N <= 0 || N > MAX) {
        printf("Please enter a board size between 1 and %d.\n", MAX);
        return 1;
    }

    // Initialize the board with 0 (empty)
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++) {
            board[r][c] = 0;
        }
    }

    printf("\n--- Starting Recursive Search for %d x %d Board ---\n\n", N, N);

    // Start recursion from the first row (index 0)
    solveNQueens(0);

    // Final Summary Box
    printf("\n========================================================\n");
    printf("                   📊 FINAL SUMMARY 📊\n");
    printf("========================================================\n");
    printf("  Board Dimensions       : %d x %d\n", N, N);
    printf("  Total Combinations     : %d\n", totalSolutions);
    printf("  Total Recursive Calls  : %d\n", totalRecursiveCalls);
    printf("  Total Backtrack Steps  : %d\n", totalBacktracks);
    printf("========================================================\n");

    return 0;
}