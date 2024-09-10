Matrix44 Matrix44::getRotationOnly()
{
	Matrix44 trans = *this;
	trans.transpose();

	Matrix44 inv = *this;
	inv.inverse();

	return trans * inv;
}