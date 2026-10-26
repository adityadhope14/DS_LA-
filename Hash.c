

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SIZE 10
#define NAME_SIZE 50
#define PHONE_SIZE 15

struct Node {
    char name[NAME_SIZE];
    char phone[PHONE_SIZE];
    struct Node *next;
};

int hashFunction(char phone[]) {
    int i;
    int sum = 0;

    for(i = 0; phone[i] != '\0'; i++) {
        if(phone[i] >= '0' && phone[i] <= '9') {
            sum = sum + (phone[i] - '0');
        }
    }

    return sum % MAX_SIZE;
}

int countCollisions(struct Node *hashTable[], int index) {
    int count = 0;
    struct Node *temp;

    temp = hashTable[index];

    if(temp == NULL) {
        return 0;
    }

    while(temp->next != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

void insert(struct Node *hashTable[], char name[], char phone[]) {
    int index;
    int collisions;
    struct Node *newNode;
    struct Node *temp;

    index = hashFunction(phone);
    collisions = countCollisions(hashTable, index);

    newNode = (struct Node *)malloc(sizeof(struct Node));

    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = NULL;

    if(hashTable[index] == NULL) {
        hashTable[index] = newNode;

        printf("\nHash index = %d", index);
        printf("\nNo collision occurred.");
        printf("\nContact inserted successfully.\n");
    }
    else {
        temp = hashTable[index];

        while(temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = newNode;

        printf("\nHash index = %d", index);
        printf("\nCollision occurred at index %d.", index);
        printf("\nCollision number = %d", collisions + 1);
        printf("\nContact added to the chain successfully.\n");
    }
}

void deleteContact(struct Node *hashTable[], char name[], char phone[]) {
    int index;
    struct Node *temp;
    struct Node *previous;

    index = hashFunction(phone);

    temp = hashTable[index];
    previous = NULL;

    while(temp != NULL) {
        if(strcmp(temp->name, name) == 0 &&
           strcmp(temp->phone, phone) == 0) {

            if(previous == NULL) {
                hashTable[index] = temp->next;
            }
            else {
                previous->next = temp->next;
            }

            free(temp);

            printf("\nHash index = %d", index);
            printf("\nContact deleted successfully.\n");
            return;
        }

        previous = temp;
        temp = temp->next;
    }

    printf("\nContact not found in the hash table.\n");
}

void showCollisions(struct Node *hashTable[]) {
    int i;
    int collisions;
    int totalCollisions = 0;
    struct Node *temp;

    printf("\n========== COLLISION INFORMATION ==========\n");

    for(i = 0; i < MAX_SIZE; i++) {
        collisions = countCollisions(hashTable, i);

        if(collisions > 0) {
            printf("\nIndex %d : %d collision(s)", i, collisions);
            printf("\nChain: ");

            temp = hashTable[i];

            while(temp != NULL) {
                printf("%s (%s)", temp->name, temp->phone);

                if(temp->next != NULL) {
                    printf(" -> ");
                }

                temp = temp->next;
            }

            printf("\n");

            totalCollisions = totalCollisions + collisions;
        }
    }

    if(totalCollisions == 0) {
        printf("\nNo collisions have occurred.\n");
    }

    printf("\nTotal collisions = %d", totalCollisions);
    printf("\n===========================================\n");
}

void displayHashTable(struct Node *hashTable[]) {
    int i;
    int collisions;
    struct Node *temp;

    printf("\n====================================================================\n");
    printf("| %-5s | %-11s | %-25s | %-15s |\n",
           "Index", "Collisions", "Name", "Phone Number");
    printf("====================================================================\n");

    for(i = 0; i < MAX_SIZE; i++) {
        collisions = countCollisions(hashTable, i);
        temp = hashTable[i];

        if(temp == NULL) {
            printf("| %-5d | %-11d | %-25s | %-15s |\n",
                   i, 0, "NULL", "NULL");
        }
        else {
            while(temp != NULL) {
                printf("| %-5d | %-11d | %-25s | %-15s |\n",
                       i, collisions, temp->name, temp->phone);

                temp = temp->next;
            }
        }
    }

    printf("====================================================================\n");
}

void freeHashTable(struct Node *hashTable[]) {
    int i;
    struct Node *temp;
    struct Node *nextNode;

    for(i = 0; i < MAX_SIZE; i++) {
        temp = hashTable[i];

        while(temp != NULL) {
            nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }

        hashTable[i] = NULL;
    }
}

int main() {
    struct Node *hashTable[MAX_SIZE];

    int i;
    int choice;

    char name[NAME_SIZE];
    char phone[PHONE_SIZE];

    clock_t startTime;
    clock_t endTime;
    double executionTime;

    for(i = 0; i < MAX_SIZE; i++) {
        hashTable[i] = NULL;
    }

    do {
        printf("\n\n========== HASH TABLE MENU ==========\n");
        printf("1. Insert Contact\n");
        printf("2. Delete Contact\n");
        printf("3. Show Collisions\n");
        printf("4. Display Hash Table\n");
        printf("5. Exit\n");
        printf("=====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {

            case 1:
                printf("\nEnter name: ");
                scanf(" %[^\n]", name);

                printf("Enter phone number: ");
                scanf("%14s", phone);

                startTime = clock();

                insert(hashTable, name, phone);

                endTime = clock();

                executionTime =
                    ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

                printf("Execution time: %f seconds\n",
                       executionTime);

                break;

            case 2:
                printf("\nEnter name: ");
                scanf(" %[^\n]", name);

                printf("Enter phone number: ");
                scanf("%14s", phone);

                startTime = clock();

                deleteContact(hashTable, name, phone);

                endTime = clock();

                executionTime =
                    ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

                printf("Execution time: %f seconds\n",
                       executionTime);

                break;

            case 3:
                showCollisions(hashTable);
                break;

            case 4:
                displayHashTable(hashTable);
                break;

            case 5:
                printf("\nExiting program...\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while(choice != 5);

    freeHashTable(hashTable);

    return 0;
}

/*
OUTPUT:

========== HASH TABLE MENU ==========
1. Insert Contact
2. Delete Contact
3. Show Collisions
4. Display Hash Table
5. Exit
=====================================
Enter your choice: 1

Enter name: divya
Enter phone number: 123456

Hash index = 1
No collision occurred.
Contact inserted successfully.
Execution time: 0.000000 seconds


========== HASH TABLE MENU ==========
1. Insert Contact
2. Delete Contact
3. Show Collisions
4. Display Hash Table
5. Exit
=====================================
Enter your choice: 1

Enter name: mahi
Enter phone number: 456789

Hash index = 9
No collision occurred.
Contact inserted successfully.
Execution time: 0.001000 seconds


========== HASH TABLE MENU ==========
1. Insert Contact
2. Delete Contact
3. Show Collisions
4. Display Hash Table
5. Exit
=====================================
Enter your choice: 1

Enter name: shruti
Enter phone number: 123789

Hash index = 0
No collision occurred.
Contact inserted successfully.
Execution time: 0.000000 seconds


========== HASH TABLE MENU ==========
1. Insert Contact
2. Delete Contact
3. Show Collisions
4. Display Hash Table
5. Exit
=====================================
Enter your choice: 1

Enter name: priya
Enter phone number: 456123

Hash index = 1
Collision occurred at index 1.
Collision number = 1
Contact added to the chain successfully.
Execution time: 0.001000 seconds


========== HASH TABLE MENU ==========
1. Insert Contact
2. Delete Contact
3. Show Collisions
4. Display Hash Table
5. Exit
=====================================
Enter your choice: 2

Enter name: shruti
Enter phone number: 123789

Hash index = 0
Contact deleted successfully.
Execution time: 0.000000 seconds


========== HASH TABLE MENU ==========
1. Insert Contact
2. Delete Contact
3. Show Collisions
4. Display Hash Table
5. Exit
=====================================
Enter your choice: 3

========== COLLISION INFORMATION ==========

Index 1 : 1 collision(s)
Chain: divya (123456) -> priya (456123)

Total collisions = 1
===========================================


========== HASH TABLE MENU ==========
1. Insert Contact
2. Delete Contact
3. Show Collisions
4. Display Hash Table
5. Exit
=====================================
Enter your choice: 4

====================================================================
| Index | Collisions  | Name                      | Phone Number    |
====================================================================
| 0     | 0           | NULL                      | NULL            |
| 1     | 1           | divya                     | 123456          |
| 1     | 1           | priya                     | 456123          |
| 2     | 0           | NULL                      | NULL            |
| 3     | 0           | NULL                      | NULL            |
| 4     | 0           | NULL                      | NULL            |
| 5     | 0           | NULL                      | NULL            |
| 6     | 0           | NULL                      | NULL            |
| 7     | 0           | NULL                      | NULL            |
| 8     | 0           | NULL                      | NULL            |
| 9     | 0           | mahi                      | 456789          |
====================================================================


========== HASH TABLE MENU ==========
1. Insert Contact
2. Delete Contact
3. Show Collisions
4. Display Hash Table
5. Exit
=====================================
Enter your choice: 5

Exiting program...
*/