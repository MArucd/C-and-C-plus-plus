#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (ptr_is_null(A) || ptr_is_null(result)) {
    return INCORRECT_MATRIX;
  } else if (A->rows != A->columns || inf_or_nan(A)) {
    return CALCULATION_ERROR;
  }

  int res = OK;
  double det = 0.;
  s21_determinant(A, &det);

  if (det) {
    matrix_t complements, transpose;

    s21_calc_complements(A, &complements);
    s21_transpose(&complements, &transpose);

    det = 1 / det;

    s21_mult_number(&transpose, det, result);

    s21_remove_matrix(&complements);
    s21_remove_matrix(&transpose);
  } else {
    res = CALCULATION_ERROR;
  }
  return res;
}