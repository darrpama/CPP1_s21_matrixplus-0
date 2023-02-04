#include "s21_matrix.h"

void S21Matrix::allocateMemory (const int rows, const int cols) {
  this->matrix_ = new double *[rows]();           // new + () in the eol init data by 0
  for (int i = 0; i < cols; i++) {
    this->matrix_[i] = new double[cols]();
  }
};

void S21Matrix::freeMemory() {
  for (int i = 0; i < this->rows_; i++) {
    delete [] matrix_[i];
  }
  delete matrix_;
  this->rows_ = 0;
  this->cols_ = 0;
  this->matrix_ = nullptr;
};

S21Matrix::S21Matrix() {                          //  Constr
  this->rows_ = 2;
  this->cols_ = 2;
  allocateMemory(this->rows_, this->cols_);
};

S21Matrix::S21Matrix(int rows, int cols) {        //  Constr
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Incorrect size of matrix, each should be > 0");
  }
  this->rows_ = rows;
  this->cols_ = cols;
  allocateMemory(this->rows_, this->cols_);
};

S21Matrix::S21Matrix(const S21Matrix& other) {    //  Copy
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  allocateMemory(this->rows_, this->cols_);
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
};

S21Matrix::S21Matrix(S21Matrix&& other) {          //  Moving
  this->matrix_ = other.matrix_;
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  other.matrix_ = nullptr;
  other.rows_ = 0;
  other.cols_ = 0;
};

S21Matrix::~S21Matrix() {
  if (this->matrix_ != nullptr) {
    freeMemory();
  }
};

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (!this->matrix_ || !other.matrix_) {
    throw std::invalid_argument("Matrix's should be initialized");
  }
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

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!this->matrix_ || !other.matrix_) {
    throw std::invalid_argument("Matrix's should be initialized");
  }
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    throw std::invalid_argument("Size of summing matrix should be equal");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
};

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!this->matrix_ || !other.matrix_) {
    throw std::invalid_argument("Matrix's should be initialized");
  }
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
  if (!this->matrix_) {
    throw std::invalid_argument("Matrix should be initialized");
  }
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= num;
    }
  }
};

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (!this->matrix_ || !other.matrix_) {
    throw std::invalid_argument("Matrix's should be initialized");
  }
  if (this->cols_ != other.rows_) {
    throw std::invalid_argument("A * B; num cols of A should be equal num rows of B");
  }
  S21Matrix result(this->rows_, other.cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.cols_; k++) {
        result.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][i];
      }
    }
  }
  *this = result;
};

S21Matrix S21Matrix::Transpose() {
  if (!matrix_) {
    throw std::invalid_argument("Matrix should be initialized");
  }
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
  if (!matrix_) {
    throw std::invalid_argument("Matrix should be initialized");
  }
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix should be square");
  }
  if (this->Determinant() == 0) {
    throw std::invalid_argument("Determinant = 0");
  }
  S21Matrix complementsMatrix = this->Transpose();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
       complementsMatrix.matrix_[i][j] = calc_minor(i, j);
    }
  }
  return complementsMatrix;
};

double S21Matrix::Determinant() {
  if (!matrix_) {
    throw std::invalid_argument("Matrix should be initialized");
  }
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix should be square");
  }
  double determinant = 0.0;
  if (this->rows_ == 1) {
    determinant = this->matrix_[0][0];
  } else if (this->rows_ == 2) {
    determinant = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int i = 0; i < cols_; i++) {
      determinant += matrix_[0][i] * calc_minor(0, i) * pow(-1, i);
    }
  }
  return determinant;
};

S21Matrix S21Matrix::InverseMatrix() {
  if (!matrix_) {
    throw std::invalid_argument("Matrix should be initialized");
  }
  if (this->rows_ != this->cols_) {
    throw std::invalid_argument("Matrix should be sqare");
  }
  double determinant = this->Determinant();
  S21Matrix inverseMatrix = this->CalcComplements();
  inverseMatrix.MulNumber(1.0/determinant);
  return inverseMatrix;
};

S21Matrix S21Matrix::operator + (const S21Matrix &other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
};

S21Matrix S21Matrix::operator - (const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
};

S21Matrix S21Matrix::operator * (const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
};

S21Matrix& S21Matrix::operator = (const S21Matrix &other) {
  if (this != &other) {
    this->freeMemory();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    this->allocateMemory(this->rows_, this->cols_);
    for (int i = 0; i < this->cols_; i++) {
      for (int j = 0; j < this->rows_; j++) {
        this->matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
};

bool S21Matrix::operator == (const S21Matrix &other) {
  return EqMatrix(other);
};

bool S21Matrix::operator != (const S21Matrix &other) {
  return !EqMatrix(other);
};

S21Matrix S21Matrix::operator += (const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
};

S21Matrix S21Matrix::operator -= (const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
};

S21Matrix S21Matrix::operator *= (const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
};

double& S21Matrix::operator () (int row, int col) {
  if (!matrix_) {
    throw std::invalid_argument("Matrix should be initialized");
  }
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::invalid_argument("Incorrect index of matrix");
  }
  return this->matrix_[row][col];
};

double S21Matrix::calc_minor(int row, int col) {
  S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
  for (int i = 0; i < minor.GetRows(); i++) {
    for (int j = 0; j < minor.GetCols(); j++) {
      if (i != row || j != col) {
        minor.matrix_[i][j] = this->matrix_[i][j];
      }
    }
  }
  return minor.Determinant();
}

int S21Matrix::GetRows() {
  return this->rows_;
}

int S21Matrix::GetCols() {
  return this->cols_;
}

void S21Matrix::FillMatrix(double value) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = value;
    }
  }
}

