#include <check.h>

#include "s21_matrix.h"

START_TEST(create_matrix) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(5, 5, &A), OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(create_null_matrix) {
  ck_assert_int_eq(s21_create_matrix(3, 3, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(create_matrix_with_negative_size) {
  matrix_t A = {};
  ck_assert_int_eq(s21_create_matrix(3, 0, &A), INCORRECT_MATRIX);
}
END_TEST

START_TEST(remove_matrix) {
  matrix_t A = {};
  s21_remove_matrix(&A);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(eq_matrix) {
  matrix_t A = {};
  matrix_t B = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 3.;
  A.matrix[1][0] = 4.;
  A.matrix[1][1] = 5.;
  A.matrix[1][2] = 6.;
  A.matrix[2][0] = 7.;
  A.matrix[2][1] = 8.;
  A.matrix[2][2] = 9.;

  B.matrix[0][0] = 1.;
  B.matrix[0][1] = 2.;
  B.matrix[0][2] = 3.;
  B.matrix[1][0] = 4.;
  B.matrix[1][1] = 5.;
  B.matrix[1][2] = 6.;
  B.matrix[2][0] = 7.;
  B.matrix[2][1] = 8.;
  B.matrix[2][2] = 9.;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(non_eq_matrix) {
  matrix_t A;
  matrix_t B;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 2.;
  A.matrix[1][0] = 4.;
  A.matrix[1][1] = 5.;
  A.matrix[1][2] = 6.;
  A.matrix[2][0] = 7.;
  A.matrix[2][1] = 8.;
  A.matrix[2][2] = 9.;

  B.matrix[0][0] = 1.;
  B.matrix[0][1] = 2.;
  B.matrix[0][2] = 3.;
  B.matrix[1][0] = 4.;
  B.matrix[1][1] = 5.;
  B.matrix[1][2] = 6.;
  B.matrix[2][0] = 7.;
  B.matrix[2][1] = 8.;
  B.matrix[2][2] = 9.;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix3) {
  // different dimensions

  matrix_t A;
  matrix_t B;

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 5, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(eq_matrix4) {
  // failure with incorrect matrix
  matrix_t A = {};
  matrix_t B = {};
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sum_matrix1) {
  // case with success
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t sum = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &sum);

  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 3.;
  A.matrix[1][0] = 4.;
  A.matrix[1][1] = 5.;
  A.matrix[1][2] = 6.;
  A.matrix[2][0] = 7.;
  A.matrix[2][1] = 8.;
  A.matrix[2][2] = 9.;

  B.matrix[0][0] = 11.;
  B.matrix[0][1] = 12.;
  B.matrix[0][2] = 1.;
  B.matrix[1][0] = 2.;
  B.matrix[1][1] = 13.;
  B.matrix[1][2] = 11.;
  B.matrix[2][0] = 10.;
  B.matrix[2][1] = 12.;
  B.matrix[2][2] = 13.;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  sum.matrix[0][0] = 12.;
  sum.matrix[0][1] = 14.;
  sum.matrix[0][2] = 4.;
  sum.matrix[1][0] = 6.;
  sum.matrix[1][1] = 18.;
  sum.matrix[1][2] = 17.;
  sum.matrix[2][0] = 17.;
  sum.matrix[2][1] = 20.;
  sum.matrix[2][2] = 22.;

  ck_assert_int_eq(s21_eq_matrix(&result, &sum), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&sum);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix2) {
  // failure with wrong matricies;
  matrix_t A = {};
  matrix_t B = {};
  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(sum_matrix3) {
  // failire with different dimensions of matrices
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 4, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_4) {
  // failure with non-finite value

  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 3.;
  A.matrix[1][0] = 4.;
  A.matrix[1][1] = 5.;
  A.matrix[1][2] = 6.;
  A.matrix[2][0] = 7.;
  A.matrix[2][1] = 8.;
  A.matrix[2][2] = 9.;

  B.matrix[0][0] = 11.;
  B.matrix[0][1] = 12.;
  B.matrix[0][2] = 1.;
  B.matrix[1][0] = 2.;
  B.matrix[1][1] = 13.;
  B.matrix[1][2] = 11.;
  B.matrix[2][0] = 10.;
  B.matrix[2][1] = 12.;
  B.matrix[2][2] = INFINITY;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_5) {
  // success with uninitialized values
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t sum = {};

  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  s21_create_matrix(5, 5, &sum);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &sum), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&sum);
}
END_TEST

START_TEST(sub_matrix_1) {
  // case with success
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t sum = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &sum);

  A.matrix[0][0] = 10;
  A.matrix[0][1] = 20;
  A.matrix[0][2] = 30;
  A.matrix[1][0] = 40;
  A.matrix[1][1] = 50;
  A.matrix[1][2] = 60;
  A.matrix[2][0] = 70;
  A.matrix[2][1] = 80;
  A.matrix[2][2] = 90;

  B.matrix[0][0] = 10;
  B.matrix[0][1] = 10;
  B.matrix[0][2] = 10;
  B.matrix[1][0] = 10;
  B.matrix[1][1] = 10;
  B.matrix[1][2] = 10;
  B.matrix[2][0] = 10;
  B.matrix[2][1] = 10;
  B.matrix[2][2] = 10;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  sum.matrix[0][0] = 0.;
  sum.matrix[0][1] = 10;
  sum.matrix[0][2] = 20;
  sum.matrix[1][0] = 30;
  sum.matrix[1][1] = 40;
  sum.matrix[1][2] = 50;
  sum.matrix[2][0] = 60;
  sum.matrix[2][1] = 70;
  sum.matrix[2][2] = 80;

  ck_assert_int_eq(s21_eq_matrix(&result, &sum), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&sum);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_2) {
  // failure with wrong matricies;
  matrix_t A = {};
  matrix_t B = {};
  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(sub_matrix_3) {
  // failire with different dimensions of matrices
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 4, &B);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_4) {
  // failure with non-finite value

  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  A.matrix[0][0] = 1.;
  A.matrix[0][1] = 2.;
  A.matrix[0][2] = 3.;
  A.matrix[1][0] = 4.;
  A.matrix[1][1] = 5.;
  A.matrix[1][2] = 6.;
  A.matrix[2][0] = 7.;
  A.matrix[2][1] = 8.;
  A.matrix[2][2] = 9.;

  B.matrix[0][0] = 11.;
  B.matrix[0][1] = 12.;
  B.matrix[0][2] = 1.;
  B.matrix[1][0] = 2.;
  B.matrix[1][1] = 13.;
  B.matrix[1][2] = 11.;
  B.matrix[2][0] = 10.;
  B.matrix[2][1] = 12.;
  B.matrix[2][2] = INFINITY;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_5) {
  // success with uninitialized values
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t sub = {};

  s21_create_matrix(5, 5, &A);
  s21_create_matrix(5, 5, &B);
  s21_create_matrix(5, 5, &sub);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &sub), SUCCESS);
}
END_TEST

START_TEST(mult_number_1) {
  // normal case
  matrix_t A = {};
  matrix_t result = {};
  matrix_t arr = {};
  double n = 2;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  ck_assert_int_eq(s21_mult_number(&A, n, &result), OK);
  s21_create_matrix(3, 3, &arr);
  arr.matrix[0][0] = 2;
  arr.matrix[0][1] = 4;
  arr.matrix[0][2] = 6;
  arr.matrix[1][0] = 8;
  arr.matrix[1][1] = 10;
  arr.matrix[1][2] = 12;
  arr.matrix[2][0] = 14;
  arr.matrix[2][1] = 16;
  arr.matrix[2][2] = 18;
  ck_assert_int_eq(s21_eq_matrix(&result, &arr), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&arr);
}
END_TEST

START_TEST(mult_number_2) {
  // success with uninitialized values
  matrix_t A = {};
  matrix_t result = {};
  matrix_t arr = {};
  double n = 2;
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_mult_number(&A, n, &result), OK);
  s21_create_matrix(3, 3, &arr);
  ck_assert_int_eq(s21_eq_matrix(&result, &arr), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&arr);
}
END_TEST

