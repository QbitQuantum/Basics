int GzRotZMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
	GzMatrix m;
	float cd = cos(degree * PIOVER180);
	float sd = sin(degree * PIOVER180);

	IdentityMatrix(m);
	m[0][0] = cd;
	m[1][0] = sd;
	m[0][1] = -sd;
	m[1][1] = cd;

	memcpy((GzMatrix*)mat, (GzMatrix*)m, sizeof(GzMatrix));

	return GZ_SUCCESS;
}