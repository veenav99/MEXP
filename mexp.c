#include <stdio.h>
#include <stdlib.h>

// Function to multiply two square matrices
void multiplyMatrix(int** a, int** b, int** result, int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            result[i][j] = 0;
            for (int x = 0; x < k; x++) {
                result[i][j] += a[i][x] * b[x][j];
            }
        }
    }
}

// Function to print a square matrix
void printMatrix(int** matrix, int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            printf("%d", matrix[i][j]);
            if (j < k - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    // Open the input file
    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    int k;
    if (fscanf(file, "%d", &k) != 1 || k <= 0) {
        fprintf(stderr, "Invalid matrix size\n");
        fclose(file);
        return 1;
    }

    // Allocate memory for the matrix M
    int** M = (int**)malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        M[i] = (int*)malloc(k * sizeof(int));
        for (int j = 0; j < k; j++) {
            if (fscanf(file, "%d", &M[i][j]) != 1) {
                fprintf(stderr, "Invalid matrix content\n");
                fclose(file);
                return 1;
            }
        }
    }

    int n;
    if (fscanf(file, "%d", &n) != 1 || n < 0) {
        fprintf(stderr, "Invalid exponent value\n");
        fclose(file);
        return 1;
    }

    fclose(file);

    // Allocate memory for the result matrix
    int** result = (int**)malloc(k * sizeof(int*));
    for (int i = 0; i < k; i++) {
        result[i] = (int*)malloc(k * sizeof(int));
    }

    if (n == 0) {
        // If n is 0, the result is the identity matrix
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                if (i == j) {
                    result[i][j] = 1;
                } else {
                    result[i][j] = 0;
                }
            }
        }
    } else {
        // Initialize the result matrix to M
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                result[i][j] = M[i][j];
            }
        }

        // Multiply M by itself (n-1) times
        for (int i = 1; i < n; i++) {
            int** temp = (int**)malloc(k * sizeof(int*));
            for (int j = 0; j < k; j++) {
                temp[j] = (int*)malloc(k * sizeof(int));
            }

            multiplyMatrix(result, M, temp, k);

            // Copy the result back to the result matrix
            for (int j = 0; j < k; j++) {
                for (int l = 0; l < k; l++) {
                    result[j][l] = temp[j][l];
                }
            }

            // Free memory used by the temporary matrix
            for (int j = 0; j < k; j++) {
                free(temp[j]);
            }
            free(temp);
        }
    }

    // Print the result matrix
    printMatrix(result, k);

    // Free memory used by the matrices
    for (int i = 0; i < k; i++) {
        free(M[i]);
        free(result[i]);
    }
    free(M);
    free(result);

    return 0;
}