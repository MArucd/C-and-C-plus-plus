#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

TEST(EqMatrix, eq) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = b(i, j) = j;
    }
  }
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(EqMatrix, eq2) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = b(i, j) = i + j;
    }
  }
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(EqMatrix, eq3) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = b(i, j) = (i + j) / 3;
    }
  }
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(EqMatrix, NotEqual) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = i + j;
      b(i, j) = i + j + 1;
    }
  }
  ASSERT_EQ(a.EqMatrix(b), 0);
  ASSERT_EQ(b.EqMatrix(a), 0);
}

TEST(EqMatrix, PrecisionTest) {
  int size = 5;
  S21Matrix a(size, size), b(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = b(i, j) = (i + j) / 3;
    }
  }
  a(4, 3) -= 0.000002;
  ASSERT_EQ(a.EqMatrix(b), 0);
  ASSERT_EQ(b.EqMatrix(a), 0);
}

TEST(EqMatrix, DiffDimension) {
  int size = 4;
  S21Matrix a(size, size), b(size - 1, size - 1);
  ASSERT_EQ(a.EqMatrix(b), 0);
  ASSERT_EQ(b.EqMatrix(a), 0);
}

TEST(EqMatrix, EmptyMatrices) {
  int size = 9;
  S21Matrix a(size, size), b(size, size);
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(EqMatrix, Uninitialized) {
  S21Matrix a, b;
  ASSERT_EQ(a.EqMatrix(b), 1);
  ASSERT_EQ(b.EqMatrix(a), 1);
}

TEST(MulNumber, 1dMatrix) {
  S21Matrix source;
  source(0, 0) = 3.141592;
  source.MulNumber(2.718281);
  S21Matrix expected;
  expected(0, 0) = 8.53972984335;
  ASSERT_EQ(source.EqMatrix(expected), true);
}

TEST(MulNumber, 3dMatrix) {
  S21Matrix source(3, 3);
  source(0, 0) = 1.3;
  source(1, 0) = 89.13;
  source(2, 0) = 1;
  source(0, 1) = 9.1;
  source(1, 1) = 7;
  source(2, 1) = 1389;
  source(0, 2) = 8.123;
  source(1, 2) = 0;
  source(2, 2) = 0.0004;
  source.MulNumber(1.234567);
  S21Matrix expected(3, 3);
  expected(0, 0) = 1.3 * 1.234567;
  expected(1, 0) = 89.13 * 1.234567;
  expected(2, 0) = 1 * 1.234567;
  expected(0, 1) = 9.1 * 1.234567;
  expected(1, 1) = 7 * 1.234567;
  expected(2, 1) = 1389 * 1.234567;
  expected(0, 2) = 8.123 * 1.234567;
  expected(1, 2) = 0 * 1.234567;
  expected(2, 2) = 0.0004 * 1.234567;
  ASSERT_EQ(source.EqMatrix(expected), 1);
}

TEST(Constructor, Constructor_null) {
  S21Matrix Matrix;
  EXPECT_EQ(Matrix.GetRows(), 1);
  EXPECT_EQ(Matrix.GetCols(), 1);
}

TEST(Constructor, Constructor_1) {
  int rows = 3;
  int columns = 4;
  S21Matrix Matrix(rows, columns);
  EXPECT_EQ(Matrix.GetCols(), columns);
  EXPECT_EQ(Matrix.GetRows(), rows);
}

TEST(Constructor, Constructor_Copy) {
  int rows = 3;
  int columns = 4;
  S21Matrix sample(rows, columns);
  S21Matrix expect(sample);
  EXPECT_EQ(sample.EqMatrix(expect), true);
}

TEST(Constructors, Copy) {
  S21Matrix source(3, 3);
  source(0, 0) = 99;
  source(2, 2) = -99;
  source(1, 1) = 13;
  S21Matrix copy(source);
  ASSERT_EQ(source.EqMatrix(copy), 1);
}

TEST(Complements, 1) {
  S21Matrix source(3, 3);
  S21Matrix expected(3, 3);
  source(0, 0) = 1;
  source(0, 1) = 2;
  source(0, 2) = 3;
  source(1, 0) = 0;
  source(1, 1) = 4;
  source(1, 2) = 2;
  source(2, 0) = 5;
  source(2, 1) = 2;
  source(2, 2) = 1;
  expected(0, 0) = 0;
  expected(0, 1) = 10;
  expected(0, 2) = -20;
  expected(1, 0) = 4;
  expected(1, 1) = -14;
  expected(1, 2) = 8;
  expected(2, 0) = -8;
  expected(2, 1) = -2;
  expected(2, 2) = 4;
  S21Matrix result = source.CalcComplements();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Complements, 2) {
  S21Matrix source(3, 3);
  S21Matrix expected(3, 3);
  source(0, 0) = 1.0;
  source(0, 1) = 2.0;
  source(0, 2) = 3.0;
  source(1, 0) = 0.0;
  source(1, 1) = 4.0;
  source(1, 2) = 2.0;
  source(2, 0) = 5.0;
  source(2, 1) = 2.0;
  source(2, 2) = 1.0;
  expected(0, 0) = 0.0;
  expected(0, 1) = 10.0;
  expected(0, 2) = -20.0;
  expected(1, 0) = 4.0;
  expected(1, 1) = -14.0;
  expected(1, 2) = 8.0;
  expected(2, 0) = -8.0;
  expected(2, 1) = -2.0;
  expected(2, 2) = 4.0;
  S21Matrix result = source.CalcComplements();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Complements, 2d) {
  S21Matrix source(2, 2), expected(2, 2);
  source(0, 0) = 3;
  source(0, 1) = 1;
  source(1, 0) = 20;
  source(1, 1) = -2;
  expected(0, 0) = -2;
  expected(0, 1) = -20;
  expected(1, 0) = -1;
  expected(1, 1) = 3;
  S21Matrix result = source.CalcComplements();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Determinant, J) {
  int size = 5;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = j;
    }
  }
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 0);
}

