#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (ptr_is_null(A) || ptr_is_null(result)) {
    return INCORRECT_MATRIX;
  } else if (inf_or_nan(A) || isinf(number) || isnan(number)) {
    return CALCULATION_ERROR;
  }
  s21_create_matrix(A->rows, A->columns, result);

  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      result->matrix[m][n] = number * A->matrix[m][n];
    }
  }
  return OK;
}