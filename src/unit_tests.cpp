#include <gtest/gtest.h>
#include "s21_matrix.h"

using namespace std;

TEST(Constructors, Default) {
  S21Matrix matrix;
  EXPECT_EQ(2, matrix.GetRows());
  EXPECT_EQ(2, matrix.GetCols());
}

TEST(Constructors, Parameters) {
  S21Matrix matrix1(5, 5);
  EXPECT_EQ(5, matrix1.GetRows());
  EXPECT_EQ(5, matrix1.GetCols());

  EXPECT_NO_THROW(S21Matrix matrix2(10, 10));
  EXPECT_ANY_THROW(S21Matrix matrix3(0, 10));
  EXPECT_ANY_THROW(S21Matrix matrix4(10, 0));
  EXPECT_ANY_THROW(S21Matrix matrix5(-10, 10));
  EXPECT_ANY_THROW(S21Matrix matrix6(10, -10));
  EXPECT_ANY_THROW(S21Matrix matrix7(-0, 10));
  EXPECT_ANY_THROW(S21Matrix matrix8(10, -0));
}

TEST(Constructors, Copy) {
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

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
