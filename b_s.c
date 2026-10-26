//NAME: ADITYA MADHUKAR DHOPE 
//PRN: 258109072

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int size, target;
    int low, high, mid;
    int found = 0;
    int comparisons = 0;

    printf("Enter array size: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid size entered.\n");
        return 1;
    }

    int numbers[size];

    srand(time(NULL));

    int val = (rand() % 10) + 1;
    for (int i = 0; i < size; i++) {
        numbers[i] = val;
        val += (rand() % 10) + 1; 
    }

    printf("\nGenerated %d sorted numbers\n", size);
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }

    printf("\n\nEnter element to search: ");
    scanf("%d", &target);

    clock_t start_time = clock();

    low = 0;
    high = size - 1;

    printf("\n--- Step-by-Step Binary Search Execution ---\n");

    while (low <= high) {
        mid = (low + high) / 2;
        comparisons++;

        printf("\n[Comparison %d]\n", comparisons);
        printf("  Current Range : low = %d, high = %d --> mid = %d\n", low, high, mid);
        printf("  Comparing     : numbers[%d] (%d) with target (%d)\n", mid, numbers[mid], target);

        if (numbers[mid] == target) {
            printf("  Action        : Match found! (%d == %d)\n", numbers[mid], target);
            printf("\nSuccessful search: Found %d at index %d!\n", target, mid);
            found = 1;
            break;
        }
        else if (numbers[mid] < target) {
            printf("  Result        : %d < %d (Target is in the right half)\n", numbers[mid], target);
            printf("  Shifting      : low shifted from %d to %d (mid + 1), high remains %d\n", low, mid + 1, high);
            low = mid + 1; 
        }
        else {
            printf("  Result        : %d > %d (Target is in the left half)\n", numbers[mid], target);
            printf("  Shifting      : high shifted from %d to %d (mid - 1), low remains %d\n", high, mid - 1, low);
            high = mid - 1; 
        }
    }

    if (!found) {
        printf("\n  Search Space Exhausted: low (%d) > high (%d)\n", low, high);
        printf("\nUnsuccessful search: Element %d was not found in the array.\n", target);
    }

    clock_t end_time = clock();

    double time_taken_ms = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;

    printf("--------------------------------------------\n");
    printf("Total comparisons made   : %d\n", comparisons);
    printf("Binary Search time taken : %.6f milliseconds\n", time_taken_ms);

    return 0;
}