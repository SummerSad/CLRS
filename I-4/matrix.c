#include <stdio.h>
#include <stdlib.h>

typedef struct matrix { int row, col, **val; } matrix;

matrix cre_matrix(int row, int col) {
    matrix temp;
    temp.row = row;
    temp.col = col;
    temp.val = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        temp.val[i] = (int *)malloc(col * sizeof(int));
    }
    return temp;
}

void rand_matrix(matrix *temp) {
    for (int i = 0; i < temp->row; i++) {
        for (int j = 0; j < temp->col; j++) {
            temp->val[i][j] = rand() % 10;
        }
    }
}

void del_matrix(matrix *temp) {
    for (int i = 0; i < temp->row; i++) {
        free(temp->val[i]);
    }
    free(temp->val);
}

void pri_matrix(matrix temp) {
    for (int i = 0; i < temp.row; i++) {
        for (int j = 0; j < temp.col; j++) {
            printf("%d ", temp.val[i][j]);
        }
        printf("\n");
    }
}

// Matrix multiplication
matrix multi(matrix A, matrix B) {
    if (A.col == B.row) {
        matrix C = cre_matrix(A.row, B.col);
    }
}

int main() {
    matrix A = cre_matrix(2, 3);
    rand_matrix(&A);
    pri_matrix(A);
    del_matrix(&A);
    return 0;
}
