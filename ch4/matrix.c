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
    printf("Matrix %dx%x\n", temp.row, temp.col);
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
        for (int i = 0; i < C.row; i++) {
            for (int j = 0; j < C.col; j++) {
                C.val[i][j] = 0;
                for (int k = 0; k < A.col; k++) {
                    C.val[i][j] += A.val[i][k] * B.val[k][j];
                }
            }
        }
        return C;
    }
}

void test(int i, int j, int k) {
    matrix A = cre_matrix(i, j);
    rand_matrix(&A);
    matrix B = cre_matrix(j, k);
    rand_matrix(&B);
    matrix C = multi(A, B);
    pri_matrix(A);
    pri_matrix(B);
    pri_matrix(C);
}

int main() {
    test(2, 3, 4);
    return 0;
}
