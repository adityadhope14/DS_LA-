
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printSubArray(int arr[], int start, int end) {
    printf("[ ");
    for (int i = start; i <= end; i++) {
        printf("%d ", arr[i]);
    }
    printf("]");
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    printf("\n  --> MERGING Left ");
    printSubArray(L, 0, n1 - 1);
    printf(" and Right ");
    printSubArray(R, 0, n2 - 1);
    printf("\n");

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            printf("      Compare %d <= %d -> Pick %d\n", L[i], R[j], L[i]);
            arr[k] = L[i];
            i++;
        } else {
            printf("      Compare %d > %d  -> Pick %d\n", L[i], R[j], R[j]);
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        printf("      Take remaining from Left: %d\n", L[i]);
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        printf("      Take remaining from Right: %d\n", R[j]);
        arr[k] = R[j];
        j++;
        k++;
    }

    printf("  RESULT: Merged Subarray ");
    printSubArray(arr, left, right);
    printf("\n");
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        printf("\nDIVIDE: Splitting ");
        printSubArray(arr, left, right);
        printf(" into Left ");
        printSubArray(arr, left, mid);
        printf(" and Right ");
        printSubArray(arr, mid + 1, right);
        printf("\n");

        mergeSort(arr, left, mid);

        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    int size;

    printf("Enter array size: ");
    if (scanf("%d", &size) != 1 || size <= 0) {
        printf("Invalid size entered.\n");
        return 1;
    }

    int numbers[size];
    srand(time(NULL));

    int current_val = (rand() % 20) + 1;
    for (int i = 0; i < size; i++) {
        numbers[i] = current_val;
        current_val += (rand() % 15) + 1;
    }

    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    printf("\n==========================================");
    printf("\nINITIAL UNSORTED ARRAY: ");
    printSubArray(numbers, 0, size - 1);
    printf("\n==========================================\n");

    clock_t start_time = clock();

    mergeSort(numbers, 0, size - 1);

    clock_t end_time = clock();

    double time_taken_ms = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000.0;

    printf("\n==========================================");
    printf("\nFINAL SORTED ARRAY: ");
    printSubArray(numbers, 0, size - 1);
    printf("\n==========================================\n");

    printf("\nMerge Sort Execution Time: %.6f milliseconds (%.6f seconds)\n", 
           time_taken_ms, time_taken_ms / 1000.0);

    return 0;
}