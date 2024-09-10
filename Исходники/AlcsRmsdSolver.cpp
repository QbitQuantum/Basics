double determinant(double  mat[3][3])
{
	MatrixXd mmat = get3by3Mat(mat);
	return mmat.determinant();
}