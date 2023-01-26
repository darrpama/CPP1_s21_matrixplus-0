#include <iostream>
#include <stdexcept>
#include <math.h>

class S21Matrix {
private:
  int rows_, cols_;
  double **matrix_;
  void allocateMemory(const int rows, const int cols);
  void freeMemory();

public:
  S21Matrix();                              //  default constructor (make 2 x 2 matrix)

  S21Matrix(int rows, int cols);            //  variable constructor

  S21Matrix(const S21Matrix& other);        //  copy

  S21Matrix(S21Matrix&& other);             //  move
  
  ~S21Matrix();                             //  destructor

  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
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
  int GetRows();
  int GetCols();
  void FillMatrix(double value);
};
