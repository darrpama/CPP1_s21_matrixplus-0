#include "s21_matrix.h"

S21Matrix::S21Matrix() {
  this->rows_ = 2;
  this->cols_ = 2;
  this->matrix_ = new double *[rows_];
  allocateMemory(this->rows_, this->cols_);
};

S21Matrix::S21Matrix(int rows, int cols) {
  this->rows_ = rows;
  this->cols_ = cols;
  allocateMemory(this->rows_, this->cols_);
};

//  Copy
S21Matrix::S21Matrix(const S21Matrix& other) {
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
};

//  Moving
S21Matrix::S21Matrix(S21Matrix&& other) {
};
  
S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    freeMemory();
  }
};

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  return true;
};

void S21Matrix::SumMatrix(const S21Matrix& other){};
void S21Matrix::SubMatrix(const S21Matrix& other){};
void S21Matrix::MulNumber(const S21Matrix& other){};
void S21Matrix::MulMatrix(const S21Matrix& other){};

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

void S21Matrix::allocateMemory(const int rows, const int cols) {
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

int main(void) {
  return 0;
}
