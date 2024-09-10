//----------------------------------------------------------------------------
void AffineTransform (int warmups, Ellipse2f& ellipse0, Ellipse2f& ellipse1)
{
	float random = 0.0f;
	for (int i = 0; i < warmups; ++i)
	{
		random = Mathf::SymmetricRandom();
	}

	Matrix2f A;
	Vector2f B;
	for (int row = 0; row < 2; ++row)
	{
		for (int col = 0; col < 2; ++col)
		{
			A[row][col] = Mathf::SymmetricRandom();
		}
		B[row] = Mathf::SymmetricRandom();
	}
	if (A.Determinant() < 0.0f)
	{
		A[0][0] = -A[0][0];
		A[0][1] = -A[0][1];
	}

	Matrix2f invA = A.Inverse();
	Vector2f K = invA*(ellipse0.Center - B);
	Matrix2f D(
	    1.0f/(ellipse0.Extent[0]*ellipse0.Extent[0]),
	    1.0f/(ellipse0.Extent[1]*ellipse0.Extent[1]));
	Matrix2f N = A.TransposeTimes(D)*A;
	Matrix2f R;
	N.EigenDecomposition(R, D);

	ellipse0.Center = K;
	ellipse0.Axis[0] = R.GetColumn(0);
	ellipse0.Axis[1] = R.GetColumn(1);
	ellipse0.Extent[0] = Mathf::InvSqrt(D[0][0]);
	ellipse0.Extent[1] = Mathf::InvSqrt(D[1][1]);

	K = invA*(ellipse1.Center - B);
	D = Matrix2f(
	        1.0f/(ellipse1.Extent[0]*ellipse1.Extent[0]),
	        1.0f/(ellipse1.Extent[1]*ellipse1.Extent[1]));
	N = A.TransposeTimes(D)*A;
	N.EigenDecomposition(R, D);

	ellipse1.Center = K;
	ellipse1.Axis[0] = R.GetColumn(0);
	ellipse1.Axis[1] = R.GetColumn(1);
	ellipse1.Extent[0] = Mathf::InvSqrt(D[0][0]);
	ellipse1.Extent[1] = Mathf::InvSqrt(D[1][1]);
}