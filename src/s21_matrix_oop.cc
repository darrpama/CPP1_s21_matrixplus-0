#include "s21_matrix_oop.h"

using namespace S21;

void S21Matrix::AllocateMemory(const int rows, const int cols) {
  this->matrix_ = new double *[rows](); // new + () in the eol init data by 0
  for (int i = 0; i < rows; i++) {
    this->matrix_[i] = new double[cols]();
  }
};

void S21Matrix::FreeMemory() {
  IsMatrixUninitialized();
  for (int i = 0; i < this->rows_; i++) {
    delete[] matrix_[i];
  }
  delete matrix_;
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
};

void S21Matrix::IsMatrixUninitialized() {
  if (!this->matrix_) {
    throw std::invalid_argument("Matrix should be initialized");
  }
}

void S21Matrix::IsMatrixUninitialized(const S21Matrix &other) {
  if (!this->matrix_ || !other.matrix_) {
    throw std::invalid_argument("Matrices should be initialized");
  }
}

S21Matrix::S21Matrix() { //  Constr
  this->rows_ = 2;
  this->cols_ = 2;
  this->AllocateMemory(this->rows_, this->cols_);
};

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) { //  Constr
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Incorrect size of matrix, each should be > 0");
  }
  this->AllocateMemory(this->rows_, this->cols_);
};

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) { //  Copy
  AllocateMemory(this->rows_, this->cols_);
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
};

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
    : rows_(other.rows_), cols_(other.cols_),
      matrix_(other.matrix_) { //  Moving
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
};

S21Matrix::~S21Matrix() {
  if (matrix_) {
    this->FreeMemory();
  }
};

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  IsMatrixUninitialized(other);
  bool answer = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    answer = false;
  } else {
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < this->cols_; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) < 0.0000001) {
          continue;
        } else {
          i = rows_;
          j = cols_;
          answer = false;
          break;
        }
      }
    }
  }
  return answer;
};

void S21Matrix::SumMatrix(const S21Matrix &other) {
  IsMatrixUninitialized(other);
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Size of summing matrix should be equal");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
};

void S21Matrix::SubMatrix(const S21Matrix &other) {
  IsMatrixUninitialized(other);
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Size of summing matrix should be equal");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
};

void S21Matrix::MulNumber(const double num) {
  IsMatrixUninitialized();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
};

void S21Matrix::MulMatrix(const S21Matrix &other) {
  IsMatrixUninitialized(other);
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument(
        "A * B; num cols of A should be equal num rows of B");
  }
  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < this->cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
};

S21Matrix S21::S21Matrix::Transpose() {
  IsMatrixUninitialized();
  // construct new matrix with rows = cols_ and cols = rows_
  S21Matrix result(this->cols_, this->rows_);
  for (int i = 0; i < result.GetRows(); i++) {
    for (int j = 0; j < result.GetCols(); j++) {
      result.matrix_[i][j] = this->matrix_[j][i];
    }
  }
  return result;
};

S21Matrix S21Matrix::CalcComplements() {
  IsMatrixUninitialized();
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix should be square");
  }
  if (this->Determinant() == 0) {
    throw std::invalid_argument("Determinant = 0");
  }
  S21Matrix complementsMatrix = this->Transpose();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      complementsMatrix.matrix_[i][j] = CalcMinor(i, j) * pow(-1, i + j);
    }
  }
  return complementsMatrix;
};

double S21Matrix::Determinant() {
  IsMatrixUninitialized();
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix should be square");
  }
  double determinant = 0.0;
  if (this->rows_ == 1) {
    determinant = this->matrix_[0][0];
  } else if (this->rows_ == 2 || this->cols_ == 2) {
    determinant =
        (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]);
  } else {
    for (int i = 0; i < cols_; i++) {
      determinant += matrix_[0][i] * this->CalcMinor(0, i) * pow(-1, i);
    }
  }
  return determinant;
};

double S21Matrix::CalcMinor(int row, int col) {
  S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
  int g = 0;
  int k = 0;
  for (int i = 0; i < this->GetRows() - 1; i++) {
    if (i >= row) {
      g = 1;
    } else {
      g = 0;
    }
    for (int j = 0; j < this->GetCols() - 1; j++) {
      if (j >= col) {
        k = 1;
      } else {
        k = 0;
      }
      minor.matrix_[i][j] = this->matrix_[i + g][j + k];
    }
  }
  return minor.Determinant();
}

S21Matrix S21Matrix::InverseMatrix() {
  IsMatrixUninitialized();
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix should be sqare");
  }
  double determinant = this->Determinant();
  S21Matrix inverseMatrix = this->CalcComplements().Transpose();
  inverseMatrix.MulNumber(1.0 / determinant);
  return inverseMatrix;
};

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
};

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
};

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
};

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  IsMatrixUninitialized(other);
  this->FreeMemory();
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->AllocateMemory(other.rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
};

bool S21Matrix::operator==(const S21Matrix &other) { return EqMatrix(other); };

bool S21Matrix::operator!=(const S21Matrix &other) { return !EqMatrix(other); };

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
};

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
};

S21Matrix S21Matrix::operator*=(const double &num) {
  this->MulNumber(num);
  return *this;
};

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
};

double &S21Matrix::operator()(int row, int col) {
  IsMatrixUninitialized();
  if (row >= this->rows_ || col >= this->cols_ || row < 0 || col < 0) {
    throw std::invalid_argument("Incorrect index of matrix");
  }
  return this->matrix_[row][col];
};

int S21Matrix::GetRows() const { return this->rows_; }

int S21Matrix::GetCols() const { return this->cols_; }

void S21Matrix::SetRows(int rows) {
  IsMatrixUninitialized();
  if (rows < 0) {
    throw std::invalid_argument("Incorrect index of rows");
  }
  if (rows < this->rows_) {
    this->rows_ = rows;
  }
  S21Matrix result(rows, this->cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(i, j) = this->matrix_[i][j];
    }
  }
  *this = result;
}

void S21Matrix::SetCols(int cols) {
  IsMatrixUninitialized();
  if (cols < 0) {
    throw std::invalid_argument("Incorrect index of cols");
  }
  S21Matrix result(this->rows_, cols);
  if (cols < this->cols_) {
    this->cols_ = cols;
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result(i, j) = this->matrix_[i][j];
    }
  }
  *this = result;
}

void S21Matrix::FillMatrix(double value) {
  IsMatrixUninitialized();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = value;
    }
  }
}

void S21Matrix::PrintMatrix() const {
  for (int i = 0; i < this->GetRows(); i++) {
    for (int j = 0; j < this->GetCols(); j++) {
      std::cout << this->matrix_[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
