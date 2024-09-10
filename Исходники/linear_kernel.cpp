MatrixType linear_kernel::eval(const MatrixType & X, const MatrixType & Y) const
{
	return X.transpose()*Y;
}