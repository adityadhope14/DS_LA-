

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->data)
        root->left = insert(root->left, value);
    else if (value > root->data)
        root->right = insert(root->right, value);
    else
        printf("Duplicate values are not allowed.\n");

    return root;
}

struct Node* findMin(struct Node* root) {
    while (root != NULL && root->left != NULL)
        root = root->left;
    return root;
}

struct Node* deleteNode(struct Node* root, int value) {
    struct Node* temp;

    if (root == NULL) {
        printf("Element not found.\n");
        return NULL;
    }

    if (value < root->data)
        root->left = deleteNode(root->left, value);
    else if (value > root->data)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left == NULL) {
            temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            temp = root->left;
            free(root);
            return temp;
        }

        temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

void display(struct Node* root, int space) {
    int i;

    if (root == NULL)
        return;

    space += 5;
    display(root->right, space);

    printf("\n");
    for (i = 5; i < space; i++)
        printf(" ");

    printf("%d\n", root->data);

    display(root->left, space);
}

void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    int choice, value;
    clock_t startTime, endTime;
    double executionTime;

    startTime = clock();

    do {
        printf("\n===== BINARY SEARCH TREE MENU =====\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display Tree\n");
        printf("4. Inorder Traversal\n");
        printf("5. Preorder Traversal\n");
        printf("6. Postorder Traversal\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    choice = 7;
                    break;
                }
                root = insert(root, value);
                display(root, 0);
                break;

            case 2:
                printf("Enter value to delete: ");
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input.\n");
                    choice = 7;
                    break;
                }
                if (root != NULL) {
                    root = deleteNode(root, value);
                    display(root, 0);
                } else {
                    printf("Tree is empty.\n");
                }
                break;

            case 3:
                if (root == NULL)
                    printf("Tree is empty.\n");
                else
                    display(root, 0);
                break;

            case 4:
                printf("Inorder Traversal: ");
                inorder(root);
                printf("\n");
                break;

            case 5:
                printf("Preorder Traversal: ");
                preorder(root);
                printf("\n");
                break;

            case 6:
                printf("Postorder Traversal: ");
                postorder(root);
                printf("\n");
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

    freeTree(root);
    return 0;
}

/*
SAMPLE OUTPUT:

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 1
Enter value to insert: 4 

4

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 1
Enter value to insert: 5

     5

4

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 1
Enter value to insert: 9

          9

     5

4

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 1
Enter value to insert: 1

          9

     5

4

     1

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 1
Enter value to insert: 2

          9

     5

4

          2

     1

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 2
Enter value to delete: 4

     9

5

          2

     1

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 3

     9

5

          2

     1

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 4
Inorder Traversal: 1 2 5 9 

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 5
Preorder Traversal: 5 1 2 9 

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 
6
Postorder Traversal: 2 1 9 5 

===== BINARY SEARCH TREE MENU =====
1. Insert
2. Delete
3. Display Tree
4. Inorder Traversal
5. Preorder Traversal
6. Postorder Traversal
7. Exit
Enter your choice: 7
Exiting program...

Execution time: 52.023000 seconds

KEY OBSERVATIONS:

1. BST stores smaller values on the left and larger values on the right.
2. Insertion and deletion modify the tree.
3. Inorder traversal displays values in sorted order.
4. Preorder and postorder follow different visiting orders.
*/