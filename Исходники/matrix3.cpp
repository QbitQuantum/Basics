// DIVISION A/B = A * (1/B) = A * Inverse(B)
Matrix3 Matrix3::operator/ ( const Matrix3& myMatrix ) const
{
	Matrix3 temp = myMatrix;

	return( *this * temp.Inverse() );
}