TEST(Determinant, iplj) {
  int size = 5;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 0);
}

TEST(Determinant, 3) {
  int size = 3;
  S21Matrix source(size, size);
  source(0, 0) = 2;
  source(0, 1) = 3;
  source(0, 2) = 1;
  source(1, 0) = 7;
  source(1, 1) = 4;
  source(1, 2) = 1;
  source(2, 0) = 9;
  source(2, 1) = -2;
  source(2, 2) = 1;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, -32);
}

TEST(Determinant, 2) {
  int size = 2;
  S21Matrix source(size, size);
  source(0, 0) = -5;
  source(0, 1) = -4;
  source(1, 0) = -2;
  source(1, 1) = -3;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 7);
}

TEST(Determinant, 8) {
  int size = 8;
  S21Matrix source(size, size);
  source(0, 0) = 2;
  source(0, 1) = 8;
  source(0, 2) = 7;
  source(0, 3) = 4;
  source(0, 4) = 1;
  source(0, 5) = 8;
  source(0, 6) = 3;
  source(0, 7) = 9;
  source(1, 0) = 4;
  source(1, 1) = 2;
  source(1, 2) = 6;
  source(1, 3) = 2;
  source(1, 4) = 2;
  source(1, 5) = 1;
  source(1, 6) = 5;
  source(1, 7) = 8;
  source(2, 0) = 8;
  source(2, 1) = 6;
  source(2, 2) = 7;
  source(2, 3) = 7;
  source(2, 4) = 3;
  source(2, 5) = 4;
  source(2, 6) = 4;
  source(2, 7) = 1;
  source(3, 0) = 1;
  source(3, 1) = 7;
  source(3, 2) = 0;
  source(3, 3) = 4;
  source(3, 4) = 4;
  source(3, 5) = 3;
  source(3, 6) = 0;
  source(3, 7) = 5;
  source(4, 0) = 5;
  source(4, 1) = 7;
  source(4, 2) = 5;
  source(4, 3) = 6;
  source(4, 4) = 8;
  source(4, 5) = 3;
  source(4, 6) = 1;
  source(4, 7) = 9;
  source(5, 0) = 3;
  source(5, 1) = 7;
  source(5, 2) = 8;
  source(5, 3) = 0;
  source(5, 4) = 5;
  source(5, 5) = 7;
  source(5, 6) = 0;
  source(5, 7) = 2;
  source(6, 0) = 5;
  source(6, 1) = 8;
  source(6, 2) = 3;
  source(6, 3) = 5;
  source(6, 4) = 9;
  source(6, 5) = 1;
  source(6, 6) = 2;
  source(6, 7) = 0;
  source(7, 0) = 7;
  source(7, 1) = 8;
  source(7, 2) = 7;
  source(7, 3) = 4;
  source(7, 4) = 7;
  source(7, 5) = 9;
  source(7, 6) = 1;
  source(7, 7) = 5;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, -616458);
}

TEST(Determinant, 1) {
  S21Matrix source(1, 1);
  source(0, 0) = 9;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 9);
}

TEST(Determinant, AllZero) {
  S21Matrix source(9, 9);
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, 0);
}

TEST(Determinant, 2dMatrix) {
  S21Matrix source(2, 2);
  source(0, 0) = 73;
  source(0, 1) = 16;
  source(1, 0) = 0;
  source(1, 1) = -4;
  double result = source.Determinant();
  ASSERT_DOUBLE_EQ(result, -292);
}

TEST(Mutators, Setter1) {
  int size = 9;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  size--;
  source.SetRows(size);
  ASSERT_EQ(source.GetRows(), size);
}

TEST(Mutators, Setter2) {
  int size = 9;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  size++;
  source.SetRows(size);
  ASSERT_EQ(source.GetRows(), size);
  ASSERT_DOUBLE_EQ(source(size - 1, size - 2), 0);
}

TEST(Mutators, Setter3) {
  int size = 9;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  size--;
  source.SetColumns(size);
  ASSERT_EQ(source.GetCols(), size);
}

TEST(Mutators, Setter4) {
  int size = 9;
  S21Matrix source(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      source(i, j) = i + j;
    }
  }
  size++;
  source.SetColumns(size);
  ASSERT_EQ(source.GetCols(), size);
  ASSERT_DOUBLE_EQ(source(size - 2, size - 1), 0);
}

