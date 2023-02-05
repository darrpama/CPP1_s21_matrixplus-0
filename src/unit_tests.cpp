#include <gtest/gtest.h>
#include <iostream>
#include "s21_matrix.h"

using namespace std;

TEST(Constructors, Default1) {
  S21Matrix matrix;
  EXPECT_EQ(2, matrix.GetRows());
  EXPECT_EQ(2, matrix.GetCols());
}

TEST(Constructors, Parameters1) {
  S21Matrix matrix1(5, 5);
  EXPECT_EQ(5, matrix1.GetRows());
  EXPECT_EQ(5, matrix1.GetCols());
  matrix1.PrintMatrix();

  EXPECT_NO_THROW(S21Matrix matrix2(10, 10));
  EXPECT_ANY_THROW(S21Matrix matrix3(0, 10));
  EXPECT_ANY_THROW(S21Matrix matrix4(10, 0));
  EXPECT_ANY_THROW(S21Matrix matrix5(-10, 10));
  EXPECT_ANY_THROW(S21Matrix matrix6(10, -10));
  EXPECT_ANY_THROW(S21Matrix matrix7(-0, 10));
  EXPECT_ANY_THROW(S21Matrix matrix8(10, -0));
}

TEST(Constructors, Parameters2) {
  S21Matrix matrix1(5, 7);
  matrix1.PrintMatrix();
  EXPECT_EQ(5, matrix1.GetRows());
  EXPECT_EQ(7, matrix1.GetCols());

  S21Matrix matrix2(7, 5);
  matrix2.PrintMatrix();
  EXPECT_EQ(7, matrix2.GetRows());
  EXPECT_EQ(5, matrix2.GetCols());
}

TEST(Constructors, Copy1) {
  S21Matrix matrix1(3, 3);
  matrix1.FillMatrix(5);
  S21Matrix matrix2(matrix1);
  EXPECT_EQ(matrix1.GetRows(), matrix2.GetRows());
  EXPECT_EQ(matrix1.GetCols(), matrix2.GetCols());
  for (int i = 0; i < matrix1.GetRows() - 1; i++) {
    for (int j = 0; j < matrix1.GetCols() - 1; j++) {
      EXPECT_EQ(matrix1.GetCols(), matrix2.GetCols());
    }
  }
}

TEST(Constructors, Initialization1) {
  double test[5][5] = {{0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0},
                       {0, 0, 0, 0}};
  S21Matrix matrix(4, 4);
  EXPECT_EQ(matrix.GetRows(), 4);
  EXPECT_EQ(matrix.GetCols(), 4);
  for (int i = 0; i < matrix.GetRows(); i++) {
    for (int j = 0; j < matrix.GetCols(); j++) {
      EXPECT_EQ(matrix(i, j), test[i][j]);
    }
  }
}

TEST(Constructors, Move1) {
  S21Matrix A(4, 4);
  A.FillMatrix(4);
  S21Matrix C(A);
  S21Matrix B = std::move(A);
  EXPECT_EQ(C.EqMatrix(B), true);
  EXPECT_EQ(C.GetRows(), B.GetRows());
  EXPECT_EQ(C.GetCols(), B.GetCols());
}

TEST(Methods, Eq1) {
  S21Matrix A(4, 4);
  A.FillMatrix(1);
  S21Matrix B = A;
  EXPECT_EQ(A.EqMatrix(B), true);
}

TEST(Methods, Sum1) {
  S21Matrix A(3, 3), B(3, 3);
  A.FillMatrix(1);
  B.FillMatrix(2);
  S21Matrix C(3, 3);
  C.FillMatrix(3);
  S21Matrix tmp1 = A + B;
  S21Matrix tmp2 = A;
  tmp2 += B;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

TEST(Methods, Sub1) {
  S21Matrix A(3, 3), B(3, 3);
  A.FillMatrix(1);
  B.FillMatrix(2);
  S21Matrix C(3, 3);
  C.FillMatrix(-1);
  S21Matrix tmp1 = A - B;
  S21Matrix tmp2 = A;
  tmp2 -= B;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

TEST(Methods, MulM1) {
  S21Matrix A(3, 3), B(3, 3);
  A.FillMatrix(1);
  B.FillMatrix(2);
  S21Matrix C(3, 3);
  C.FillMatrix(6);
  S21Matrix tmp1 = A * B;
  S21Matrix tmp2 = A;
  tmp2 *= B;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

TEST(Methods, MulM2) {
  S21Matrix A(3, 2), B(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 5;
  A(2, 1) = 6;
  B.FillMatrix(2);
  S21Matrix C(3, 3);
  C(0, 0) = 6;
  C(0, 1) = 6;
  C(0, 2) = 6;
  C(1, 0) = 14;
  C(1, 1) = 14;
  C(1, 2) = 14;
  C(2, 0) = 22;
  C(2, 1) = 22;
  C(2, 2) = 22;
  S21Matrix tmp1 = A * B;
  S21Matrix tmp2 = A;
  tmp2.PrintMatrix();
  tmp2 *= B;
  std::cout << "aboba" << std::endl;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
