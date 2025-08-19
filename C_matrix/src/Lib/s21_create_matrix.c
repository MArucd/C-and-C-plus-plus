#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (ptr_is_null(result) || negative_size(rows, columns)) {
    return INCORRECT_MATRIX;
  }
  int res = OK;
  int ptr = 0;
  result->matrix = (double **)calloc(rows, sizeof(double *));

  for (; ptr < rows; ptr++) {
    result->matrix[ptr] = (double *)calloc(columns, sizeof(double));
  }

  result->rows = rows;
  result->columns = columns;
  return res;
}