TEST(Overload, Sum) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  S21Matrix result = source1 + source2;

  expected(0, 0) = 352.412 + 352.412;
  expected(1, 0) = 1 + 1;
  expected(2, 0) = 1;
  expected(0, 1) = -1234.8234 + 1234.8234;
  expected(1, 1) = 0.00001 + 0.00001;
  expected(2, 1) = 352.412 + 123456789;
  expected(0, 2) = -0.00001 + 1234.8234;
  expected(1, 2) = 352.412 + 0.412;
  expected(2, 2) = 9 + 9;

  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, Sub) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  S21Matrix result = source1 - source2;
  expected(0, 0) = 352.412 - 352.412;
  expected(1, 0) = 0;
  expected(2, 0) = 1;
  expected(0, 1) = 1234.8234 - -1234.8234;
  expected(1, 1) = 0.00001 - 0.00001;
  expected(2, 1) = 352.412 - 123456789;
  expected(0, 2) = 1234.8234 - -0.00001;
  expected(1, 2) = 352.412 - 0.412;
  expected(2, 2) = 0;
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, MulNum1) {
  S21Matrix source(3, 3);
  source(0, 0) = 1.3;
  source(1, 0) = 89.13;
  source(2, 0) = 1;
  source(0, 1) = 9.1;
  source(1, 1) = 7;
  source(2, 1) = 1389;
  source(0, 2) = 8.123;
  source(1, 2) = 0;
  source(2, 2) = 0.0004;
  S21Matrix result = source * 1.234567;
  S21Matrix expected(3, 3);
  expected(0, 0) = 1.3 * 1.234567;
  expected(1, 0) = 89.13 * 1.234567;
  expected(2, 0) = 1 * 1.234567;
  expected(0, 1) = 9.1 * 1.234567;
  expected(1, 1) = 7 * 1.234567;
  expected(2, 1) = 1389 * 1.234567;
  expected(0, 2) = 8.123 * 1.234567;
  expected(1, 2) = 0 * 1.234567;
  expected(2, 2) = 0.0004 * 1.234567;
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, MulNum2) {
  S21Matrix source(3, 3);
  source(0, 0) = 1.3;
  source(1, 0) = 89.13;
  source(2, 0) = 1;
  source(0, 1) = 9.1;
  source(1, 1) = 7;
  source(2, 1) = 1389;
  source(0, 2) = 8.123;
  source(1, 2) = 0;
  source(2, 2) = 0.0004;
  S21Matrix result = 1.234567 * source;
  S21Matrix expected(3, 3);
  expected(0, 0) = 1.3 * 1.234567;
  expected(1, 0) = 89.13 * 1.234567;
  expected(2, 0) = 1 * 1.234567;
  expected(0, 1) = 9.1 * 1.234567;
  expected(1, 1) = 7 * 1.234567;
  expected(2, 1) = 1389 * 1.234567;
  expected(0, 2) = 8.123 * 1.234567;
  expected(1, 2) = 0 * 1.234567;
  expected(2, 2) = 0.0004 * 1.234567;
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, MulMat) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 3;
  source1(0, 1) = 27;
  source1(0, 2) = 18;
  source1(1, 0) = 0;
  source1(1, 1) = 18;
  source1(1, 2) = 15;
  source1(2, 0) = 24;
  source1(2, 1) = 9;
  source1(2, 2) = 9;

  source2(0, 0) = 3;
  source2(0, 1) = 18;
  source2(0, 2) = 24;
  source2(1, 0) = 21;
  source2(1, 1) = 15;
  source2(1, 2) = 24;
  source2(2, 0) = 0;
  source2(2, 1) = 27;
  source2(2, 2) = 3;

  expected(0, 0) = 576;
  expected(0, 1) = 945;
  expected(0, 2) = 774;
  expected(1, 0) = 378;
  expected(1, 1) = 675;
  expected(1, 2) = 477;
  expected(2, 0) = 261;
  expected(2, 1) = 810;
  expected(2, 2) = 819;

  S21Matrix result = source1 * source2;
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Overload, SumCut) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  source1 += source2;
  expected(0, 0) = 352.412 + 352.412;
  expected(1, 0) = 1 + 1;
  expected(2, 0) = 1;
  expected(0, 1) = -1234.8234 + 1234.8234;
  expected(1, 1) = 0.00001 + 0.00001;
  expected(2, 1) = 352.412 + 123456789;
  expected(0, 2) = -0.00001 + 1234.8234;
  expected(1, 2) = 352.412 + 0.412;
  expected(2, 2) = 9 + 9;
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(Overload, SubCut) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  source1 -= source2;
  expected(0, 0) = 352.412 - 352.412;
  expected(1, 0) = 0;
  expected(2, 0) = 1;
  expected(0, 1) = 1234.8234 - -1234.8234;
  expected(1, 1) = 0.00001 - 0.00001;
  expected(2, 1) = 352.412 - 123456789;
  expected(0, 2) = 1234.8234 - -0.00001;
  expected(1, 2) = 352.412 - 0.412;
  expected(2, 2) = 0;
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(Overload, MulNum1Cut) {
  S21Matrix source(3, 3);
  source(0, 0) = 1.3;
  source(1, 0) = 89.13;
  source(2, 0) = 1;
  source(0, 1) = 9.1;
  source(1, 1) = 7;
  source(2, 1) = 1389;
  source(0, 2) = 8.123;
  source(1, 2) = 0;
  source(2, 2) = 0.0004;
  source *= 1.234567;
  S21Matrix expected(3, 3);
  expected(0, 0) = 1.3 * 1.234567;
  expected(1, 0) = 89.13 * 1.234567;
  expected(2, 0) = 1 * 1.234567;
  expected(0, 1) = 9.1 * 1.234567;
  expected(1, 1) = 7 * 1.234567;
  expected(2, 1) = 1389 * 1.234567;
  expected(0, 2) = 8.123 * 1.234567;
  expected(1, 2) = 0 * 1.234567;
  expected(2, 2) = 0.0004 * 1.234567;
  ASSERT_EQ(source.EqMatrix(expected), true);
}

