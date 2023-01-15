#include <iostream>

class S21Matrix {
	private:
		// Attributes
		int rows_, cols_;
		double **matrix_;
	public:
		S21Matrix();
		~S21Matrix();

		void SumMatrix(const S21Matrix& other);
		// Other methods...
}
