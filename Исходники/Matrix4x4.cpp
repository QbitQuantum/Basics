Matrix4x4& Matrix4x4::quadricScale(const Vector& factors)
{
	Matrix4x4 scaleMatrix;
	scaleMatrix.makeScaling(factors);
	Matrix4x4 scaleMatrixInverse = scaleMatrix.invert();
	(*this) = scaleMatrixInverse * (*this) * scaleMatrixInverse.transpose();
	return *this;
}