TEST(Overload, MulMatCut) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 3;
  source1(0, 1) = 27;
  source1(0, 2) = 18;
  source1(1, 0) = 0;
  source1(1, 1) = 18;
  source1(1, 2) = 15;
  source1(2, 0) = 24;
  source1(2, 1) = 9;
  source1(2, 2) = 9;

  source2(0, 0) = 3;
  source2(0, 1) = 18;
  source2(0, 2) = 24;
  source2(1, 0) = 21;
  source2(1, 1) = 15;
  source2(1, 2) = 24;
  source2(2, 0) = 0;
  source2(2, 1) = 27;
  source2(2, 2) = 3;

  expected(0, 0) = 576;
  expected(0, 1) = 945;
  expected(0, 2) = 774;
  expected(1, 0) = 378;
  expected(1, 1) = 675;
  expected(1, 2) = 477;
  expected(2, 0) = 261;
  expected(2, 1) = 810;
  expected(2, 2) = 819;

  source1 *= source2;
  ASSERT_EQ(source1.EqMatrix(expected), true);
}

TEST(Overload, Equity) {
  S21Matrix a(5, 5), b(5, 5);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      a(i, j) = b(i, j) = i + j;
    }
  }
  ASSERT_EQ(a == b, true);
  ASSERT_EQ(b == a, true);
}

TEST(Overload, Constant) {
  int size = 5;
  S21Matrix a(size, size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      a(i, j) = i + j;
    }
  }
  S21Matrix b = a;
  ASSERT_DOUBLE_EQ(a(1, 1), b(1, 1));
}

TEST(SumMatrix, 1dMatrix) {
  S21Matrix source1, source2, expected;
  source1(0, 0) = 352.412;
  source2(0, 0) = 1234.8234;
  source1.SumMatrix(source2);
  expected(0, 0) = 352.412 + 1234.8234;
  ASSERT_EQ(source1.EqMatrix(expected), true);
}

TEST(SumMatrix, 3dMatrix) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  source1.SumMatrix(source2);
  expected(0, 0) = 352.412 + 352.412;
  expected(1, 0) = 1 + 1;
  expected(2, 0) = 1;
  expected(0, 1) = -1234.8234 + 1234.8234;
  expected(1, 1) = 0.00001 + 0.00001;
  expected(2, 1) = 352.412 + 123456789;
  expected(0, 2) = -0.00001 + 1234.8234;
  expected(1, 2) = 352.412 + 0.412;
  expected(2, 2) = 9 + 9;
  ASSERT_EQ(source1.EqMatrix(expected), true);
}

TEST(SubMatrix, 1dMatrix) {
  S21Matrix source1, source2, expected;
  source1(0, 0) = 352.412;
  source2(0, 0) = 1234.8234;
  source1.SubMatrix(source2);
  expected(0, 0) = 352.412 - 1234.8234;
  ASSERT_EQ(source1.EqMatrix(expected), true);
}

TEST(SubMatrix, 3dMatrix) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 352.412;
  source1(1, 0) = 1;
  source1(2, 0) = 1;
  source1(0, 1) = 1234.8234;
  source1(1, 1) = 0.00001;
  source1(2, 1) = 352.412;
  source1(0, 2) = 1234.8234;
  source1(1, 2) = 352.412;
  source1(2, 2) = 9;

  source2(0, 0) = 352.412;
  source2(1, 0) = 1;
  source2(2, 0) = 0;
  source2(0, 1) = -1234.8234;
  source2(1, 1) = 0.00001;
  source2(2, 1) = 123456789;
  source2(0, 2) = -0.00001;
  source2(1, 2) = 0.412;
  source2(2, 2) = 9;
  source1.SubMatrix(source2);
  expected(0, 0) = 352.412 - 352.412;
  expected(1, 0) = 0;
  expected(2, 0) = 1;
  expected(0, 1) = 1234.8234 - -1234.8234;
  expected(1, 1) = 0.00001 - 0.00001;
  expected(2, 1) = 352.412 - 123456789;
  expected(0, 2) = 1234.8234 - -0.00001;
  expected(1, 2) = 352.412 - 0.412;
  expected(2, 2) = 0;
  ASSERT_EQ(source1.EqMatrix(expected), true);
}

TEST(SumMatrix, Uninitialized) {
  S21Matrix source1, source2;
  ASSERT_EQ(source1.EqMatrix(source2), true);
}

TEST(SubMatrix, Uninitialized) {
  S21Matrix source1, source2;
  ASSERT_EQ(source1.EqMatrix(source2), true);
}

TEST(MulMatrix, 3dMatrices) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 1;
  source1(0, 1) = 1;
  source1(0, 2) = 2;
  source1(1, 0) = 2;
  source1(1, 1) = 4;
  source1(1, 2) = 5;
  source1(2, 0) = 12;
  source1(2, 1) = 13;
  source1(2, 2) = 14;

  source2(0, 0) = 1;
  source2(0, 1) = -4;
  source2(0, 2) = -4;
  source2(1, 0) = -7;
  source2(1, 1) = -7;
  source2(1, 2) = -16;
  source2(2, 0) = -16;
  source2(2, 1) = -17;
  source2(2, 2) = -17;

  expected(0, 0) = -38;
  expected(0, 1) = -45;
  expected(0, 2) = -54;
  expected(1, 0) = -106;
  expected(1, 1) = -121;
  expected(1, 2) = -157;
  expected(2, 0) = -303;
  expected(2, 1) = -377;
  expected(2, 2) = -494;

  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(MulMatrix, DifferentDimension) {
  S21Matrix source1(3, 3), source2(3, 1), expected(3, 1);
  source1(0, 0) = 5;
  source1(0, 1) = 8;
  source1(0, 2) = -4;
  source1(1, 0) = 6;
  source1(1, 1) = 9;
  source1(1, 2) = -5;
  source1(2, 0) = 4;
  source1(2, 1) = 7;
  source1(2, 2) = -2;

  source2(0, 0) = 2;
  source2(1, 0) = -3;
  source2(2, 0) = 1;

  expected(0, 0) = -18;
  expected(1, 0) = -20;
  expected(2, 0) = -15;

  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), true);
}

