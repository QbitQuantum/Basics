void ScaleMatrix(D3DRMMATRIX4D* mat, float fX, float fY, float fZ)
{
	D3DRMMATRIX4D scalemat;

	IdentityMatrix(&scalemat);

	scalemat[0][0] = fX; 
	scalemat[1][1] = fY; 
	scalemat[2][2] = fZ;

	PostMultiplyMatrix(mat, &scalemat);

}