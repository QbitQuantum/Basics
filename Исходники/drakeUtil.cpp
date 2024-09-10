void care(MatrixBase<DerivedA> const& A, MatrixBase<DerivedB> const& B, MatrixBase<DerivedQ> const& Q, MatrixBase<DerivedR> const& R,  MatrixBase<DerivedX> & X)
{
    const size_t n = A.rows();

    LLT<MatrixXd> R_cholesky(R);

    MatrixXd H(2 * n, 2 * n);
    H << A, B * R_cholesky.solve(B.transpose()), Q, -A.transpose();

    MatrixXd Z = H;
    MatrixXd Z_old;

    //these could be options
    const double tolerance = 1e-9;
    const double max_iterations = 100;

    double relative_norm;
    size_t iteration = 0;

    const double p = static_cast<double>(Z.rows());

    do {
        Z_old = Z;
        //R. Byers. Solving the algebraic Riccati equation with the matrix sign function. Linear Algebra Appl., 85:267–279, 1987
        //Added determinant scaling to improve convergence (converges in rough half the iterations with this)
        double ck = pow(abs(Z.determinant()), -1.0/p);
        Z *= ck;
        Z = Z - 0.5 * (Z - Z.inverse());
        relative_norm = (Z - Z_old).norm();
        iteration ++;
    } while(iteration < max_iterations && relative_norm > tolerance);

    MatrixXd W11 = Z.block(0, 0, n, n);
    MatrixXd W12 = Z.block(0, n, n, n);
    MatrixXd W21 = Z.block(n, 0, n, n);
    MatrixXd W22 = Z.block(n, n, n, n);

    MatrixXd lhs(2 * n, n);
    MatrixXd rhs(2 * n, n);
    MatrixXd eye = MatrixXd::Identity(n, n);
    lhs << W12, W22 + eye;
    rhs << W11 + eye, W21;

    JacobiSVD<MatrixXd> svd(lhs, ComputeThinU | ComputeThinV);

    X = svd.solve(rhs);
}