#include <stdio.h>

// Global variable to keep track of the step number in the terminal
int stepCount = 0;

// Recursive function to move plates between branches
void towerOfHanoi(int n, char fromBranch, char toBranch, char auxBranch) {
    // Base Case: If there is only 1 plate left, move it directly
    if (n == 1) {
        stepCount++;
        printf("Step %d: Move Plate 1 from Branch %c to Branch %c\n", 
               stepCount, fromBranch, toBranch);
        return;
    }

    // Step 1: Move top (n - 1) plates from Starting Branch to Helper (Aux) Branch
    towerOfHanoi(n - 1, fromBranch, auxBranch, toBranch);

    // Step 2: Move the current largest plate (Plate n) to the Destination Branch
    stepCount++;
    printf("Step %d: Move Plate %d from Branch %c to Branch %c\n", 
           stepCount, n, fromBranch, toBranch);

    // Step 3: Move the (n - 1) plates from Helper (Aux) Branch to Destination Branch
    towerOfHanoi(n - 1, auxBranch, toBranch, fromBranch);
}

int main() {
    int n;

    // Ask the user for the number of plates
    printf("Enter the number of plates (e.g., 8): ");
    scanf("%d", &n);

    // Check for valid input
    if (n <= 0) {
        printf("Please enter a number greater than 0.\n");
        return 1;
    }

    printf("\n--- Starting Tower of Hanoi with %d Plates ---\n", n);
    printf("Branches: A (Start), B (Helper), C (Destination)\n\n");

    // Call the function with Branches A, C (Destination), and B (Helper)
    towerOfHanoi(n, 'A', 'C', 'B');

    printf("\n--- Completed! Total steps taken: %d ---\n", stepCount);

    return 0;
}