

#include <stdio.h>
#include <time.h>

int graph[20][20], visited[20], n;

void DFS(int vertex) {
    int i;

    visited[vertex] = 1;
    printf("%d ", vertex);

    for (i = 0; i < n; i++) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            DFS(i);
        }
    }
}

int main() {
    int i, j, start;
    clock_t startTime, endTime;
    double executionTime;

    startTime = clock();

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    if (n < 1 || n > 20) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter adjacency matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    printf("Enter starting vertex (0 to %d): ", n - 1);
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid starting vertex.\n");
        return 1;
    }

    printf("DFS Sequence: ");
    DFS(start);

    printf("\n");

    endTime = clock();
    executionTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", executionTime);

    return 0;
}

/*
SAMPLE OUTPUT:

Enter number of vertices: 4
Enter adjacency matrix:
1 1 0 1
1 0 0 1
1 1 0 0
1 0 0 0 
Enter starting vertex (0 to 3): 0
DFS Sequence: 0 1 3 
Execution time: 29.807000 seconds

KEY OBSERVATIONS:

1. DFS explores one path before backtracking.
2. A visited array prevents revisiting vertices.
3. DFS uses recursion to traverse the graph.
*/