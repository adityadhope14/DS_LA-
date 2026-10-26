#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define MAX_SIZE 10005

int original_arr[MAX_SIZE];
int arr[MAX_SIZE];
int temp[MAX_SIZE];

void printSubArray(int left, int right) {
    printf("[");
    for (int i = left; i <= right; i++) {
        printf("%d%s", arr[i], (i < right) ? ", " : "");
    }
    printf("]");
}

void mergeVisual(int left, int mid, int right, int depth) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    #pragma omp critical
    {
        for (int d = 0; d < depth; d++) printf("  ");
        printf("\033[1;32m[MERGE ]\033[0m Thread %d | Indices [%d..%d] & [%d..%d] -> ",
               omp_get_thread_num(), left, mid, mid + 1, right);
        printSubArray(left, right);
        printf("\n");
    }
}

void mergeSortVisual(int left, int right, int depth) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        #pragma omp critical
        {
            for (int d = 0; d < depth; d++) printf("  ");
            printf("\033[1;36m[DIVIDE]\033[0m Thread %d | Splitting [%d..%d] at mid=%d -> Left[%d..%d], Right[%d..%d]\n",
                   omp_get_thread_num(), left, right, mid, left, mid, mid + 1, right);
        }

        #pragma omp parallel sections
        {
            #pragma omp section
            mergeSortVisual(left, mid, depth + 1);

            #pragma omp section
            mergeSortVisual(mid + 1, right, depth + 1);
        }

        mergeVisual(left, mid, right, depth);
    }
}

void merge(int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }
    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}

void mergeSortSequential(int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortSequential(left, mid);
        mergeSortSequential(mid + 1, right);
        merge(left, mid, right);
    }
}

void mergeSortParallel(int left, int right, int depth) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        if (depth < 4) {
            #pragma omp parallel sections
            {
                #pragma omp section
                mergeSortParallel(left, mid, depth + 1);
                #pragma omp section
                mergeSortParallel(mid + 1, right, depth + 1);
            }
        } else {
            mergeSortSequential(left, mid);
            mergeSortSequential(mid + 1, right);
        }
        merge(left, mid, right);
    }
}

void resetArray(int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = original_arr[i];
    }
}

int main() {
    omp_set_nested(1);
    omp_set_num_threads(4);

    printf("\n\033[1;35m================================================================================\033[0m\n");
    printf("\033[1;37m           ASSIGNMENT 09: PARALLELIZATION OF MERGE SORT USING OPENMP            \033[0m\n");
    printf("\033[1;35m================================================================================\033[0m\n\n");

    int demo_n = 10;
    int sample_input[10] = {45, 32, 89, 12, 56, 78, 34, 90, 11, 67};

    FILE *file = fopen("input.txt", "r");
    if (file != NULL) {
        if (fscanf(file, "%d", &demo_n) == 1 && demo_n > 0 && demo_n <= 20) {
            for (int i = 0; i < demo_n; i++) {
                fscanf(file, "%d", &original_arr[i]);
            }
        } else {
            demo_n = 10;
            for (int i = 0; i < demo_n; i++) original_arr[i] = sample_input[i];
        }
        fclose(file);
    } else {
        for (int i = 0; i < demo_n; i++) original_arr[i] = sample_input[i];
    }

    resetArray(demo_n);

    printf("\033[1;33m>>> PHASE 1: STEP-BY-STEP PARALLEL EXECUTION TRACE (N = %d)\033[0m\n", demo_n);
    printf("--------------------------------------------------------------------------------\n");
    printf("\033[1;37mInitial Unsorted Array : \033[0m");
    printSubArray(0, demo_n - 1);
    printf("\n\n");

    mergeSortVisual(0, demo_n - 1, 0);

    printf("\n\033[1;37mFinal Sorted Array     : \033[1;32m");
    printSubArray(0, demo_n - 1);
    printf("\033[0m\n");
    printf("--------------------------------------------------------------------------------\n\n");

    printf("\033[1;33m>>> PHASE 2: SEQUENTIAL VS. PARALLEL PERFORMANCE BENCHMARK (5 RUNS AVG)\033[0m\n");
    printf("+--------------+--------------------------+--------------------------+---------------------+\n");
    printf("| Input Size   | Sequential Avg Time (s)  | Parallel Avg Time (s)    | Speedup Status      |\n");
    printf("+--------------+--------------------------+--------------------------+---------------------+\n");

    int sizes[4] = {10, 100, 1000, 10000};
    srand(42);

    for (int s = 0; s < 4; s++) {
        int n = sizes[s];
        for (int i = 0; i < n; i++) {
            original_arr[i] = rand() % 10000;
        }

        double seq_total = 0.0;
        for (int run = 0; run < 5; run++) {
            resetArray(n);
            clock_t start = clock();
            mergeSortSequential(0, n - 1);
            clock_t end = clock();
            seq_total += (double)(end - start) / CLOCKS_PER_SEC;
        }
        double seq_avg = seq_total / 5.0;

        double par_total = 0.0;
        for (int run = 0; run < 5; run++) {
            resetArray(n);
            double start = omp_get_wtime();
            mergeSortParallel(0, n - 1, 0);
            double end = omp_get_wtime();
            par_total += (end - start);
        }
        double par_avg = par_total / 5.0;

        if (seq_avg == 0.0) seq_avg = 0.000001;
        if (par_avg == 0.0) par_avg = 0.000001;
        double speedup = seq_avg / par_avg;

        if (speedup >= 1.0) {
            printf("| %-12d | %-24.6f | %-24.6f | \033[1;32m%6.2fx (faster)\033[0m    |\n",
                   n, seq_avg, par_avg, speedup);
        } else {
            printf("| %-12d | %-24.6f | %-24.6f | \033[1;31m%6.2fx (slower)\033[0m    |\n",
                   n, seq_avg, par_avg, speedup);
        }
    }

    printf("+--------------+--------------------------+--------------------------+---------------------+\n\n");
    return 0;
}