START_TEST(mult_number_3) {
  // failure with non-finite matrix
  matrix_t A = {};
  matrix_t result = {};
  double num = 3;
  s21_create_matrix(3, 3, &A);
  A.matrix[0][1] = INFINITY;
  ck_assert_int_eq(s21_mult_number(&A, num, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_4) {
  // failure with non finite double
  matrix_t A = {};
  matrix_t result = {};
  double num = INFINITY;
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_mult_number(&A, num, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_number_5) {
  matrix_t A = {};
  double num = 3.1;
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_mult_number(&A, num, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(mult_matrix_1) {
  // success with ordinary case
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t arr = {};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 4;
  A.matrix[0][1] = 3;
  A.matrix[1][0] = 7;
  A.matrix[1][1] = 5;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = -28;
  B.matrix[0][1] = 93;
  B.matrix[1][0] = 38;
  B.matrix[1][1] = -126;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  s21_create_matrix(2, 2, &arr);
  arr.matrix[0][0] = 2;
  arr.matrix[0][1] = -6;
  arr.matrix[1][0] = -6;
  arr.matrix[1][1] = 21;
  ck_assert_int_eq(s21_eq_matrix(&arr, &result), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&arr);
}
END_TEST

START_TEST(mult_matrix_2) {
  // succes with uninitialized values
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};
  matrix_t arr = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &arr);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &arr), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&arr);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_matrix_3) {
  // fail with different dimensions of matrices
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(3, 2, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_4) {
  // fail with non-finite matrix
  matrix_t A = {};
  matrix_t B = {};
  matrix_t result = {};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  B.matrix[2][2] = INFINITY;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(mult_matrix_5) {
  // fail with INCORRECT_MATRIX
  matrix_t A = {};
  s21_create_matrix(3, 3, &A);
  ck_assert_int_eq(s21_mult_matrix(&A, NULL, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(transpose_1) {
  // success with normal matrix
  matrix_t A = {};
  matrix_t result = {};
  matrix_t answer = {};
  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  s21_create_matrix(2, 3, &answer);
  answer.matrix[0][0] = 1;
  answer.matrix[0][1] = 2;
  answer.matrix[0][2] = 3;
  answer.matrix[1][0] = 4;
  answer.matrix[1][1] = 5;
  answer.matrix[1][2] = 6;
  ck_assert_int_eq(s21_eq_matrix(&result, &answer), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&answer);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(transpose_2) {
  // succes with uninitialized matrix 3x2
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 2, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(result.rows, 2);
  ck_assert_int_eq(result.columns, 3);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(determinant_1) {
  // normal case 3x3
  matrix_t A = {};
  double result;

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 0.);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_2) {
  // success with 1x1
  matrix_t A = {};
  double result;

  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 21;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 21);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_3) {
  // success with 3x3
  matrix_t A = {};
  double result;

  s21_create_matrix(2, 2, &A);

  A.matrix[0][0] = 11;
  A.matrix[0][1] = -3;
  A.matrix[1][0] = -15;
  A.matrix[1][1] = -2;

  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, -67);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(determinant_4) {
  // fail with non-square matrix
  matrix_t A = {};
  double result;
  s21_create_matrix(3, 2, &A);

  ck_assert_int_eq(s21_determinant(&A, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_1) {
  // success with normal matrix 3x3

  matrix_t A = {};
  matrix_t result = {};
  matrix_t answer = {};

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);

  s21_create_matrix(3, 3, &answer);

  answer.matrix[0][0] = 0;
  answer.matrix[0][1] = 10;
  answer.matrix[0][2] = -20;
  answer.matrix[1][0] = 4;
  answer.matrix[1][1] = -14;
  answer.matrix[1][2] = 8;
  answer.matrix[2][0] = -8;
  answer.matrix[2][1] = -2;
  answer.matrix[2][2] = 4;

  ck_assert_int_eq(s21_eq_matrix(&result, &answer), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(calc_complements_2) {
  // fail with non-square matrix
  matrix_t A = {};
  matrix_t result = {};

  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_calc_complements(&A, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(calc_complements_3) {
  // fail with INCORRECT_MATRIX
  matrix_t A = {};

  s21_create_matrix(3, 3, &A);

  ck_assert_int_eq(s21_calc_complements(&A, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_1) {
  // success with normal 3x3 matrix
  matrix_t A = {};
  matrix_t result = {};
  matrix_t answer = {};

  s21_create_matrix(3, 3, &A);

  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);

  s21_create_matrix(3, 3, &answer);

  answer.matrix[0][0] = 1.;
  answer.matrix[0][1] = -1.;
  answer.matrix[0][2] = 1.;
  answer.matrix[1][0] = -38.;
  answer.matrix[1][1] = 41.;
  answer.matrix[1][2] = -34.;
  answer.matrix[2][0] = 27.;
  answer.matrix[2][1] = -29.;
  answer.matrix[2][2] = 24.;

  ck_assert_int_eq(s21_eq_matrix(&result, &answer), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(inverse_matrix_2) {
  // success with matrix 1x1
  matrix_t A = {};
  matrix_t result = {};
  matrix_t answer = {};

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &answer);

  A.matrix[0][0] = 21;
  answer.matrix[0][0] = 1.0 / 21.0;

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &answer), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&answer);
}
END_TEST

START_TEST(inverse_matrix_3) {
  // fail with non-square matrix
  matrix_t A = {};
  matrix_t result = {};

  s21_create_matrix(5, 3, &A);

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_4) {
  // fail when the determinant of matrix equals zero
  matrix_t A = {};
  matrix_t result = {};

  s21_create_matrix(3, 3, &A);

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 0.0;
    }
  }

  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_matrix_5) {
  // fail with INCORRECT_MATRIX
  matrix_t A = {};

  s21_create_matrix(3, 3, &A);

  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&A);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, create_matrix);
  tcase_add_test(tc1_1, create_null_matrix);
  tcase_add_test(tc1_1, create_matrix_with_negative_size);
  tcase_add_test(tc1_1, remove_matrix);
  tcase_add_test(tc1_1, eq_matrix);
  tcase_add_test(tc1_1, non_eq_matrix);
  tcase_add_test(tc1_1, eq_matrix3);
  tcase_add_test(tc1_1, eq_matrix4);
  tcase_add_test(tc1_1, sum_matrix1);
  tcase_add_test(tc1_1, sum_matrix2);
  tcase_add_test(tc1_1, sum_matrix3);
  tcase_add_test(tc1_1, sum_matrix_4);
  tcase_add_test(tc1_1, sum_matrix_5);
  tcase_add_test(tc1_1, sub_matrix_1);
  tcase_add_test(tc1_1, sub_matrix_2);
  tcase_add_test(tc1_1, sub_matrix_3);
  tcase_add_test(tc1_1, sub_matrix_4);
  tcase_add_test(tc1_1, sub_matrix_5);
  tcase_add_test(tc1_1, mult_number_1);
  tcase_add_test(tc1_1, mult_number_2);
  tcase_add_test(tc1_1, mult_number_3);
  tcase_add_test(tc1_1, mult_number_4);
  tcase_add_test(tc1_1, mult_number_5);
  tcase_add_test(tc1_1, mult_matrix_1);
  tcase_add_test(tc1_1, mult_matrix_2);
  tcase_add_test(tc1_1, mult_matrix_3);
  tcase_add_test(tc1_1, mult_matrix_4);
  tcase_add_test(tc1_1, mult_matrix_5);
  tcase_add_test(tc1_1, transpose_1);
  tcase_add_test(tc1_1, transpose_2);
  tcase_add_test(tc1_1, determinant_1);
  tcase_add_test(tc1_1, determinant_2);
  tcase_add_test(tc1_1, determinant_3);
  tcase_add_test(tc1_1, determinant_4);
  tcase_add_test(tc1_1, calc_complements_1);
  tcase_add_test(tc1_1, calc_complements_2);
  tcase_add_test(tc1_1, calc_complements_3);
  tcase_add_test(tc1_1, inverse_matrix_1);
  tcase_add_test(tc1_1, inverse_matrix_2);
  tcase_add_test(tc1_1, inverse_matrix_3);
  tcase_add_test(tc1_1, inverse_matrix_4);
  tcase_add_test(tc1_1, inverse_matrix_5);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
