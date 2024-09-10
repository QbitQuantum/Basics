double Matrixf3Measure(const Matrixf3& mx)
{
	double d = Determinant(mx);
	return (d >= 0 ? +1 : -1) * pow(fabs(d), 1.0 / 3.0);
}