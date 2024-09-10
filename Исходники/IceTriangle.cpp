void Triangle::Inflate(float fat_coeff, bool constant_border)
{
	// Compute triangle center
	Point TriangleCenter;
	Center(TriangleCenter);

	// Don't normalize?
	// Normalize => add a constant border, regardless of triangle size
	// Don't => add more to big triangles
	for(udword i=0;i<3;i++)
	{
		Point v = mVerts[i] - TriangleCenter;

		if(constant_border)	v.Normalize();

		mVerts[i] += v * fat_coeff;
	}
}