static void testNullSpacesIntersection() {
	typedef Matrix<double, Dynamic, Dynamic, RowMajor> MatT;
	double AData[] = {
		1, -1, 1,
		1, -1, 1,
		1, -1, 1
	};
	double BData[] = {
		4, 2, 0,
		2, 1, 0,
		6, 3, 0
	};
	double expectedYData[] = {
		1,
		-2,
		-3
	};

	Map<MatT> A(AData, 3, 3);
	Map<MatT> B(BData, 3, 3);
	Map<MatT> expectedY(expectedYData, 3, 1);

	MatrixXd Y;

	nullSpacesIntersection(A, B, Y);

	// colinearity test through dot product
	assert(abs((Y.transpose() * expectedY)(0)) - (Y.norm() * expectedY.norm()) <= 10E-4);
}