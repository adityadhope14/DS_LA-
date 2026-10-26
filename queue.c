

#include <stdio.h>
#include <time.h>

#define MAX 100

int queue[MAX];
int front = -1;
int rear = -1;

void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue Overflow! Queue is full.\n");
        return;
    }

    if (front == -1) {
        front = 0;
    }

    rear++;
    queue[rear] = value;

    printf("%d inserted into the queue.\n", value);
}

void dequeue() {
    int value;

    if (front == -1 || front > rear) {
        printf("Queue Underflow! Queue is empty.\n");
        return;
    }

    value = queue[front];
    printf("Deleted element: %d\n", value);

    front++;

    if (front > rear) {
        front = -1;
        rear = -1;
    }
}

void display() {
    int i;

    if (front == -1) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue (Front to Rear): ");

    for (i = front; i <= rear; i++) {
        printf("%d ", queue[i]);
    }

    printf("\n");
}

void peek() {
    if (front == -1) {
        printf("Queue is empty. No front element.\n");
        return;
    }

    printf("Front element: %d\n", queue[front]);
}

int main() {
    int choice, value;
    clock_t startTime, endTime;
    double executionTime;

    startTime = clock();

    do {
        printf("\n===== QUEUE MENU =====\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Peek (Front Element)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");

                if (scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    choice = 5;
                    break;
                }

                enqueue(value);
                display();
                break;

            case 2:
                dequeue();
                display();
                break;

            case 3:
                display();
                break;

            case 4:
                peek();
                break;

            case 5:
                printf("Exiting program...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 5);

    endTime = clock();

    executionTime =
        (double)(endTime - startTime) / CLOCKS_PER_SEC;

    printf("\nExecution time: %.6f seconds\n", executionTime);

    return 0;
}

/*
SAMPLE OUTPUT:

===== QUEUE MENU =====
1. Enqueue
2. Dequeue
3. Display Queue
4. Peek (Front Element)
5. Exit
Enter your choice: 1
Enter value to enqueue: 45
45 inserted into the queue.
Queue (Front to Rear): 45 

===== QUEUE MENU =====
1. Enqueue
2. Dequeue
3. Display Queue
4. Peek (Front Element)
5. Exit
Enter your choice: 1
Enter value to enqueue: 56
56 inserted into the queue.
Queue (Front to Rear): 45 56 

===== QUEUE MENU =====
1. Enqueue
2. Dequeue
3. Display Queue
4. Peek (Front Element)
5. Exit
Enter your choice: 1
Enter value to enqueue: 78
78 inserted into the queue.
Queue (Front to Rear): 45 56 78 

===== QUEUE MENU =====
1. Enqueue
2. Dequeue
3. Display Queue
4. Peek (Front Element)
5. Exit
Enter your choice: 4
Front element: 45

===== QUEUE MENU =====
1. Enqueue
2. Dequeue
3. Display Queue
4. Peek (Front Element)
5. Exit
Enter your choice: 2
Deleted element: 45
Queue (Front to Rear): 56 78 

===== QUEUE MENU =====
1. Enqueue
2. Dequeue
3. Display Queue
4. Peek (Front Element)
5. Exit
Enter your choice: 3
Queue (Front to Rear): 56 78 

===== QUEUE MENU =====
1. Enqueue
2. Dequeue
3. Display Queue
4. Peek (Front Element)
5. Exit
Enter your choice: 4
Front element: 56

===== QUEUE MENU =====
1. Enqueue
2. Dequeue
3. Display Queue
4. Peek (Front Element)
5. Exit
Enter your choice: 5
Exiting program...

Execution time: 767.520000 seconds

KEY OBSERVATIONS:

1. Queue follows FIFO.
2. Enqueue inserts and Dequeue removes elements.
3. Overflow and Underflow are handled.
4. Peek displays the front element.
*/
