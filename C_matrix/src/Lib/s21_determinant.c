#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  if (ptr_is_null(A) || result == NULL) {
    return INCORRECT_MATRIX;
  } else if (A->rows != A->columns || inf_or_nan(A)) {
    return CALCULATION_ERROR;
  }
  matrix_t copy;
  s21_create_matrix(A->rows, A->columns, &copy);

  for (int i = 0; i < copy.rows; i++) {
    for (int j = 0; j < copy.columns; j++) {
      copy.matrix[i][j] = A->matrix[i][j];
    }
  }

  int not_zero = 0, all_zero = 1, sign = 1;
  double *tmp = NULL;
  *result = 1.;

  for (int rows = 0; rows < copy.rows - 1 && *result; rows++) {
    for (not_zero = rows, all_zero = 1; not_zero < copy.rows; not_zero++) {
      if (copy.matrix[not_zero][rows]) {
        tmp = copy.matrix[not_zero];
        all_zero = 0;
        break;
      }
    }

    if (copy.matrix[rows][rows] == 0. && tmp) {
      copy.matrix[not_zero] = copy.matrix[rows];
      copy.matrix[rows] = tmp;
      sign = -sign;
    }

    if (all_zero) {
      *result = 0.;
    } else {
      for (int m = rows + 1; m < copy.rows; m++) {
        double tmp = copy.matrix[m][rows] / copy.matrix[rows][rows];

        for (int n = rows; n < copy.columns; n++) {
          copy.matrix[m][n] -= copy.matrix[rows][n] * tmp;
        }
      }
    }
  }

  for (int k = 0; k < A->rows; k++) {
    *result *= copy.matrix[k][k];
  }

  *result *= sign;
  s21_remove_matrix(&copy);

  return OK;
}