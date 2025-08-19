#ifndef S21_matrix
#define S21_matrix

#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// основa

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_determinant(matrix_t *A, double *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// доп

int negative_size(int rows, int columns);
int ptr_is_null(matrix_t *A);
int equal_size(matrix_t *A, matrix_t *B);
int size_for_mult(matrix_t *A, matrix_t *B);
int inf_or_nan(matrix_t *A);
void record_determinant_matrix(matrix_t *determinant, matrix_t *A, int minor_row, int minor_col);
void algebraic_complements(matrix_t *A, matrix_t *result);

#endif