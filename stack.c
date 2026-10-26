

#include <stdio.h>
#include <time.h>

#define MAX 100

int stack[MAX];
int top = -1;

void push(int value) {
    if (top == MAX - 1) {
        printf("Stack Overflow! Stack is full.\n");
        return;
    }

    top++;
    stack[top] = value;

    printf("%d pushed onto the stack.\n", value);
}

void pop() {
    int value;

    if (top == -1) {
        printf("Stack Underflow! Stack is empty.\n");
        return;
    }

    value = stack[top];
    top--;

    printf("Popped element: %d\n", value);
}

void display() {
    int i;

    if (top == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("\nStack (Top to Bottom):\n");

    for (i = top; i >= 0; i--) {
        printf("| %d |\n", stack[i]);
    }

    printf("-----\n");
}

void peek() {
    if (top == -1) {
        printf("Stack is empty. No top element.\n");
        return;
    }

    printf("Top element: %d\n", stack[top]);
}

int main() {
    int choice, value;
    clock_t startTime, endTime;
    double executionTime;

    startTime = clock();

    do {
        printf("\n===== STACK MENU =====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display Stack\n");
        printf("4. Peek (Top Element)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter an integer.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to push: ");

                if (scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    choice = 5;
                    break;
                }

                push(value);
                display();
                break;

            case 2:
                pop();
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

===== STACK MENU =====
1. Push
2. Pop
3. Display Stack
4. Peek (Top Element)
5. Exit
Enter your choice: 1
Enter value to push: 45
45 pushed onto the stack.

Stack (Top to Bottom):
| 45 |
-----

===== STACK MENU =====
1. Push
2. Pop
3. Display Stack
4. Peek (Top Element)
5. Exit
Enter your choice: 1
Enter value to push: 78
78 pushed onto the stack.

Stack (Top to Bottom):
| 78 |
| 45 |
-----

===== STACK MENU =====
1. Push
2. Pop
3. Display Stack
4. Peek (Top Element)
5. Exit
Enter your choice: 1
Enter value to push: 96
96 pushed onto the stack.

Stack (Top to Bottom):
| 96 |
| 78 |
| 45 |
-----

===== STACK MENU =====
1. Push
2. Pop
3. Display Stack
4. Peek (Top Element)
5. Exit
Enter your choice: 4
Top element: 96

===== STACK MENU =====
1. Push
2. Pop
3. Display Stack
4. Peek (Top Element)
5. Exit
Enter your choice: 2
Popped element: 96

Stack (Top to Bottom):
| 78 |
| 45 |
-----

===== STACK MENU =====
1. Push
2. Pop
3. Display Stack
4. Peek (Top Element)
5. Exit
Enter your choice: 1
Enter value to push: 85
85 pushed onto the stack.

Stack (Top to Bottom):
| 85 |
| 78 |
| 45 |
-----

===== STACK MENU =====
1. Push
2. Pop
3. Display Stack
4. Peek (Top Element)
5. Exit
Enter your choice: 3

Stack (Top to Bottom):
| 85 |
| 78 |
| 45 |
-----

===== STACK MENU =====
1. Push
2. Pop
3. Display Stack
4. Peek (Top Element)
5. Exit
Enter your choice: 5
Exiting program...

Execution time: 45.958000 seconds
*/