TEST(MulMatrix, BigMatrices) {
  S21Matrix source1(2, 4), source2(4, 6), expected(2, 6);
  source1(0, 0) = 9;
  source1(0, 1) = 9;
  source1(0, 2) = 2;
  source1(0, 3) = 8;
  source1(1, 0) = 6;
  source1(1, 1) = 7;
  source1(1, 2) = 8;
  source1(1, 3) = 5;

  source2(0, 0) = 2;
  source2(0, 1) = 5;
  source2(0, 2) = 6;
  source2(0, 3) = 8;
  source2(0, 4) = 5;
  source2(0, 5) = 1;
  source2(1, 0) = 0;
  source2(1, 1) = 7;
  source2(1, 2) = 6;
  source2(1, 3) = 4;
  source2(1, 4) = 8;
  source2(1, 5) = 9;
  source2(2, 0) = 0;
  source2(2, 1) = 7;
  source2(2, 2) = 1;
  source2(2, 3) = 6;
  source2(2, 4) = 2;
  source2(2, 5) = 7;
  source2(3, 0) = 1;
  source2(3, 1) = 4;
  source2(3, 2) = 8;
  source2(3, 3) = 4;
  source2(3, 4) = 0;
  source2(3, 5) = 6;

  expected(0, 0) = 26;
  expected(0, 1) = 154;
  expected(0, 2) = 174;
  expected(0, 3) = 152;
  expected(0, 4) = 121;
  expected(0, 5) = 152;
  expected(1, 0) = 17;
  expected(1, 1) = 155;
  expected(1, 2) = 126;
  expected(1, 3) = 144;
  expected(1, 4) = 102;
  expected(1, 5) = 155;

  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), true);
}

