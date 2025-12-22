#include <stdio.h>

#define MAX 10

void inputMatrix(int mat[MAX][MAX], int row, int col) {
    printf("Enter elements of matrix (%dx%d):\n", row, col);
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            scanf("%d", &mat[i][j]);
}

void printMatrix(int mat[MAX][MAX], int row, int col) {
    for(int i=0; i<row; i++) {
        for(int j=0; j<col; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}

void addMatrices(int a[MAX][MAX], int b[MAX][MAX], int row, int col, int result[MAX][MAX]) {
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            result[i][j] = a[i][j] + b[i][j];
}

void multiplyMatrices(int a[MAX][MAX], int b[MAX][MAX], int row1, int col1, int col2, int result[MAX][MAX]) {
    for(int i=0; i<row1; i++) {
        for(int j=0; j<col2; j++) {
            result[i][j] = 0;
            for(int k=0; k<col1; k++)
                result[i][j] += a[i][k] * b[k][j];
        }
    }
}

void transposeMatrix(int mat[MAX][MAX], int row, int col, int result[MAX][MAX]) {
    for(int i=0; i<row; i++)
        for(int j=0; j<col; j++)
            result[j][i] = mat[i][j];
}

int main() {
    int a[MAX][MAX], b[MAX][MAX], res[MAX][MAX];
    int row1, col1, row2, col2;

    printf("Matrix 1 size (rows cols): ");
    scanf("%d %d", &row1, &col1);
    inputMatrix(a, row1, col1);

    printf("Matrix 2 size (rows cols): ");
    scanf("%d %d", &row2, &col2);
    inputMatrix(b, row2, col2);

    // Addition
    if(row1 == row2 && col1 == col2) {
        addMatrices(a, b, row1, col1, res);
        printf("Sum of matrices:\n");
        printMatrix(res, row1, col1);
    } else {
        printf("Matrix addition not possible due to size mismatch.\n");
    }

    // Multiplication
    if(col1 == row2) {
        multiplyMatrices(a, b, row1, col1, col2, res);
        printf("Product of matrices:\n");
        printMatrix(res, row1, col2);
    } else {
        printf("Matrix multiplication not possible due to size mismatch.\n");
    }

    // Transpose of first matrix
    transposeMatrix(a, row1, col1, res);
    printf("Transpose of first matrix:\n");
    printMatrix(res, col1, row1);

    return 0;
}
