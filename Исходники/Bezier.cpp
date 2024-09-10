Vec3 Bezier::SurfNorm(float px, float py) const
{
	Vec3 tempy[4];
	Vec3 tempx[4];
	Vec3 temp2[4];

	//get splines along x axis
	for (int j = 0; j < 4; ++j)
	{
		tempy[j] = Bernstein(px, points[j]);
	}

	//get splines along y axis
	for (int j = 0; j < 4; ++j)
	{
		for (int i = 0; i < 4; ++i)
		{
			temp2[i] = points[i][j];
		}
		tempx[j] = Bernstein(py, temp2);
	}

	Vec3 tx = BernsteinTangent(px, tempx);
	Vec3 ty = BernsteinTangent(py, tempy);
	Vec3 n = -tx.cross(ty).Normalize();

	return n;
}