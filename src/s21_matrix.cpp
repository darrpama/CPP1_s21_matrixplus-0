#include <iostream>

class S21Matrix {
private:
  int rows_, cols_;
  double **matrix_;

public:
  S21Matrix() {

  };

  S21Matrix(int rows, int cols) {

  };

  S21Matrix(const S21Matrix& other) {

  };

  S21Matrix(S21Matrix&& other) {

  };
  
  ~S21Matrix() {

  };

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const S21Matrix& other);
  void MulMatrix(const S21Matrix& other);

  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator + (const S21Matrix &other);
  S21Matrix operator - (const S21Matrix &other);
  S21Matrix operator * (const S21Matrix &other);
  bool operator == (const S21Matrix &other);
  bool operator != (const S21Matrix &other);
  S21Matrix operator += (const S21Matrix &other);
  S21Matrix operator -= (const S21Matrix &other);
  S21Matrix operator *= (const S21Matrix &other);
  double & operator () (int rows, int cols);

};

int main(void) {
  return 0;
}
