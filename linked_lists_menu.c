


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
};

struct Node *head[4] = {NULL};

int lengthList(int type) {
    struct Node *temp = head[type];
    int count = 0;

    if (temp == NULL)
        return 0;

    if (type == 3) {
        do {
            count++;
            temp = temp->next;
        } while (temp != head[type]);
    } else {
        while (temp != NULL) {
            count++;
            temp = temp->next;
        }
    }

    return count;
}

void display(int type) {
    struct Node *temp = head[type];

    if (temp == NULL) {
        printf("Linked list is empty.\n");
        return;
    }

    printf("Linked List: ");

    if (type == 3) {
        do {
            printf("%d -> ", temp->data);
            temp = temp->next;
        } while (temp != head[type]);
        printf("(back to head)\n");
    } else {
        while (temp != NULL) {
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void insertBeginning(int type, int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *last;

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = value;

    if (head[type] == NULL) {
        newNode->next = (type == 3) ? newNode : NULL;
        newNode->prev = NULL;
        head[type] = newNode;
    } else if (type == 3) {
        last = head[type];
        while (last->next != head[type])
            last = last->next;

        newNode->next = head[type];
        newNode->prev = NULL;
        last->next = newNode;
        head[type] = newNode;
    } else {
        newNode->next = head[type];
        newNode->prev = NULL;

        if (type == 2)
            head[type]->prev = newNode;

        head[type] = newNode;
    }

    printf("Node inserted at the beginning.\n");
    display(type);
}

void insertEnd(int type, int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    struct Node *temp;

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    newNode->data = value;
    newNode->prev = NULL;

    if (head[type] == NULL) {
        newNode->next = (type == 3) ? newNode : NULL;
        head[type] = newNode;
    } else {
        temp = head[type];

        if (type == 3) {
            while (temp->next != head[type])
                temp = temp->next;
            temp->next = newNode;
            newNode->next = head[type];
        } else {
            while (temp->next != NULL)
                temp = temp->next;
            temp->next = newNode;
            newNode->next = NULL;

            if (type == 2)
                newNode->prev = temp;
        }
    }

    printf("Node inserted at the end.\n");
    display(type);
}

void insertPosition(int type, int value, int position) {
    struct Node *newNode, *temp;
    int length = lengthList(type);
    int i;

    if (position < 1 || position > length + 1) {
        printf("Invalid position.\n");
        return;
    }

    if (position == 1) {
        insertBeginning(type, value);
        return;
    }

    newNode = (struct Node *)malloc(sizeof(struct Node));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    temp = head[type];

    for (i = 1; i < position - 1; i++)
        temp = temp->next;

    newNode->data = value;
    newNode->next = temp->next;
    newNode->prev = NULL;
    temp->next = newNode;

    if (type == 2) {
        newNode->prev = temp;
        if (newNode->next != NULL)
            newNode->next->prev = newNode;
    }

    printf("Node inserted at position %d.\n", position);
    display(type);
}

void deleteBeginning(int type) {
    struct Node *temp = head[type];
    struct Node *last;

    if (head[type] == NULL) {
        printf("Linked list is empty. Deletion not possible.\n");
        return;
    }

    if (type == 3 && head[type]->next != head[type]) {
        last = head[type];
        while (last->next != head[type])
            last = last->next;

        head[type] = head[type]->next;
        last->next = head[type];
    } else {
        head[type] = (type == 3) ? NULL : head[type]->next;
    }

    if (type == 2 && head[type] != NULL)
        head[type]->prev = NULL;

    free(temp);
    printf("First node deleted.\n");
    display(type);
}

void deleteEnd(int type) {
    struct Node *temp, *prev = NULL;

    if (head[type] == NULL) {
        printf("Linked list is empty. Deletion not possible.\n");
        return;
    }

    if (lengthList(type) == 1) {
        free(head[type]);
        head[type] = NULL;
    } else if (type == 3) {
        temp = head[type];
        while (temp->next != head[type]) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = head[type];
        free(temp);
    } else {
        temp = head[type];
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = NULL;
        free(temp);
    }

    printf("Last node deleted.\n");
    display(type);
}

void deletePosition(int type, int position) {
    struct Node *temp, *toDelete;
    int length = lengthList(type);
    int i;

    if (position < 1 || position > length) {
        printf("Invalid position or empty list.\n");
        return;
    }

    if (position == 1) {
        deleteBeginning(type);
        return;
    }

    temp = head[type];

    for (i = 1; i < position - 1; i++)
        temp = temp->next;

    toDelete = temp->next;
    temp->next = toDelete->next;

    if (type == 2 && toDelete->next != NULL)
        toDelete->next->prev = temp;

    free(toDelete);
    printf("Node at position %d deleted.\n", position);
    display(type);
}

void search(int type, int value) {
    struct Node *temp = head[type];
    int position = 1;
    int length = lengthList(type);

    while (position <= length) {
        if (temp->data == value) {
            printf("Element %d found at position %d.\n", value, position);
            return;
        }
        temp = temp->next;
        position++;
    }

    printf("Element %d not found.\n", value);
}

void freeList(int type) {
    struct Node *temp;
    int length = lengthList(type);
    int i;

    temp = head[type];

    for (i = 0; i < length; i++) {
        struct Node *nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }

    head[type] = NULL;
}

int main() {
    int choice, type, operation, value, position;
    clock_t startTime, endTime;
    double executionTime;

    startTime = clock();

    do {
        printf("\n===== LINKED LIST MENU =====\n");
        printf("1. Singly Linked List\n");
        printf("2. Doubly Linked List\n");
        printf("3. Circular Linked List\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
            break;

        if (choice >= 1 && choice <= 3) {
            type = choice;

            do {
                if (type == 1)
                    printf("\n===== SINGLY LINKED LIST =====\n");
                else if (type == 2)
                    printf("\n===== DOUBLY LINKED LIST =====\n");
                else
                    printf("\n===== CIRCULAR LINKED LIST =====\n");

                printf("1. Insert at Beginning\n");
                printf("2. Insert at End\n");
                printf("3. Insert at Position\n");
                printf("4. Delete from Beginning\n");
                printf("5. Delete from End\n");
                printf("6. Delete from Position\n");
                printf("7. Display / Traverse\n");
                printf("8. Search an Element\n");
                printf("9. Back to Main Menu\n");
                printf("Enter your choice: ");

                if (scanf("%d", &operation) != 1) {
                    operation = 9;
                    choice = 4;
                    break;
                }

                switch (operation) {
                    case 1:
                        printf("Enter value: ");
                        if (scanf("%d", &value) == 1)
                            insertBeginning(type, value);
                        else {
                            operation = 9;
                            choice = 4;
                        }
                        break;

                    case 2:
                        printf("Enter value: ");
                        if (scanf("%d", &value) == 1)
                            insertEnd(type, value);
                        else {
                            operation = 9;
                            choice = 4;
                        }
                        break;

                    case 3:
                        printf("Enter value: ");
                        if (scanf("%d", &value) != 1) {
                            operation = 9;
                            choice = 4;
                            break;
                        }
                        printf("Enter position (starting from 1): ");
                        if (scanf("%d", &position) == 1)
                            insertPosition(type, value, position);
                        else {
                            operation = 9;
                            choice = 4;
                        }
                        break;

                    case 4:
                        deleteBeginning(type);
                        break;

                    case 5:
                        deleteEnd(type);
                        break;

                    case 6:
                        printf("Enter position to delete: ");
                        if (scanf("%d", &position) == 1)
                            deletePosition(type, position);
                        else {
                            operation = 9;
                            choice = 4;
                        }
                        break;

                    case 7:
                        display(type);
                        break;

                    case 8:
                        printf("Enter value to search: ");
                        if (scanf("%d", &value) == 1)
                            search(type, value);
                        else {
                            operation = 9;
                            choice = 4;
                        }
                        break;

                    case 9:
                        break;

                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (operation != 9 && choice != 4);
        } else if (choice == 4) {
            printf("Exiting program...\n");
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    freeList(1);
    freeList(2);
    freeList(3);

    endTime = clock();
    executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;

    printf("\nExecution time: %.6f seconds\n", executionTime);

    return 0;
}

/*
SAMPLE OUTPUT:

===== LINKED LIST MENU =====
1. Singly Linked List
2. Doubly Linked List
3. Circular Linked List
4. Exit
Enter your choice: 1

===== SINGLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 1
Enter value: 45
Node inserted at the beginning.
Linked List: 45 -> NULL

===== SINGLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 2
Enter value: 12
Node inserted at the end.
Linked List: 45 -> 12 -> NULL

===== SINGLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 3
Enter value: 56
Enter position (starting from 1): 1
Node inserted at the beginning.
Linked List: 56 -> 45 -> 12 -> NULL

===== SINGLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 7
Linked List: 56 -> 45 -> 12 -> NULL

===== SINGLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 9

===== LINKED LIST MENU =====
1. Singly Linked List
2. Doubly Linked List
3. Circular Linked List
4. Exit
Enter your choice: 2

===== DOUBLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 1
Enter value: 32
Node inserted at the beginning.
Linked List: 32 -> NULL

===== DOUBLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 2
Enter value: 89
Node inserted at the end.
Linked List: 32 -> 89 -> NULL

===== DOUBLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 7
Linked List: 32 -> 89 -> NULL

===== DOUBLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 8
Enter value to search: 89
Element 89 found at position 2.

===== DOUBLY LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 9

===== LINKED LIST MENU =====
1. Singly Linked List
2. Doubly Linked List
3. Circular Linked List
4. Exit
Enter your choice: 3

===== CIRCULAR LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 2
Enter value: 45
Node inserted at the end.
Linked List: 45 -> (back to head)

===== CIRCULAR LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 1
Enter value: 85
Node inserted at the beginning.
Linked List: 85 -> 45 -> (back to head)

===== CIRCULAR LINKED LIST =====
1. Insert at Beginning
2. Insert at End
3. Insert at Position
4. Delete from Beginning
5. Delete from End
6. Delete from Position
7. Display / Traverse
8. Search an Element
9. Back to Main Menu
Enter your choice: 9

===== LINKED LIST MENU =====
1. Singly Linked List
2. Doubly Linked List
3. Circular Linked List
4. Exit
Enter your choice: 4
Exiting program...

Execution time: 80.708000 seconds

KEY OBSERVATIONS:
1. Doubly linked lists maintain previous links.
2. Circular linked lists connect the last node to the head.
*/