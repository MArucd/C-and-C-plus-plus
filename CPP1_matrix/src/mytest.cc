#include "s21_matrix_oop.h"
using namespace std;
int main() {
  S21Matrix M1(2, 3);
  S21Matrix M2(3, 2);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 3; j++) {
      M1.operator()(i, j) = pow(i * 3, 1) + 1 + j;
    }
  }
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 2; j++) {
      M2.operator()(i, j) = pow(i * 3, 1) + 1 + j;
    }
  }
  M1.MulMatrix(M2);
  int rows = 3;
  int columns = 4;
  S21Matrix sample(rows, columns);
  M1.PrintMatrix();
  M1.~S21Matrix();
  //   S21Matrix expect((const S21Matrix&) sample);
  //   cout << sample.EqMatrix(expect);
  // EXPECT_EQ(sample.EqMatrix(expect), true);
  return 0;
}