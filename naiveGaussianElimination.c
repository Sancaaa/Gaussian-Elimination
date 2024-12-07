#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 100

void betterForwardElimination(int n, double A[MAX][MAX+1]);
void backSubstitution(int n, double A[MAX][MAX+1], double x[MAX]);
void printMatrix(int n, double A[MAX][MAX+1]);
void printSolution(int n, double x[MAX]);

int main() {
    int n = 3; // INPUT banyak variabel
    double A[MAX][MAX+1] = {
        {3, 2, -1, 1},  //INPUT matriks
        {2, 3, 2, 12},
        {1, 1, 1, 3} 	 
    };
    double x[MAX]; // Solution array

    printf("============================================================\n");
    printf("Matrix Awal:\n");
    printMatrix(n, A);
    printf("============================================================\n");

    printf("============================================================\n");
    printf("Matrix Gaussian Elimination:\n");
    betterForwardElimination(n, A);
    printf("============================================================\n");

    printf("============================================================\n");
    printf("Hasil Subtitusi:\n");
    backSubstitution(n, A, x);
    printSolution(n, x);
    printf("============================================================");

    // double v = (x[0]*36) + (x[1]*6) + (x[2]); 
    // printf("\n %lf", v);

    return 0;
}

void betterForwardElimination(int n, double A[MAX][MAX+1]) {
    for (int i = 0; i < n - 1; i++) {
        int pivotRow = i; //pivot == patokan, awalnya 0 
        int swap = 0;
        for (int j = i + 1; j < n; j++) {
            if (fabs(A[j][i]) > fabs(A[pivotRow][i])) { //fabs == absolute value
                pivotRow = j;
                swap = 1;
            }
        }

        // Swap row
        for (int k = i; k <= n; k++) {
            double temp = A[i][k];
            A[i][k] = A[pivotRow][k];
            A[pivotRow][k] = temp;
        }

        if(swap == 1) {
            printf("\nMatriks setelah pertukaran baris %d dan %d:\n", i+1, pivotRow+1);
            printMatrix(n, A);
        }

        // Diagonal bawah 0
        for (int j = i + 1; j < n; j++) {
            double factor = A[j][i] / A[i][i];
            for (int k = i; k <= n; k++) {
                A[j][k] -= factor * A[i][k];
            }

            printf("\nMatriks setelah eliminasi untuk baris %d:\n", j+1);
            printMatrix(n, A);
        }
    }
}

void backSubstitution(int n, double A[MAX][MAX+1], double x[MAX]) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = A[i][n];
        for (int j = i + 1; j < n; j++) {
            x[i] -= A[i][j] * x[j];
        }
        x[i] /= A[i][i];
    }
}

void printMatrix(int n, double A[MAX][MAX+1]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= n; j++) {
            printf("%12.6f ", A[i][j]);
        }
        printf("\n");
    }
}

void printSolution(int n, double x[MAX]) {
    for (int i = 0; i < n; i++) {
        printf("x%d = %.6f\n", i + 1, x[i]);
    }
}