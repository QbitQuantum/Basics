VectorXi ind2sub(int k,int nrows, int ncols)
{
	VectorXi v;
	v.setZero(2);
	v(1) = floor(k/nrows);
	v(0) = k - v(1)*nrows;
	return v;
}