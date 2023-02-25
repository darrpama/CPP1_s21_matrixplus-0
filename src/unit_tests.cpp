#include <gtest/gtest.h>
#include <iostream>
#include "s21_matrix_oop.h"

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

TEST(Methods, Eq2) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  A.FillMatrix(1);
  B.FillMatrix(2);
  EXPECT_EQ(A.EqMatrix(B), false);
}

TEST(Methods, Eq3) {
  S21Matrix A(4, 3);
  S21Matrix B(4, 4);
  A.FillMatrix(1);
  B.FillMatrix(1);
  EXPECT_EQ(A.EqMatrix(B), false);
}

TEST(Methods, NonEq1) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  A.FillMatrix(1);
  B.FillMatrix(2);
  EXPECT_EQ(A != B, true);
}

TEST(Methods, NonEq2) {
  S21Matrix A(4, 4);
  S21Matrix B(4, 4);
  A.FillMatrix(1);
  B.FillMatrix(1);
  EXPECT_EQ(A != B, false);
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

TEST(Methods, Sum2) {
  S21Matrix A(8, 3), B(8, 3);
  A.FillMatrix(1);
  B.FillMatrix(2);
  S21Matrix C(8, 3);
  C.FillMatrix(3);
  S21Matrix tmp1 = A + B;
  S21Matrix tmp2 = A;
  tmp2 += B;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

TEST(Methods, Sum3) {
  S21Matrix A(3, 8), B(3, 8);
  A.FillMatrix(1);
  B.FillMatrix(2);
  S21Matrix C(3, 8);
  C.FillMatrix(3);
  S21Matrix tmp1 = A + B;
  S21Matrix tmp2 = A;
  tmp2 += B;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

TEST(Methods, SumExeption) {
  S21Matrix A(3, 2), B(3, 3);
  EXPECT_ANY_THROW(A.SumMatrix(B));
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

TEST(Methods, Sub2) {
  S21Matrix A(3, 8), B(3, 8);
  A.FillMatrix(1);
  B.FillMatrix(2);
  S21Matrix C(3, 8);
  C.FillMatrix(-1);
  S21Matrix tmp1 = A - B;
  S21Matrix tmp2 = A;
  tmp2 -= B;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

TEST(Methods, Sub3) {
  S21Matrix A(8, 3), B(8, 3);
  A.FillMatrix(1);
  B.FillMatrix(2);
  S21Matrix C(8, 3);
  C.FillMatrix(-1);
  S21Matrix tmp1 = A - B;
  S21Matrix tmp2 = A;
  tmp2 -= B;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

TEST(Methods, SubExeption) {
  S21Matrix A(3, 2), B(3, 3);
  EXPECT_ANY_THROW(A.SubMatrix(B));
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
  tmp1.PrintMatrix();
  S21Matrix tmp2 = A;
  tmp2 *= B;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

TEST(Methods, MulM3) {
  S21Matrix A(1, 3), B(3, 1);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  B(0, 0) = 4;
  B(1, 0) = 5;
  B(2, 0) = 6;
  S21Matrix C(1, 1);
  C(0, 0) = 32;
  S21Matrix tmp1 = A * B;
  S21Matrix tmp2 = A;
  tmp2 *= B;
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
}

TEST(Methods, MulM4) {
  S21Matrix A(1, 3), B(3, 1);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  B(0, 0) = 4;
  B(1, 0) = 5;
  B(2, 0) = 6;
  S21Matrix C(1, 1);
  C(0, 0) = 32;
  S21Matrix CC(3, 3);
  CC(0, 0) = 4;
  CC(0, 1) = 8;
  CC(0, 2) = 12;
  CC(1, 0) = 5;
  CC(1, 1) = 10;
  CC(1, 2) = 15;
  CC(2, 0) = 6;
  CC(2, 1) = 12;
  CC(2, 2) = 18;

  S21Matrix tmp1 = A * B;
  S21Matrix tmp2 = A;
  tmp2 *= B;
  S21Matrix tmp3 = B * A;
  tmp3.PrintMatrix();
  EXPECT_EQ(tmp1.EqMatrix(C), true);
  EXPECT_EQ(tmp2.EqMatrix(C), true);
  EXPECT_EQ(tmp3.EqMatrix(CC), true);
}

TEST(Methods, MulMExeption) {
  S21Matrix A(3, 2), B(3, 2);
  S21Matrix C(2, 3), D(2, 3);
  EXPECT_ANY_THROW(A.MulMatrix(B));
  EXPECT_ANY_THROW(C.MulMatrix(D));
}

TEST(Methods, MulN1) {
  S21Matrix A(3, 3);
  S21Matrix B(2, 3);
  S21Matrix C(3, 2);
  A.FillMatrix(1);
  B.FillMatrix(2);
  C.FillMatrix(3);
  A.MulNumber(2);
  B.MulNumber(2);
  C.MulNumber(2);

  S21Matrix AA(3, 3);
  S21Matrix BB(2, 3);
  S21Matrix CC(3, 2);
  AA.FillMatrix(2);
  BB.FillMatrix(4);
  CC.FillMatrix(6);
  EXPECT_EQ(A.EqMatrix(AA), true);
  EXPECT_EQ(B.EqMatrix(BB), true);
  EXPECT_EQ(C.EqMatrix(CC), true);
}

TEST(Methods, Transpose1) {
  S21Matrix A(3, 2), B(2, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(1, 0) = 3;
  A(1, 1) = 4;
  A(2, 0) = 5;
  A(2, 1) = 6;
  B.FillMatrix(2);
  S21Matrix AA(2, 3);
  AA(0, 0) = 1;
  AA(0, 1) = 3;
  AA(0, 2) = 5;
  AA(1, 0) = 2;
  AA(1, 1) = 4;
  AA(1, 2) = 6;
  S21Matrix BB(3, 2);
  BB.FillMatrix(2);
  A = A.Transpose();
  B = B.Transpose();
  EXPECT_EQ(A.EqMatrix(AA), true);
  EXPECT_EQ(B.EqMatrix(BB), true);
}

TEST(Methods, Determinant1) {
  S21Matrix A(2, 2), B(2, 2);
  A(0, 0) = 2;
  A(0, 1) = 0;
  A(1, 0) = 0;
  A(1, 1) = 2;
  B.FillMatrix(2);
  EXPECT_EQ(A.Determinant(), 4);
  EXPECT_EQ(B.Determinant(), 0);
}

TEST(Methods, Determinant2) {
  S21Matrix A(3, 3), B(4, 4);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 4;
  A(1, 1) = 5;
  A(1, 2) = 6;
  A(2, 0) = 7;
  A(2, 1) = 8;
  A(2, 2) = 9;
  B.FillMatrix(2);
  EXPECT_EQ(A.Determinant(), 0);
  EXPECT_EQ(B.Determinant(), 0);
}

TEST(Methods, Determinant3) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 0;
  A(0, 2) = 0;
  A(1, 0) = 0;
  A(1, 1) = 1;
  A(1, 2) = 0;
  A(2, 0) = 0;
  A(2, 1) = 0;
  A(2, 2) = 1;
  EXPECT_EQ(A.Determinant(), 1);
}

TEST(Methods, Determinant04) {
  S21Matrix A(1, 1);
  A(0, 0) = 1;
  EXPECT_EQ(A.Determinant(), 1);
}

TEST(Methods, DeterminantExeption) {
  S21Matrix A(3, 2);
  A(0, 0) = 1;
  A(0, 1) = 0;
  A(1, 0) = 0;
  A(1, 1) = 1;
  A(2, 0) = 0;
  A(2, 1) = 0;
  EXPECT_ANY_THROW(A.Determinant());
}

TEST(Methods, Transpose01) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 0;
  A(0, 2) = 0;
  A(1, 0) = 0;
  A(1, 1) = 1;
  A(1, 2) = 0;
  A(2, 0) = 0;
  A(2, 1) = 0;
  A(2, 2) = 1;

  S21Matrix answer = A.Transpose();

  S21Matrix trA(3, 3);
  trA(0, 0) = 1;
  trA(0, 1) = 0;
  trA(0, 2) = 0;
  trA(1, 0) = 0;
  trA(1, 1) = 1;
  trA(1, 2) = 0;
  trA(2, 0) = 0;
  trA(2, 1) = 0;
  trA(2, 2) = 1;
  EXPECT_EQ(answer == trA, true);
}

TEST(Methods, Transpose02) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 0;
  A(0, 2) = 2;
  A(1, 0) = 0;
  A(1, 1) = 1;
  A(1, 2) = 0;
  A(2, 0) = 3;
  A(2, 1) = 0;
  A(2, 2) = 1;

  S21Matrix answer = A.Transpose();

  S21Matrix trA(3, 3);
  trA(0, 0) = 1;
  trA(0, 1) = 0;
  trA(0, 2) = 3;
  trA(1, 0) = 0;
  trA(1, 1) = 1;
  trA(1, 2) = 0;
  trA(2, 0) = 2;
  trA(2, 1) = 0;
  trA(2, 2) = 1;
  EXPECT_EQ(answer == trA, true);
}

TEST(Methods, Complements01) {
  S21Matrix A(3, 3);
  A(0, 0) = 0.73;
  A(0, 1) = -0.07;
  A(0, 2) = -0.12;
  A(1, 0) = -0.19;
  A(1, 1) = 0.72;
  A(1, 2) = -0.15;
  A(2, 0) = -0.12;
  A(2, 1) = -0.17;
  A(2, 2) = 0.92;

  S21Matrix answer = A.CalcComplements();

  S21Matrix ComplA(3, 3);
  ComplA(0, 0) = 0.6369;
  ComplA(0, 1) = 0.1928;
  ComplA(0, 2) = 0.1187;
  ComplA(1, 0) = 0.0848;
  ComplA(1, 1) = 0.6572;
  ComplA(1, 2) = 0.1325;
  ComplA(2, 0) = 0.0969;
  ComplA(2, 1) = 0.1323;
  ComplA(2, 2) = 0.5123;
  EXPECT_EQ(answer == ComplA, true);
}

TEST(Methods, ComplementsExeption) {
  S21Matrix A(3, 2);
  A(0, 0) = 0.73;
  A(0, 1) = -0.07;
  A(1, 0) = -0.19;
  A(1, 1) = 0.72;
  A(2, 0) = -0.12;
  A(2, 1) = -0.17;

  EXPECT_ANY_THROW(A.CalcComplements());
}

TEST(Methods, ComplementsExeptionZeroDeterminant) {
  S21Matrix A(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 1;
  A(0, 2) = 1;
  A(1, 0) = 2;
  A(1, 1) = 2;
  A(1, 2) = 2;
  A(2, 0) = 3;
  A(2, 1) = 3;
  A(2, 2) = 3;

  EXPECT_ANY_THROW(A.CalcComplements());
}

TEST(Methods, InverseMatrix01) {
  S21Matrix A(3, 3);
  A(0, 0) = 0.73;
  A(0, 1) = -0.07;
  A(0, 2) = -0.12;
  A(1, 0) = -0.19;
  A(1, 1) = 0.72;
  A(1, 2) = -0.15;
  A(2, 0) = -0.12;
  A(2, 1) = -0.17;
  A(2, 2) = 0.92;

  S21Matrix answer = A.InverseMatrix();

  S21Matrix C(3, 3);
  C(0, 0) = 1;
  C(1, 1) = 1;
  C(2, 2) = 1;
  EXPECT_EQ((answer * A) == C, true);
  S21Matrix tmp1(3, 3);
  tmp1 = answer * A;
  tmp1.PrintMatrix();
}

TEST(Methods, InverseMatrix02) {
  S21Matrix A(3, 3);
  A(0, 0) = -1;
  A(0, 1) = 2;
  A(0, 2) = -2;
  A(1, 0) = 2;
  A(1, 1) = -1;
  A(1, 2) = 5;
  A(2, 0) = 3;
  A(2, 1) = -2;
  A(2, 2) = 4;

  S21Matrix answer = A.InverseMatrix();

  S21Matrix C(3, 3);
  C(0, 0) = 1;
  C(1, 1) = 1;
  C(2, 2) = 1;
  EXPECT_EQ((answer * A) == C, true);
  S21Matrix tmp1(3, 3);
  tmp1 = answer * A;
  tmp1.PrintMatrix();
}

TEST(Methods, InverseMatrixExeption) {
  S21Matrix A(3, 2);
  A(0, 0) = -1;
  A(0, 1) = 2;
  A(1, 0) = 2;
  A(1, 1) = -1;
  A(2, 0) = 3;
  A(2, 1) = -2;

  EXPECT_ANY_THROW(A.InverseMatrix());
}

TEST(Methods, MulEqMatrix) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 1;
  A(1, 1) = 2;
  A(1, 2) = 3;
  A(2, 0) = 1;
  A(2, 1) = 2;
  A(2, 2) = 3;

  B(0, 0) = 1;
  B(0, 1) = 2;
  B(0, 2) = 3;
  B(1, 0) = 1;
  B(1, 1) = 2;
  B(1, 2) = 3;
  B(2, 0) = 1;
  B(2, 1) = 2;
  B(2, 2) = 3;

  C(0, 0) = 6;
  C(0, 1) = 12;
  C(0, 2) = 18;
  C(1, 0) = 6;
  C(1, 1) = 12;
  C(1, 2) = 18;
  C(2, 0) = 6;
  C(2, 1) = 12;
  C(2, 2) = 18;

  B *= A;
  EXPECT_EQ(C == B, true);
}

TEST(Methods, MulEqNum) {
  S21Matrix A(3, 3);
  S21Matrix B(3, 3);
  S21Matrix C(3, 3);
  A(0, 0) = 1;
  A(0, 1) = 2;
  A(0, 2) = 3;
  A(1, 0) = 1;
  A(1, 1) = 2;
  A(1, 2) = 3;
  A(2, 0) = 1;
  A(2, 1) = 2;
  A(2, 2) = 3;

  C(0, 0) = 6;
  C(0, 1) = 12;
  C(0, 2) = 18;
  C(1, 0) = 6;
  C(1, 1) = 12;
  C(1, 2) = 18;
  C(2, 0) = 6;
  C(2, 1) = 12;
  C(2, 2) = 18;

  A *= 6;
  // A.PrintMatrix();
  EXPECT_EQ(C == A, true);
}

TEST(Methods, Brackets) {
  S21Matrix A(2, 2);
  EXPECT_ANY_THROW(A(-1, 2) = 10);
}
int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
