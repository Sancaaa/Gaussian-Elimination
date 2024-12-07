#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100

void luDecomposition(int n, double A[MAX][MAX], double L[MAX][MAX], double U[MAX][MAX]);
void printMatrix(int n, double A[MAX][MAX]);
void forwardSubstitution(int n, double L[MAX][MAX], double b[MAX], double y[MAX]);
void backwardSubstitution(int n, double U[MAX][MAX], double y[MAX], double x[MAX]);

int main() {
    int n = 3; // INPUT jumlah variabel
    double A[MAX][MAX] = {
        {25, 5, 1},  // INPUT matriks
        {64, 8, 1},
        {144, 12, 1}
    };
    double b[MAX] = {106.8, 177.2, 279.2}; // INPUT matriks b
    double L[MAX][MAX] = {0}, U[MAX][MAX] = {0}; 
    double y[MAX] = {0}, x[MAX] = {0}; 

    printf("============================================================\n");
    printf("Matrix Awal (A):\n");
    printMatrix(n, A);
    printf("============================================================\n");

    printf("Matriks b:\n");
    for (int i = 0; i < n; i++) {
        printf("%12.6f ", b[i]);
    }
    printf("\n");

    luDecomposition(n, A, L, U);

    printf("\n============================================================\n");
    printf("Matriks Lower Triangular (L):\n");
    printMatrix(n, L);
    printf("\nMatriks Upper Triangular (U):\n");
    printMatrix(n, U);
    printf("============================================================\n");

    printf("\n============================================================\n");
    printf("Sistem Persamaan (L.y = b):\n");
    printf("Matriks L:\n");
    printMatrix(n, L);
    printf("Matriks b (transpose):\n");
    for (int i = 0; i < n; i++) {
        printf("%12.6f ", b[i]);
    }
    printf("\n");

    forwardSubstitution(n, L, b, y);
    
    printf("\n============================================================\n");
    printf("Solusi untuk y (L.y = b):\n");
    for (int i = 0; i < n; i++) {
        printf("y%d = %12.6f\n", i + 1, y[i]);
    }
    printf("============================================================\n");

    printf("\n============================================================\n");
    printf("Sistem Persamaan (U.x = y):\n");
    printf("Matriks U:\n");
    printMatrix(n, U);
    printf("Matriks y (Transpose):\n");
    for (int i = 0; i < n; i++) {
        printf("%12.6f ", y[i]);
    }
    printf("\n");

    backwardSubstitution(n, U, y, x);

    printf("\n============================================================\n");
    printf("Solusi untuk x (U.x = y):\n");
    for (int i = 0; i < n; i++) {
        printf("x%d = %12.6f\n", i + 1, x[i]);
    }
    printf("============================================================\n");

    return 0;
}

void luDecomposition(int n, double A[MAX][MAX], double L[MAX][MAX], double U[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int k = i; k < n; k++) {
            double sum = 0;
            for (int j = 0; j < i; j++) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }

        for (int k = i; k < n; k++) {
            if (i == k) {
                L[i][i] = 1; // Diagonal L = 1
            } else {
                double sum = 0;
                for (int j = 0; j < i; j++) {
                    sum += L[k][j] * U[j][i];
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }
}

void forwardSubstitution(int n, double L[MAX][MAX], double b[MAX], double y[MAX]) {
    for (int i = 0; i < n; i++) {
        double sum = 0;
        for (int j = 0; j < i; j++) {
            sum += L[i][j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i][i];
    }
}

void backwardSubstitution(int n, double U[MAX][MAX], double y[MAX], double x[MAX]) {
    for (int i = n - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += U[i][j] * x[j];
        }
        x[i] = (y[i] - sum) / U[i][i];
    }
}

void printMatrix(int n, double A[MAX][MAX]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%12.6f ", A[i][j]);
        }
        printf("\n");
    }
}
