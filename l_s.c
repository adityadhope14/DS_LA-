

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int size, target, found = 0;

    printf("Enter array size: ");
    scanf("%d", &size);

    int numbers[size]; 

    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        numbers[i] = (rand() % 10000) + 1;
    }
    
    printf("\nGenerated %d random numbers:\n", size);
    for (int i = 0; i < size; i++) {
        printf("%d ", numbers[i]);
    }

    printf("\nEnter number to search: ");
    scanf("%d", &target);

    clock_t start = clock();

    for (int i = 0; i < size; i++) {
        if (numbers[i] == target) {
            printf("\nSuccessful search: Found %d at index %d\n", target, i);
            found = 1;
            break;
        }
    }

    if (!found) printf("\nUnsuccessful search: Not found\n");

    clock_t end = clock();

    double time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;
    printf("Time taken: %.4f ms\n", time_ms);

    return 0;
}