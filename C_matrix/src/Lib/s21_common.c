#include "../s21_matrix.h"

int negative_size(int rows, int columns) { return rows <= 0 || columns <= 0; }

int ptr_is_null(matrix_t *A) { return A == NULL; }

int equal_size(matrix_t *A, matrix_t *B) {
  return A->rows != B->rows || A->columns != B->columns;
}

int size_for_mult(matrix_t *A, matrix_t *B) { return A->columns != B->rows; }

int inf_or_nan(matrix_t *A) {
  int res = OK;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (isinf(A->matrix[i][j]) || isnan(A->matrix[i][j])) {
        res = CALCULATION_ERROR;
        i = A->rows;
        j = A->columns;
      }
    }
  }
  return res;
}

void record_determinant_matrix(matrix_t *determinant, matrix_t *A,
                               int minor_row, int minor_col) {
  for (int src_row = 0, det_rows = 0; src_row < A->rows; src_row++) {
    for (int src_col = 0, det_col = 0; src_col < A->columns; src_col++) {
      if (src_row != minor_row && src_col != minor_col) {
        determinant->matrix[det_rows][det_col] = A->matrix[src_row][src_col];
        det_col++;

        if (det_col == determinant->columns) {
          det_rows++;
          det_col = 0;
        }
      }
    }
  }
}

void algebraic_complements(matrix_t *A, matrix_t *result) {
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      if ((n + m) % 2) {
        result->matrix[m][n] *= -1;
      }
    }
  }
}