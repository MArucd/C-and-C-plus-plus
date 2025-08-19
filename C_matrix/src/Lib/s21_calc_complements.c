#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (ptr_is_null(A) || ptr_is_null(result)) {
    return INCORRECT_MATRIX;
  } else if (A->rows != A->columns || inf_or_nan(A)) {
    return CALCULATION_ERROR;
  }

  s21_create_matrix(A->rows, A->columns, result);

  matrix_t determinant;

  if (A->rows > 1) {
    s21_create_matrix(A->rows - 1, A->columns - 1, &determinant);
  } else {
    result->matrix[0][0] = 1.;
  }

  for (int minor_row = 0; minor_row < A->rows && A->rows > 1; minor_row++) {
    for (int minor_col = 0; minor_col < A->columns; minor_col++) {
      record_determinant_matrix(&determinant, A, minor_row, minor_col);
      s21_determinant(&determinant, &result->matrix[minor_row][minor_col]);
    }
  }

  if (A->rows > 1) {
    s21_remove_matrix(&determinant);
    algebraic_complements(A, result);
  }

  return OK;
}