TEST(MulMatrix, 3dMatrices2) {
  S21Matrix source1(3, 3), source2(3, 3), expected(3, 3);
  source1(0, 0) = 3;
  source1(0, 1) = 27;
  source1(0, 2) = 18;
  source1(1, 0) = 0;
  source1(1, 1) = 18;
  source1(1, 2) = 15;
  source1(2, 0) = 24;
  source1(2, 1) = 9;
  source1(2, 2) = 9;

  source2(0, 0) = 3;
  source2(0, 1) = 18;
  source2(0, 2) = 24;
  source2(1, 0) = 21;
  source2(1, 1) = 15;
  source2(1, 2) = 24;
  source2(2, 0) = 0;
  source2(2, 1) = 27;
  source2(2, 2) = 3;

  expected(0, 0) = 576;
  expected(0, 1) = 945;
  expected(0, 2) = 774;
  expected(1, 0) = 378;
  expected(1, 1) = 675;
  expected(1, 2) = 477;
  expected(2, 0) = 261;
  expected(2, 1) = 810;
  expected(2, 2) = 819;

  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(MulMatrix, EmptyMatrices) {
  S21Matrix source1(19, 9), source2(9, 14), expected(19, 14);
  source1.MulMatrix(source2);
  ASSERT_EQ(source1.EqMatrix(expected), 1);
}

TEST(Transpose, 1dMatrix) {
  S21Matrix source, expected;
  source(0, 0) = 123;
  expected(0, 0) = 123;
  S21Matrix result = source.Transpose();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Transpose, 3dMatrix) {
  S21Matrix source(3, 3), expected(3, 3);
  source(0, 0) = 352.412;
  source(1, 0) = 1;
  source(2, 0) = 1;
  source(0, 1) = 1234.8234;
  source(1, 1) = 0.00001;
  source(2, 1) = 352.412;
  source(0, 2) = 1234.8234;
  source(1, 2) = 352.412;
  source(2, 2) = 9;
  expected(0, 0) = 352.412;
  expected(0, 1) = 1;
  expected(0, 2) = 1;
  expected(1, 0) = 1234.8234;
  expected(1, 1) = 0.00001;
  expected(1, 2) = 352.412;
  expected(2, 0) = 1234.8234;
  expected(2, 1) = 352.412;
  expected(2, 2) = 9;
  S21Matrix result = source.Transpose();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(Transpose, 3x4Matrix) {
  S21Matrix source(3, 4), expected(4, 3);
  source(0, 0) = 352.412;
  source(1, 0) = 1;
  source(2, 0) = 1;
  source(0, 1) = 1234.8234;
  source(1, 1) = 0.00001;
  source(2, 1) = 352.412;
  source(0, 2) = 1234.8234;
  source(1, 2) = 352.412;
  source(2, 2) = 9;
  source(0, 3) = 13;
  source(1, 3) = 32.42;
  source(2, 3) = 0.9;
  expected(0, 0) = 352.412;
  expected(0, 1) = 1;
  expected(0, 2) = 1;
  expected(1, 0) = 1234.8234;
  expected(1, 1) = 0.00001;
  expected(1, 2) = 352.412;
  expected(2, 0) = 1234.8234;
  expected(2, 1) = 352.412;
  expected(2, 2) = 9;
  expected(3, 0) = 13;
  expected(3, 1) = 32.42;
  expected(3, 2) = 0.9;
  ASSERT_EQ(source.Transpose().EqMatrix(expected), true);
}

TEST(Transpose, 4x3Matrix) {
  S21Matrix source(4, 3), expected(3, 4);
  source(0, 0) = 352.412;
  source(1, 0) = 1;
  source(2, 0) = 1;
  source(3, 0) = 1234.8234;
  source(0, 1) = 0.00001;
  source(1, 1) = 352.412;
  source(2, 1) = 1234.8234;
  source(3, 1) = 352.412;
  source(0, 2) = 9;
  source(1, 2) = 13;
  source(2, 2) = 32.42;
  source(3, 2) = 0.9;
  expected(0, 0) = 352.412;
  expected(0, 1) = 1;
  expected(0, 2) = 1;
  expected(0, 3) = 1234.8234;
  expected(1, 0) = 0.00001;
  expected(1, 1) = 352.412;
  expected(1, 2) = 1234.8234;
  expected(1, 3) = 352.412;
  expected(2, 0) = 9;
  expected(2, 1) = 13;
  expected(2, 2) = 32.42;
  expected(2, 3) = 0.9;
  ASSERT_EQ(source.Transpose().EqMatrix(expected), 1);
}

TEST(Complements, SizeError) {
  S21Matrix source(2, 1);
  EXPECT_THROW(source.CalcComplements(), std::invalid_argument);
}

TEST(Determinant, WrongSize) {
  S21Matrix source(3, 9);
  EXPECT_THROW(source.Determinant(), std::invalid_argument);
}

TEST(InverseMatrix, Uninitialized) {
  S21Matrix source;
  EXPECT_THROW(source.InverseMatrix(), std::logic_error);
}

TEST(InverseMatrix, AllZero) {
  S21Matrix source(4, 4);
  EXPECT_THROW(source.InverseMatrix(), std::logic_error);
}

TEST(InverseMatrix, WrongSize) {
  S21Matrix source(10, 9);
  EXPECT_THROW(source.InverseMatrix(), std::invalid_argument);
}

TEST(MulMatrix, Size_error) {
  S21Matrix source1(2, 2), source2(5, 5);
  EXPECT_THROW(source1.MulMatrix(source2), std::invalid_argument);
}

TEST(Index, OutOfRange) {
  S21Matrix source1(3, 3);
  EXPECT_THROW(source1(12, 4), std::invalid_argument);
}

TEST(Seter, LessThanRows) {
  S21Matrix source;
  EXPECT_THROW(source.SetRows(-3), std::invalid_argument);
}

TEST(Seter, LessThanCols) {
  S21Matrix source;
  EXPECT_THROW(source.SetColumns(-3), std::invalid_argument);
}

TEST(Constructors, WrongIndex) {
  EXPECT_THROW(S21Matrix source(-1, -1), std::bad_alloc);
}

TEST(Overload, WrongIndex) {
  const S21Matrix a(9, 9);
  S21Matrix b;
  b = a;
  EXPECT_EQ(b.EqMatrix(a), true);
}

TEST(SumMatrix, DiffSize) {
  S21Matrix source1(3, 2), source2(2, 3);
  EXPECT_THROW(source1.SumMatrix(source2), std::invalid_argument);
  EXPECT_THROW(source2.SumMatrix(source1), std::invalid_argument);
}

TEST(SubMatrix, DiffSize) {
  S21Matrix source1(3, 2), source2(2, 3);
  EXPECT_THROW(source1.SubMatrix(source2), std::invalid_argument);
  EXPECT_THROW(source2.SubMatrix(source1), std::invalid_argument);
}

TEST(Inverse, Uncorrect) {
  S21Matrix source1(3, 2);
  EXPECT_THROW(source1.InverseMatrix(), std::invalid_argument);
}

TEST(Inverse, Uncorrect_1) {
  S21Matrix source1(3, 12);
  EXPECT_THROW(source1.InverseMatrix(), std::invalid_argument);
}

TEST(Constructors, Move) {
  S21Matrix source(3, 3);
  source(0, 0) = 99;
  source(2, 2) = -99;
  source(1, 1) = 13;
  S21Matrix moved_matrix(std::move(source));
  ASSERT_EQ(moved_matrix(0, 0), 99);
  ASSERT_EQ(moved_matrix(1, 1), 13);
  ASSERT_EQ(moved_matrix(2, 2), -99);
}

TEST(InverseMatrix, BigMatrix) {
  int size = 8;
  S21Matrix source(size, size), expected(size, size);
  source(0, 0) = 2;
  source(0, 1) = 8;
  source(0, 2) = 7;
  source(0, 3) = 4;
  source(0, 4) = 1;
  source(0, 5) = 8;
  source(0, 6) = 3;
  source(0, 7) = 9;
  source(1, 0) = 4;
  source(1, 1) = 2;
  source(1, 2) = 6;
  source(1, 3) = 2;
  source(1, 4) = 2;
  source(1, 5) = 1;
  source(1, 6) = 5;
  source(1, 7) = 8;
  source(2, 0) = 8;
  source(2, 1) = 6;
  source(2, 2) = 7;
  source(2, 3) = 7;
  source(2, 4) = 3;
  source(2, 5) = 4;
  source(2, 6) = 4;
  source(2, 7) = 1;
  source(3, 0) = 1;
  source(3, 1) = 7;
  source(3, 2) = 0;
  source(3, 3) = 4;
  source(3, 4) = 4;
  source(3, 5) = 3;
  source(3, 6) = 0;
  source(3, 7) = 5;
  source(4, 0) = 5;
  source(4, 1) = 7;
  source(4, 2) = 5;
  source(4, 3) = 6;
  source(4, 4) = 8;
  source(4, 5) = 3;
  source(4, 6) = 1;
  source(4, 7) = 9;
  source(5, 0) = 3;
  source(5, 1) = 7;
  source(5, 2) = 8;
  source(5, 3) = 0;
  source(5, 4) = 5;
  source(5, 5) = 7;
  source(5, 6) = 0;
  source(5, 7) = 2;
  source(6, 0) = 5;
  source(6, 1) = 8;
  source(6, 2) = 3;
  source(6, 3) = 5;
  source(6, 4) = 9;
  source(6, 5) = 1;
  source(6, 6) = 2;
  source(6, 7) = 0;
  source(7, 0) = 7;
  source(7, 1) = 8;
  source(7, 2) = 7;
  source(7, 3) = 4;
  source(7, 4) = 7;
  source(7, 5) = 9;
  source(7, 6) = 1;
  source(7, 7) = 5;

  expected(0, 0) = -0.5349902183;
  expected(0, 1) = 0.2894503762;
  expected(0, 2) = 0.2648128502;
  expected(0, 3) = 0.6295578936;
  expected(0, 4) = -0.1684575429;
  expected(0, 5) = 0.2471263249;
  expected(0, 6) = -0.3773947292;
  expected(0, 7) = 0.0217143747;
  expected(1, 0) = -0.3358379646;
  expected(1, 1) = 0.2037511071;
  expected(1, 2) = 0.2032547229;
  expected(1, 3) = 0.6234293334;
  expected(1, 4) = -0.1799149334;
  expected(1, 5) = 0.3295114996;
  expected(1, 6) = -0.2254070837;
  expected(1, 7) = -0.1935314328;
  expected(2, 0) = 0.09452225456;
  expected(2, 1) = -0.09221066155;
  expected(2, 2) = 0.03813722914;
  expected(2, 3) = -0.2190871073;
  expected(2, 4) = 0.1695573745;
  expected(2, 5) = 0.1092580516;
  expected(2, 6) = 0.007715043036;
  expected(2, 7) = -0.1600498331;
  expected(3, 0) = 0.3630563639;
  expected(3, 1) = -0.3052665388;
  expected(3, 2) = -0.04656927155;
  expected(3, 3) = -0.4771776828;
  expected(3, 4) = 0.2389343637;
  expected(3, 5) = -0.2685487089;
  expected(3, 6) = 0.1928760759;
  expected(3, 7) = -0.001245826966;
  expected(4, 0) = 0.2619837848;
  expected(4, 1) = -0.133556544;
  expected(4, 2) = -0.2495968906;
  expected(4, 3) = -0.4562289726;
  expected(4, 4) = 0.1044612934;
  expected(4, 5) = -0.2245895097;
  expected(4, 6) = 0.3128420752;
  expected(4, 7) = 0.1500734843;
  expected(5, 0) = 0.2992174649;
  expected(5, 1) = -0.1560300945;
  expected(5, 2) = -0.1850280149;
  expected(5, 3) = -0.3646314915;
  expected(5, 4) = -0.02339656554;
  expected(5, 5) = -0.2701059926;
  expected(5, 6) = 0.1915783395;
  expected(5, 7) = 0.2628500238;
  expected(6, 0) = 0.3028673486;
  expected(6, 1) = 0.0418714657;
  expected(6, 2) = -0.2001336669;
  expected(6, 3) = -0.3106910771;
  expected(6, 4) = -0.1692459178;
  expected(6, 5) = -0.2826713255;
  expected(6, 6) = 0.3477738954;
  expected(6, 7) = 0.1562734201;
  expected(7, 0) = -0.1023914038;
  expected(7, 1) = 0.1015348978;
  expected(7, 2) = 0.0104305565;
  expected(7, 3) = 0.1667915738;
  expected(7, 4) = 0.02489382894;
  expected(7, 5) = 0.04583280613;
  expected(7, 6) = -0.1284726616;
  expected(7, 7) = -0.01017100922;

  S21Matrix result = source.InverseMatrix();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(InverseMatrix, 3dMatrix) {
  int size = 3;
  S21Matrix source(size, size), expected(size, size);
  source(0, 0) = 3;
  source(0, 1) = 27;
  source(0, 2) = 18;
  source(1, 0) = 0;
  source(1, 1) = 18;
  source(1, 2) = 15;
  source(2, 0) = 24;
  source(2, 1) = 9;
  source(2, 2) = 9;

  expected(0, 0) = 0.01333333333;
  expected(0, 1) = -0.04;
  expected(0, 2) = 0.04;
  expected(1, 0) = 0.1777777778;
  expected(1, 1) = -0.2;
  expected(1, 2) = -0.02222222222;
  expected(2, 0) = -0.2133333333;
  expected(2, 1) = 0.3066666667;
  expected(2, 2) = 0.02666666667;

  S21Matrix result = source.InverseMatrix();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(InverseMatrix, 3dMatrix2) {
  int size = 3;
  S21Matrix source(size, size), expected(size, size);
  source(0, 0) = 4;
  source(0, 1) = 6;
  source(0, 2) = 8;
  source(1, 0) = 9;
  source(1, 1) = 2;
  source(1, 2) = 7;
  source(2, 0) = 9;
  source(2, 1) = 1;
  source(2, 2) = 0;

  expected(0, 0) = -0.02517985612;
  expected(0, 1) = 0.02877697842;
  expected(0, 2) = 0.09352517986;
  expected(1, 0) = 0.226618705;
  expected(1, 1) = -0.2589928058;
  expected(1, 2) = 0.1582733813;
  expected(2, 0) = -0.03237410072;
  expected(2, 1) = 0.1798561151;
  expected(2, 2) = -0.1654676259;

  S21Matrix result = source.InverseMatrix();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

TEST(InverseMatrix, 8dMatrix) {
  int size = 8;
  S21Matrix source(size, size), expected(size, size);
  source(0, 0) = 2;
  source(0, 1) = 8;
  source(0, 2) = 7;
  source(0, 3) = 4;
  source(0, 4) = 1;
  source(0, 5) = 8;
  source(0, 6) = 3;
  source(0, 7) = 9;
  source(1, 0) = 4;
  source(1, 1) = 2;
  source(1, 2) = 6;
  source(1, 3) = 2;
  source(1, 4) = 2;
  source(1, 5) = 1;
  source(1, 6) = 5;
  source(1, 7) = 8;
  source(2, 0) = 8;
  source(2, 1) = 6;
  source(2, 2) = 7;
  source(2, 3) = 7;
  source(2, 4) = 3;
  source(2, 5) = 4;
  source(2, 6) = 4;
  source(2, 7) = 1;
  source(3, 0) = 1;
  source(3, 1) = 7;
  source(3, 2) = 0;
  source(3, 3) = 4;
  source(3, 4) = 4;
  source(3, 5) = 3;
  source(3, 6) = 0;
  source(3, 7) = 5;
  source(4, 0) = 5;
  source(4, 1) = 7;
  source(4, 2) = 5;
  source(4, 3) = 6;
  source(4, 4) = 8;
  source(4, 5) = 3;
  source(4, 6) = 1;
  source(4, 7) = 9;
  source(5, 0) = 3;
  source(5, 1) = 7;
  source(5, 2) = 8;
  source(5, 3) = 0;
  source(5, 4) = 5;
  source(5, 5) = 7;
  source(5, 6) = 0;
  source(5, 7) = 2;
  source(6, 0) = 5;
  source(6, 1) = 8;
  source(6, 2) = 3;
  source(6, 3) = 5;
  source(6, 4) = 9;
  source(6, 5) = 1;
  source(6, 6) = 2;
  source(6, 7) = 0;
  source(7, 0) = 7;
  source(7, 1) = 8;
  source(7, 2) = 7;
  source(7, 3) = 4;
  source(7, 4) = 7;
  source(7, 5) = 9;
  source(7, 6) = 1;
  source(7, 7) = 5;

  expected(0, 0) = -0.5349902183;
  expected(0, 1) = 0.2894503762;
  expected(0, 2) = 0.2648128502;
  expected(0, 3) = 0.6295578936;
  expected(0, 4) = -0.1684575429;
  expected(0, 5) = 0.2471263249;
  expected(0, 6) = -0.3773947292;
  expected(0, 7) = 0.0217143747;
  expected(1, 0) = -0.3358379646;
  expected(1, 1) = 0.2037511071;
  expected(1, 2) = 0.2032547229;
  expected(1, 3) = 0.6234293334;
  expected(1, 4) = -0.1799149334;
  expected(1, 5) = 0.3295114996;
  expected(1, 6) = -0.2254070837;
  expected(1, 7) = -0.1935314328;
  expected(2, 0) = 0.09452225456;
  expected(2, 1) = -0.09221066155;
  expected(2, 2) = 0.03813722914;
  expected(2, 3) = -0.2190871073;
  expected(2, 4) = 0.1695573745;
  expected(2, 5) = 0.1092580516;
  expected(2, 6) = 0.007715043036;
  expected(2, 7) = -0.1600498331;
  expected(3, 0) = 0.3630563639;
  expected(3, 1) = -0.3052665388;
  expected(3, 2) = -0.04656927155;
  expected(3, 3) = -0.4771776828;
  expected(3, 4) = 0.2389343637;
  expected(3, 5) = -0.2685487089;
  expected(3, 6) = 0.1928760759;
  expected(3, 7) = -0.001245826966;
  expected(4, 0) = 0.2619837848;
  expected(4, 1) = -0.133556544;
  expected(4, 2) = -0.2495968906;
  expected(4, 3) = -0.4562289726;
  expected(4, 4) = 0.1044612934;
  expected(4, 5) = -0.2245895097;
  expected(4, 6) = 0.3128420752;
  expected(4, 7) = 0.1500734843;
  expected(5, 0) = 0.2992174649;
  expected(5, 1) = -0.1560300945;
  expected(5, 2) = -0.1850280149;
  expected(5, 3) = -0.3646314915;
  expected(5, 4) = -0.02339656554;
  expected(5, 5) = -0.2701059926;
  expected(5, 6) = 0.1915783395;
  expected(5, 7) = 0.2628500238;
  expected(6, 0) = 0.3028673486;
  expected(6, 1) = 0.0418714657;
  expected(6, 2) = -0.2001336669;
  expected(6, 3) = -0.3106910771;
  expected(6, 4) = -0.1692459178;
  expected(6, 5) = -0.2826713255;
  expected(6, 6) = 0.3477738954;
  expected(6, 7) = 0.1562734201;
  expected(7, 0) = -0.1023914038;
  expected(7, 1) = 0.1015348978;
  expected(7, 2) = 0.0104305565;
  expected(7, 3) = 0.1667915738;
  expected(7, 4) = 0.02489382894;
  expected(7, 5) = 0.04583280613;
  expected(7, 6) = -0.1284726616;
  expected(7, 7) = -0.01017100922;

  S21Matrix result = source.InverseMatrix();
  ASSERT_EQ(result.EqMatrix(expected), 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}