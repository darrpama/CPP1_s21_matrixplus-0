#include "s21_matrix.h"

void S21Matrix::allocateMemory (const int rows, const int cols) {
  this->matrix_ = new double *[rows];
  for (int i = 0; i < cols; i++) {
    this->matrix_[i] = new double[cols];
  }
};

void S21Matrix::freeMemory() {
  for (int i = 0; i < rows_; i++) {
    delete [] matrix_[i];
  }
  delete matrix_;
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
};

S21Matrix::S21Matrix() {                          //  Constr
  this->rows_ = 2;
  this->cols_ = 2;
  this->matrix_ = new double *[rows_];
  allocateMemory(this->rows_, this->cols_);
};

S21Matrix::S21Matrix(int rows, int cols) {        //  Constr
  if (rows_ <= 0 || cols_ <= 0) {
    throw std::invalid_argument("Incorrect size of matrix, each should be > 0");
  }
  this->rows_ = rows;
  this->cols_ = cols;
  allocateMemory(this->rows_, this->cols_);
};

S21Matrix::S21Matrix(const S21Matrix& other) {    //  Copy
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
};

S21Matrix::S21Matrix(S21Matrix&& other)           //  Moving
  : matrix_(nullptr)
  , cols_(0)
  , rows_(0) {
  matrix_ = other.matrix_;
  rows_ = other.rows_;
  cols_ = other.cols_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
};

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    freeMemory();
  }
};

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  bool answer = true;
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    answer = false;
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
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

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Size of summing matrix should be equal");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
};

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Size of summing matrix should be equal");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
};

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
};

void S21Matrix::MulMatrix(const S21Matrix& other) {};

S21Matrix S21Matrix::Transpose() {
  return S21Matrix();
};

S21Matrix S21Matrix::CalcComplements() {
  return S21Matrix();
};

double S21Matrix::Determinant() {
  return 1.0;
};

S21Matrix S21Matrix::InverseMatrix() {
  return S21Matrix();
};

S21Matrix S21Matrix::operator + (const S21Matrix &other) {
  return S21Matrix();
};

S21Matrix S21Matrix::operator - (const S21Matrix &other) {
  return S21Matrix();
};

S21Matrix S21Matrix::operator * (const S21Matrix &other) {
  return S21Matrix();
};

bool S21Matrix::operator == (const S21Matrix &other) {
  return true;
};

bool S21Matrix::operator != (const S21Matrix &other) {
  return true;
};

S21Matrix S21Matrix::operator += (const S21Matrix &other) {
  return S21Matrix();
};

S21Matrix S21Matrix::operator -= (const S21Matrix &other) {
  return S21Matrix();
};

S21Matrix S21Matrix::operator *= (const S21Matrix &other) {
  return S21Matrix();
};

double& S21Matrix::operator () (int row, int col) {
  return this->matrix_[row][col];
};

int S21Matrix::GetRows() {
  return this->rows_;
}

int S21Matrix::GetCols() {
  return this->cols_;
}

// void S21Matrix::SetRows(int rows) {
//   if (rows <= 0) {
//     throw std::invalid_argument("Incorrect size of rows, it should be > 0");
//   }
//   S21Matrix newMatrix(*this);
// }
//
// void S21Matrix::SetCols(int rows) {
//   if (rows <= 0) {
//     throw std::invalid_argument("Incorrect size of cols, it should be > 0");
//   }
// }

void S21Matrix::FillMatrix(double value) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = value;
    }
  }
}

int main(void) {
  return 0;
}
