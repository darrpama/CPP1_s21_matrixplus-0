#include "s21_matrix.h"

S21Matrix::S21Matrix(int rows, int cols) {};

S21Matrix::S21Matrix(const S21Matrix& other) {};

S21Matrix::S21Matrix(S21Matrix&& other) {};
  
S21Matrix::~S21Matrix() {};

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

double& S21Matrix::operator () (int rows, int cols) {

};


int main(void) {
  return 0;
}
