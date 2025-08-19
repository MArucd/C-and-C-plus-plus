#include "../s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (ptr_is_null(A) || ptr_is_null(B) || ptr_is_null(result)) {
    return INCORRECT_MATRIX;
  } else if (equal_size(A, B) || inf_or_nan(A) || inf_or_nan(B)) {
    return CALCULATION_ERROR;
  }

  s21_create_matrix(A->rows, A->columns, result);
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      result->matrix[m][n] = A->matrix[m][n] - B->matrix[m][n];
    }
  }
  return OK;
}