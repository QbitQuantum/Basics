double gaussian_kl_divergence( const VectorType& mean0, const MatrixType& info0,
                               const VectorType& mean1, const MatrixType& info1 )
{
	Eigen::LDLT<MatrixType> ldl0( info0 );
	Eigen::LDLT<MatrixType> ldl1( info1 );

	double det0 = ldl0.vectorD().prod();
	double det1 = ldl1.vectorD().prod();
	double detDiff = std::log( det0 ) - std::log( det1 );

	MatrixType invProd = ldl0.solve( info1 );

	VectorType meanDiff = mean1 - mean0;
	double quadTerm = meanDiff.dot( info1 * meanDiff );

	return 0.5 * ( invProd.trace() + quadTerm - mean0.size() + detDiff );
}