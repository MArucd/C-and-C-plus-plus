#include <math.h>

#include "../s21_matrix.h"
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (ptr_is_null(A) || ptr_is_null(B) || ptr_is_null(result)) {
    return INCORRECT_MATRIX;
  } else if (size_for_mult(A, B) || inf_or_nan(A) || inf_or_nan(B)) {
    return CALCULATION_ERROR;
  }
  s21_create_matrix(A->rows, B->columns, result);

  for (int m1 = 0, m = 0; m1 < A->rows; m1++, m++) {
    for (int n2 = 0, n = 0; n2 < B->columns; n2++, n++) {
      for (int n1 = 0, m2 = 0; n1 < A->columns; n1++, m2++) {
        result->matrix[m][n] += A->matrix[m1][n1] * B->matrix[m2][n2];
      }
    }
  }
  return OK;
}