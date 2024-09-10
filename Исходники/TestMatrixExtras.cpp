void TestMatrixExtras::test_add_DST() {
    for (size_t n = 11; n < 40; n += 5) {
        for (size_t m = 13; m < 30; m += 3) {
            size_t nnz = 100;
            Matrix A = MatrixFactory::MakeRandomMatrix(n, m, 2.0, 1.0);
            Matrix B = MatrixFactory::MakeRandomSparse(m, n, nnz, 2.0, 1.0);

            Matrix A_copy(A);
            Matrix B_copy(B);

            B.transpose();

            double alpha = -1.0 + 2.0 * static_cast<double> (std::rand()) / static_cast<double> (RAND_MAX);
            double gamma = -0.5 + static_cast<double> (std::rand()) / static_cast<double> (RAND_MAX);
            const double tol = 1e-8;

            int status = Matrix::add(A, alpha, B, gamma); // A = gamma * A + alpha * B
            _ASSERT_EQ(ForBESUtils::STATUS_OK, status);

            _ASSERT_EQ(n, A.getNrows());
            for (size_t i = 0; i < n; i++) {
                for (size_t j = 0; j < m; j++) {
                    _ASSERT_NUM_EQ(gamma * A_copy.get(i, j) + alpha * B_copy.get(j, i), A.get(i, j), tol);
                }
            }
        }
    }
}