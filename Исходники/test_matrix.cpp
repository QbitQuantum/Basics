bool MatrixTest::matrixAssignmentTests(void)
{
	Matrix3f m;
	m.setZero();
	m(0, 0) = 1;
	m(0, 1) = 2;
	m(0, 2) = 3;
	m(1, 0) = 4;
	m(1, 1) = 5;
	m(1, 2) = 6;
	m(2, 0) = 7;
	m(2, 1) = 8;
	m(2, 2) = 9;

	float data[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	Matrix3f m2(data);

	double eps = 1e-6f;

	for (int i = 0; i < 9; i++) {
		ut_test(fabs(data[i] - m2.data()[i]) < eps);
	}

	float data_times_2[9] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
	Matrix3f m3(data_times_2);

	ut_test(isEqual(m, m2));
	ut_test(!isEqual(m, m3));

	m2 *= 2;
	ut_test(isEqual(m2, m3));

	m2 /= 2;
	m2 -= 1;
	float data_minus_1[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	ut_test(isEqual(Matrix3f(data_minus_1), m2));

	m2 += 1;
	ut_test(isEqual(Matrix3f(data), m2));

	m3 -= m2;

	ut_test(isEqual(m3, m2));

	float data_row_02_swap[9] = {
		7, 8, 9,
		4, 5, 6,
		1, 2, 3,
	};

	float data_col_02_swap[9] = {
		3, 2, 1,
		6, 5, 4,
		9, 8, 7
	};

	Matrix3f m4(data);

	ut_test(isEqual(-m4, m4 * (-1)));

	m4.swapCols(0, 2);
	ut_test(isEqual(m4, Matrix3f(data_col_02_swap)));
	m4.swapCols(0, 2);
	m4.swapRows(0, 2);
	ut_test(isEqual(m4, Matrix3f(data_row_02_swap)));
	ut_test(fabs(m4.min() - 1) < 1e-5);

	Scalar<float> s;
	s = 1;
	ut_test(fabs(s - 1) < 1e-5);

	Matrix<float, 1, 1> m5 = s;
	ut_test(fabs(m5(0, 0) - s) < 1e-5);

	Matrix<float, 2, 2> m6;
	m6.setRow(0, Vector2f(1, 1));
	m6.setCol(0, Vector2f(1, 1));

	return true;
}