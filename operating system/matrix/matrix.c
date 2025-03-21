#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int row;
    int col;
} ThreadData;

int **A, **B, **C; 
int ROWS_A, COLS_A, ROWS_B, COLS_B; 

void* multiply(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    int sum = 0;
    for (int k = 0; k < COLS_A; k++) {
        sum += A[data->row][k] * B[k][data->col];
    }

    int* result = (int*) malloc(sizeof(int));
    if (!result) {
        perror("Memory allocation failed for result");
        exit(EXIT_FAILURE);
    }

    *result = sum;
    free(data);  // Free dynamically allocated thread data
    pthread_exit(result);
}

int main() {
    printf("Enter dimensions of Matrix A (rows cols): ");
    scanf("%d %d", &ROWS_A, &COLS_A);

    printf("Enter dimensions of Matrix B (rows cols): ");
    scanf("%d %d", &ROWS_B, &COLS_B);

    if (COLS_A != ROWS_B) {
        printf("Matrix multiplication not possible! Columns of A must match rows of B.\n");
        return 1;
    }

    // Memory allocation
    A = (int**) malloc(ROWS_A * sizeof(int*));
    B = (int**) malloc(ROWS_B * sizeof(int*));
    C = (int**) malloc(ROWS_A * sizeof(int*));

    if (!A || !B || !C) {
        perror("Memory allocation failed");
        return 1;
    }

    for (int i = 0; i < ROWS_A; i++) A[i] = (int*) malloc(COLS_A * sizeof(int));
    for (int i = 0; i < ROWS_B; i++) B[i] = (int*) malloc(COLS_B * sizeof(int));
    for (int i = 0; i < ROWS_A; i++) C[i] = (int*) malloc(COLS_B * sizeof(int));

    // Input matrices
    printf("Enter elements of Matrix A (%dx%d):\n", ROWS_A, COLS_A);
    for (int i = 0; i < ROWS_A; i++)
        for (int j = 0; j < COLS_A; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of Matrix B (%dx%d):\n", ROWS_B, COLS_B);
    for (int i = 0; i < ROWS_B; i++)
        for (int j = 0; j < COLS_B; j++)
            scanf("%d", &B[i][j]);

    pthread_t threads[ROWS_A][COLS_B];

    // Create threads
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            ThreadData* data = (ThreadData*) malloc(sizeof(ThreadData));
            if (!data) {
                perror("Memory allocation failed for thread data");
                exit(EXIT_FAILURE);
            }
            data->row = i;
            data->col = j;
            if (pthread_create(&threads[i][j], NULL, multiply, data) != 0) {
                perror("Thread creation failed");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Join threads and collect results
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            void* result;
            pthread_join(threads[i][j], &result);
            C[i][j] = *(int*)result;
            free(result);
        }
    }

    // Display result matrix
    printf("\nResult Matrix C (%dx%d):\n", ROWS_A, COLS_B);
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    for (int i = 0; i < ROWS_A; i++) free(A[i]);
    for (int i = 0; i < ROWS_B; i++) free(B[i]);
    for (int i = 0; i < ROWS_A; i++) free(C[i]);
    free(A);
    free(B);
    free(C);

    return 0;
}
