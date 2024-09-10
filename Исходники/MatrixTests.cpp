/// Test setting matrices to 0.
TYPED_TEST(AllMatrixTests, SetToZero)
{
	typedef typename TestFixture::Matrix Matrix;
	const int SIZE = Matrix::RowsAtCompileTime;

	Matrix matrix;
	matrix.setZero();
	for (int row = 0;  row < SIZE;  ++row)
	{
		for (int col = 0;  col < SIZE;  ++col)
		{
			EXPECT_NEAR(0.0, matrix(row, col), 1e-20) << row << "," << col << " wasn't properly cleared.";
		}
	}
}