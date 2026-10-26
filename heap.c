

#include <stdio.h>
#include <time.h>

#define MAX 100

int minHeap[MAX], maxHeap[MAX];
int minSize = 0, maxSize = 0;

void insertMin(int value) {
    int i, temp;

    if (minSize == MAX) {
        printf("Min-Heap is full.\n");
        return;
    }

    i = minSize++;
    minHeap[i] = value;

    while (i > 0 && minHeap[(i - 1) / 2] > minHeap[i]) {
        temp = minHeap[i];
        minHeap[i] = minHeap[(i - 1) / 2];
        minHeap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void insertMax(int value) {
    int i, temp;

    if (maxSize == MAX) {
        printf("Max-Heap is full.\n");
        return;
    }

    i = maxSize++;
    maxHeap[i] = value;

    while (i > 0 && maxHeap[(i - 1) / 2] < maxHeap[i]) {
        temp = maxHeap[i];
        maxHeap[i] = maxHeap[(i - 1) / 2];
        maxHeap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

void deleteMin() {
    int i = 0, child, temp;

    if (minSize == 0) {
        printf("Min-Heap is empty.\n");
        return;
    }

    printf("Deleted from Min-Heap: %d\n", minHeap[0]);
    minHeap[0] = minHeap[--minSize];

    while (2 * i + 1 < minSize) {
        child = 2 * i + 1;

        if (child + 1 < minSize && minHeap[child + 1] < minHeap[child])
            child++;

        if (minHeap[i] <= minHeap[child])
            break;

        temp = minHeap[i];
        minHeap[i] = minHeap[child];
        minHeap[child] = temp;
        i = child;
    }
}

void deleteMax() {
    int i = 0, child, temp;

    if (maxSize == 0) {
        printf("Max-Heap is empty.\n");
        return;
    }

    printf("Deleted from Max-Heap: %d\n", maxHeap[0]);
    maxHeap[0] = maxHeap[--maxSize];

    while (2 * i + 1 < maxSize) {
        child = 2 * i + 1;

        if (child + 1 < maxSize && maxHeap[child + 1] > maxHeap[child])
            child++;

        if (maxHeap[i] >= maxHeap[child])
            break;

        temp = maxHeap[i];
        maxHeap[i] = maxHeap[child];
        maxHeap[child] = temp;
        i = child;
    }
}

void displayMin() {
    int i;

    if (minSize == 0) {
        printf("Min-Heap is empty.\n");
        return;
    }

    printf("Min-Heap: ");
    for (i = 0; i < minSize; i++)
        printf("%d ", minHeap[i]);
    printf("\n");
}

void displayMax() {
    int i;

    if (maxSize == 0) {
        printf("Max-Heap is empty.\n");
        return;
    }

    printf("Max-Heap: ");
    for (i = 0; i < maxSize; i++)
        printf("%d ", maxHeap[i]);
    printf("\n");
}

int main() {
    int choice, value;
    clock_t startTime, endTime;
    double executionTime;

    startTime = clock();

    do {
        printf("\n===== MIN-HEAP AND MAX-HEAP MENU =====\n");
        printf("1. Insert into Min-Heap\n");
        printf("2. Delete from Min-Heap\n");
        printf("3. Display Min-Heap\n");
        printf("4. Insert into Max-Heap\n");
        printf("5. Delete from Max-Heap\n");
        printf("6. Display Max-Heap\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    choice = 7;
                    break;
                }
                insertMin(value);
                displayMin();
                break;

            case 2:
                deleteMin();
                displayMin();
                break;

            case 3:
                displayMin();
                break;

            case 4:
                printf("Enter value: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    choice = 7;
                    break;
                }
                insertMax(value);
                displayMax();
                break;

            case 5:
                deleteMax();
                displayMax();
                break;

            case 6:
                displayMax();
                break;

            case 7:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 7);

    endTime = clock();
    executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("\nExecution time: %.6f seconds\n", executionTime);

    return 0;
}

/*
SAMPLE OUTPUT:

===== MIN-HEAP AND MAX-HEAP MENU =====
1. Insert into Min-Heap
2. Delete from Min-Heap
3. Display Min-Heap
4. Insert into Max-Heap
5. Delete from Max-Heap
6. Display Max-Heap
7. Exit
Enter your choice: 1
Enter value: 4
Min-Heap: 4 

===== MIN-HEAP AND MAX-HEAP MENU =====
1. Insert into Min-Heap
2. Delete from Min-Heap
3. Display Min-Heap
4. Insert into Max-Heap
5. Delete from Max-Heap
6. Display Max-Heap
7. Exit
Enter your choice: 1
Enter value: 5
Min-Heap: 4 5 

===== MIN-HEAP AND MAX-HEAP MENU =====
1. Insert into Min-Heap
2. Delete from Min-Heap
3. Display Min-Heap
4. Insert into Max-Heap
5. Delete from Max-Heap
6. Display Max-Heap
7. Exit
Enter your choice: 2
Deleted from Min-Heap: 4
Min-Heap: 5 

===== MIN-HEAP AND MAX-HEAP MENU =====
1. Insert into Min-Heap
2. Delete from Min-Heap
3. Display Min-Heap
4. Insert into Max-Heap
5. Delete from Max-Heap
6. Display Max-Heap
7. Exit
Enter your choice: 1
Enter value: 4
Min-Heap: 4 5 

===== MIN-HEAP AND MAX-HEAP MENU =====
1. Insert into Min-Heap
2. Delete from Min-Heap
3. Display Min-Heap
4. Insert into Max-Heap
5. Delete from Max-Heap
6. Display Max-Heap
7. Exit
Enter your choice: 4
Enter value: 5
Max-Heap: 5 

===== MIN-HEAP AND MAX-HEAP MENU =====
1. Insert into Min-Heap
2. Delete from Min-Heap
3. Display Min-Heap
4. Insert into Max-Heap
5. Delete from Max-Heap
6. Display Max-Heap
7. Exit
Enter your choice: 4
Enter value: 8
Max-Heap: 8 5 

===== MIN-HEAP AND MAX-HEAP MENU =====
1. Insert into Min-Heap
2. Delete from Min-Heap
3. Display Min-Heap
4. Insert into Max-Heap
5. Delete from Max-Heap
6. Display Max-Heap
7. Exit
Enter your choice: 6
Max-Heap: 8 5 

===== MIN-HEAP AND MAX-HEAP MENU =====
1. Insert into Min-Heap
2. Delete from Min-Heap
3. Display Min-Heap
4. Insert into Max-Heap
5. Delete from Max-Heap
6. Display Max-Heap
7. Exit
Enter your choice: 6
Max-Heap: 8 5 

===== MIN-HEAP AND MAX-HEAP MENU =====
1. Insert into Min-Heap
2. Delete from Min-Heap
3. Display Min-Heap
4. Insert into Max-Heap
5. Delete from Max-Heap
6. Display Max-Heap
7. Exit
Enter your choice: 7
Exiting program...

Execution time: 38.659000 seconds 

KEY OBSERVATIONS:

1. Min-Heap keeps the smallest element at the root.
2. Max-Heap keeps the largest element at the root.
3. Insertion and deletion maintain the heap property.
4. Heap insertion and deletion take O(log n) time.
*/