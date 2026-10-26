#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int total_pivots = 0;
int pivot_swaps = 0;
int total_comparisons = 0;
int step_count = 1;

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], (i == size - 1) ? "" : ", ");
    }
    printf("\n");
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high, int total_size) {
    int pivot = arr[high]; // Last element chosen as pivot
    total_pivots++;

    int i = low;
    int j = high - 1;

    while (1) {
        while (i <= high - 1) {
            total_comparisons++;
            if (arr[i] > pivot) break;
            i++;
        }

        while (j >= low) {
            total_comparisons++;
            if (arr[j] <= pivot) break;
            j--;
        }

        if (i < j) {
            swap(&arr[i], &arr[j]);
            printf("Step %d (Inward Swap %d <-> %d): ", step_count++, arr[j], arr[i]);
            printArray(arr, total_size);
        } else {
            break;
        }
    }

    if (high != i) {
        swap(&arr[high], &arr[i]);
        pivot_swaps++;
        printf("Step %d (Pivot %d placed at index %d): ", step_count++, pivot, i);
        printArray(arr, total_size);
    }

    return i;
}

void quickSort(int arr[], int low, int high, int total_size) {
    if (low < high) {
        int pi = partition(arr, low, high, total_size);

        quickSort(arr, low, pi - 1, total_size);
        quickSort(arr, pi + 1, high, total_size);
    }
}

int main() {
    int size;

    printf("Enter size of array: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid size entered.\n");
        return 1;
    }

    int numbers[size];
    srand(time(NULL));

    int current_val = (rand() % 15) + 1;
    for (int i = 0; i < size; i++) {
        numbers[i] = current_val;
        current_val += (rand() % 15) + 1; 
    }

    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(&numbers[i], &numbers[j]);
    }

    printf("\nInitial (Randomly Generated & Distinct): ");
    printArray(numbers, size);

    clock_t start_time = clock();

    quickSort(numbers, 0, size - 1, size);

    clock_t end_time = clock();

    double time_taken_ms = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;

    printf("Sorted:  ");
    printArray(numbers, size);

    printf("\nTotal pivots selected: %d\n", total_pivots);
    printf("Total comparisons made: %d\n", total_comparisons);
    printf("Total times pivot changed position: %d\n", pivot_swaps);
    printf("Execution Time: %.6f ms\n", time_taken_ms);

    return 0;
}