/***********************************************************************//**
 * @brief Test Cholesky decomposition
 ***************************************************************************/
void TestGSymMatrix::matrix_cholesky(void)
{
    // Test Cholesky decomposition
	GSymMatrix cd           = cholesky_decompose(m_test);
	GMatrix    cd_lower     = cd.extract_lower_triangle();
	GMatrix    cd_upper     = transpose(cd_lower);
	GMatrix    cd_product   = cd_lower * cd_upper;
	GMatrix    cd_residuals = GMatrix(m_test) - cd_product;
	double res = (abs(cd_residuals)).max();
    test_value(res, 0.0, 1.0e-15, "Test cholesky_decompose() method");

    // Test compressed Cholesky decomposition
    GSymMatrix test_zero         = set_matrix_zero();
	GSymMatrix cd_zero           = cholesky_decompose(test_zero);
	GMatrix    cd_zero_lower     = cd_zero.extract_lower_triangle();
	GMatrix    cd_zero_upper     = transpose(cd_zero_lower);
	GMatrix    cd_zero_product   = cd_zero_lower * cd_zero_upper;
	GMatrix    cd_zero_residuals = GMatrix(test_zero) - cd_zero_product;
	res = (abs(cd_zero_residuals)).max();
    test_value(res, 0.0, 1.0e-15, "Test compressed cholesky_decompose() method");

	// Test Cholesky inplace decomposition
	GSymMatrix test = m_test;
    test.cholesky_decompose();
	GMatrix cd_lower2 = test.extract_lower_triangle();
    test_assert((cd_lower2 == cd_lower), "Test inplace cholesky_decompose() method");

    // Test Cholesky solver (first test)
	GVector e0(g_rows);
	GVector a0(g_rows);
	e0[0] = 1.0;
	e0[1] = 0.0;
	e0[2] = 0.0;
	a0[0] = g_matrix[0];
	a0[1] = g_matrix[3];
	a0[2] = g_matrix[6];
	GVector s0 = cd.cholesky_solver(a0) - e0;
	res = max(abs(s0));
    test_value(res, 0.0, 1.0e-15, "Test cholesky_solver() method");

    // Test Cholesky solver (second test)
	e0[0] = 0.0;
	e0[1] = 1.0;
	e0[2] = 0.0;
	a0[0] = g_matrix[1];
	a0[1] = g_matrix[4];
	a0[2] = g_matrix[7];
	s0 = cd.cholesky_solver(a0) - e0;
	res = max(abs(s0));
    test_value(res, 0.0, 1.0e-15, "Test cholesky_solver() method");

    // Test Cholesky solver (third test)
	e0[0] = 0.0;
	e0[1] = 0.0;
	e0[2] = 1.0;
	a0[0] = g_matrix[2];
	a0[1] = g_matrix[5];
	a0[2] = g_matrix[8];
	s0 = cd.cholesky_solver(a0) - e0;
	res = max(abs(s0));
    test_value(res, 0.0, 1.0e-15, "Test cholesky_solver() method");

    // Test compressed Cholesky solver (first test)
	e0 = GVector(g_rows+1);
	a0 = GVector(g_rows+1);
	e0[0] = 1.0;
	e0[1] = 0.0;
	e0[2] = 0.0;
	e0[3] = 0.0;
	a0[0] = g_matrix[0];
	a0[1] = g_matrix[3];
	a0[2] = 0.0;
	a0[3] = g_matrix[6];
	s0    = cd_zero.cholesky_solver(a0) - e0;
	res   = max(abs(s0));
    test_value(res, 0.0, 1.0e-15, "Test compressed cholesky_solver() method");

    // Test compressed Cholesky solver (second test)
	e0[0] = 0.0;
	e0[1] = 1.0;
	e0[2] = 0.0;
	e0[3] = 0.0;
	a0[0] = g_matrix[1];
	a0[1] = g_matrix[4];
	a0[2] = 0.0;
	a0[3] = g_matrix[7];
	s0    = cd_zero.cholesky_solver(a0) - e0;
	res   = max(abs(s0));
    test_value(res, 0.0, 1.0e-15, "Test compressed cholesky_solver() method");

    // Test compressed Cholesky solver (third test)
	e0[0] = 0.0;
	e0[1] = 0.0;
	e0[2] = 0.0;
	e0[3] = 1.0;
	a0[0] = g_matrix[2];
	a0[1] = g_matrix[5];
	a0[2] = 0.0;
	a0[3] = g_matrix[8];
	s0    = cd_zero.cholesky_solver(a0) - e0;
	res   = max(abs(s0));
    test_value(res, 0.0, 1.0e-15, "Test compressed cholesky_solver() method");

	// Test Cholesky inverter
	GSymMatrix unit(g_rows,g_cols);
	unit(0,0) = unit(1,1) = unit(2,2) = 1.0;
	GSymMatrix test_inv = m_test;
	test_inv.cholesky_invert();
    GMatrix ci_product   = m_test * test_inv;
    GMatrix ci_residuals = ci_product - unit;
	res = (abs(ci_residuals)).max();
    test_value(res, 0.0, 1.0e-15, "Test cholesky_invert method");

	// Test Cholesky inverter for compressed matrix
	unit = GSymMatrix(4,4);
	unit(0,0) = unit(1,1) = unit(3,3) = 1.0;
	GSymMatrix test_zero_inv = test_zero;
	test_zero_inv.cholesky_invert();
    GMatrix ciz_product   = test_zero * test_zero_inv;
    GMatrix ciz_residuals = ciz_product - unit;
	res = (abs(ciz_residuals)).max();
    test_value(res, 0.0, 1.0e-15, "Test compressed cholesky_invert method");

    // Return
    return;
}