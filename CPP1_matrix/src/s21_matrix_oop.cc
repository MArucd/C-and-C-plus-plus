#include "s21_matrix_oop.h"

// ------------------------------ constructor destructor
// ---------------------------------

S21Matrix::S21Matrix() : rows_(1), cols_(1) { CreateMatrix(); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  CreateMatrix();
  CopyMatrix(other);
}

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.NullMatrix();
}

void S21Matrix::NullMatrix() {
  matrix_ = nullptr;
  rows_ = 0;
  cols_ = 0;
}

S21Matrix::~S21Matrix() { RemoveMatrix(); }

//------------------------------ operators ---------------------------------

S21Matrix S21Matrix::operator=(const S21Matrix &other) {
  this->~S21Matrix();
  rows_ = other.rows_;
  cols_ = other.cols_;
  CreateMatrix();
  CopyMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator=(S21Matrix &&other) {
  if (this != &other) {
    this->~S21Matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    CreateMatrix();
    matrix_ = other.matrix_;
    other.NullMatrix();
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix temp(*this);
  temp.SumMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix temp(*this);
  temp.SubMatrix(other);
  return temp;
}

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); }

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix temp(*this);
  temp.MulMatrix(other);
  return temp;
}

S21Matrix S21Matrix::operator*(double num) {
  S21Matrix temp(*this);
  temp.MulNumber(num);
  return temp;
}

S21Matrix operator*(double num, S21Matrix &other) {
  S21Matrix resultMatrix(other);
  resultMatrix.MulNumber(num);
  return resultMatrix;
}

double &S21Matrix::operator()(int rows, int columns) {
  if (rows >= rows_ || columns >= cols_) {
    throw std::invalid_argument("\nIndex out of range\n");
  }
  return matrix_[rows][columns];
}

//------------------------------ methods ---------------------------------

// Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("\nThe matrix must be square\n");
  }

  S21Matrix comp(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix submatrix = Submatrix(i, j);
      double det = submatrix.Determinant();
      comp.matrix_[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * det;
    }
  }
  return comp;
}

S21Matrix S21Matrix::Submatrix(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Index outside the matrix");
  }

  S21Matrix sub(rows_ - 1, cols_ - 1);
  for (int i = 0, sub_i = 0; i < rows_; ++i) {
    if (i == row) continue;
    for (int j = 0, sub_j = 0; j < cols_; ++j) {
      if (j == col) continue;
      sub.matrix_[sub_i][sub_j] = matrix_[i][j];
      sub_j++;
    }
    sub_i++;
  }
  return sub;
}

// Вычисляет и возвращает определитель текущей матрицы
double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("nThe matrix must be square");
  } else if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("The matrix is not correct");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  } else if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }

  double det = 0.0;

  // Рекурсивное разложение на миноры
  for (int j = 0; j < cols_; ++j) {
    S21Matrix submatrix = Submatrix(0, j);  // Получаем подматрицу
    det += (j % 2 == 0 ? 1 : -1) * matrix_[0][j] * submatrix.Determinant();
  }

  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  S21Matrix temp(*this);
  double determ = temp.Determinant();
  if (temp.rows_ != temp.cols_) {
    throw std::invalid_argument("\nRows and columns must match\n");
  } else if (std::fabs(determ) < EPS) {
    throw std::logic_error("\nDeterminant value can't be equal to 0\n");
  }

  temp = temp.CalcComplements();
  temp = temp.Transpose();
  temp.MulNumber(1 / determ);

  return temp;
}

int S21Matrix::EqualMatrix(const S21Matrix &other) {
  return (other.cols_ == this->cols_) && (other.rows_ == this->rows_);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix Temp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      Temp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return Temp;
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument("\nWrong count of rows or columns\n");
  }
  S21Matrix Temp(rows_, other.cols_);

  // строки А (строки С)
  for (int i = 0; i < rows_; i++) {
    // столбцы B (столбцы С)
    for (int j = 0; j < other.cols_; j++) {
      // общий столбцы А == строки В
      for (int k = 0; k < other.rows_; k++) {
        Temp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  MoveMatrix(Temp);
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!EqualMatrix(other)) {
    throw std::invalid_argument("\nRows and columns do not match\n");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!EqualMatrix(other)) {
    throw std::invalid_argument("\nRows and columns do not match\n");
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::CopyMatrix(const S21Matrix &other) {
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::MoveMatrix(S21Matrix &other) {
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.matrix_ = nullptr;
}

void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::RemoveMatrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; i++) {
      if (matrix_[i]) delete[] matrix_[i];
    }
    delete[] matrix_;
  }
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows < 1) {
    throw std::invalid_argument("\nThere must be more than 1 rows\n");
  }
  S21Matrix tempM(rows, cols_);

  for (int i = 0; i < ((rows_ < rows) ? rows_ : rows); i++) {
    for (int j = 0; j < cols_; j++) {
      tempM.matrix_[i][j] = matrix_[i][j];
    }
  }

  *this = tempM;
}

void S21Matrix::SetColumns(int columns) {
  if (columns < 1) {
    throw std::invalid_argument("\nThere must be more than 1 columns\n");
  }
  S21Matrix tmpMatrix(rows_, columns);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < columns; ++j) {
      if (j >= cols_) {
        continue;
      } else {
        tmpMatrix.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  int rows = rows_;
  RemoveMatrix();
  rows_ = rows;
  cols_ = columns;
  CreateMatrix();
  CopyMatrix(tmpMatrix);
  tmpMatrix.~S21Matrix();
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
  bool result = true;
  if (matrix_ == nullptr || other.matrix_ == nullptr) {
    throw std::length_error("Matrix doesn't exist");
  }
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    result = false;
  }
  for (int i = 0; i < rows_ && result == true; i++) {
    for (int j = 0; j < cols_ && result == true; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        result = false;
      }
    }
  }
  return result;
}

void S21Matrix::PrintMatrix() {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << "\n";
  }
}