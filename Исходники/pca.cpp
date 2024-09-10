void pca::pca_trans(const MatrixType & centered_train_)
{
    MatrixType Ct = centered_train_.transpose() * centered_train_;
    Ct = 0.5*(Ct+Ct.transpose());

    Eigen::SelfAdjointEigenSolver<MatrixType> eigensolver(Ct);
    eigenval = eigensolver.eigenvalues();
    P = centered_train_*eigensolver.eigenvectors();

    VectorType eigv_norm = P.colwise().norm();

    for (int i = 0; i<P.cols(); i ++)
    {
        P.col(i).array() /= std::max(std::numeric_limits<NumericType>::epsilon(),eigv_norm(i));
    }


}