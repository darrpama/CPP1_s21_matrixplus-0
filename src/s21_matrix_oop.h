#include <algorithm>
#include <iostream>
#include <math.h>
#include <stdexcept>

namespace S21 {
class S21Matrix {

public:
  S21Matrix(); //  default constructor (make 2 x 2 matrix)

  S21Matrix(int rows, int cols); //  variable constructor

  S21Matrix(const S21Matrix &other); //  copy

  S21Matrix(S21Matrix &&other) noexcept; //  move

  ~S21Matrix(); //  destructor

  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);

  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix &operator=(const S21Matrix &other);
  bool operator==(const S21Matrix &other);
  bool operator!=(const S21Matrix &other);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*=(const double &num);
  double &operator()(int row, int col);
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);
  void FillMatrix(double value);
  void PrintMatrix() const;

private:
  int rows_{}, cols_{};
  double **matrix_{};
  void AllocateMemory(const int rows, const int cols);
  void FreeMemory();
  double CalcMinor(int row, int col);
  void IsMatrixUninitialized();
  void IsMatrixUninitialized(const S21Matrix &other);
  void IsMatrixInitialized();
};
} // namespace S21
