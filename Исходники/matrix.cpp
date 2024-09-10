Matrix Matrix::operator / (const Matrix& m)
{
	Matrix matrix = *this;
	return matrix * m.Inverse();
}