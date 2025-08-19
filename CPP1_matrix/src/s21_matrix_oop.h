#ifndef S21_MATRIX_OOP
#define S21_MATRIX_OOP
#include <cmath>
#include <iostream>

#define EPS 1e-7

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double **matrix_;  // Pointer to the memory where the matrix is allocated
  void CreateMatrix();
  void RemoveMatrix();
  void CopyMatrix(const S21Matrix &other);  // Copy
  void MoveMatrix(S21Matrix &other);        // Replacement
  void NullMatrix();
  int EqualMatrix(const S21Matrix &other);

 public:
  S21Matrix();                        // Default constructor
  ~S21Matrix();                       // Destructor
  S21Matrix(int rows, int cols);      // Constructor
  S21Matrix(const S21Matrix &other);  // Copy constructor
  S21Matrix(S21Matrix &&other);       // Replace constructor
  // MAIN FUNCTIONS
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);        // умножение на число
  void MulMatrix(const S21Matrix &other);  // умножение матриц
  S21Matrix Transpose();
  S21Matrix CalcComplements();  // Вычисляет матрицу алгебраических дополнений
                                // текущей матрицы и возвращает ее
  S21Matrix Submatrix(int row, int col);
  double Determinant();  // Вычисляет и возвращает определитель текущей матрицы
  S21Matrix InverseMatrix();  // Вычисляет и возвращает обратную матрицу
                              // OPERATOR
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator=(const S21Matrix &other);
  S21Matrix operator=(S21Matrix &&other);
  bool operator==(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(double num);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double num);
  double &operator()(int rows, int columns);
  friend S21Matrix operator*(double num, S21Matrix &other);
  // GETTER/SETTER
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetColumns(int columns);
  // PRINT
  void PrintMatrix();
};
#endif