TEST(MatrixTests, Determinant)
{
	Matrix test = Matrix::RotationX(1.0f) * Matrix::Translation(1.0f, 2.0f, 3.0f);

	ASSERT_FLOAT_EQ(D3DXMatrixDeterminant(reinterpret_cast<D3DXMATRIX*>(&test)), test.Determinant());
}