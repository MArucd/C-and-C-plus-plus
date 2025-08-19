#include "../s21_matrix.h"

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL && !negative_size(A->rows, A->columns)) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) {
        free(A->matrix[i]);
      }
    }
    free(A->matrix);
  }
  A->rows = 0;
  A->columns = 0;
}