void StateEstimatorKinematic::dare(const Eigen::Matrix<double,6,6> &A, const Eigen::Matrix<double,6,6> &B, Eigen::Matrix<double,6,6> &P,int zDim)
{
    Eigen::Matrix<double,6,6> Ainv = A.inverse();
    Eigen::Matrix<double,6,6> ABRB;
    if (zDim == 6)
    {
        ABRB = Ainv * B * _R.llt().solve(B.transpose());
    }
    else {
        ABRB = Ainv * B.topLeftCorner(6,zDim) * _R.topLeftCorner(zDim,zDim).llt().solve(B.topLeftCorner(6,zDim).transpose());
    }
    Eigen::Matrix<double,2*6,2*6> Z;
    Z.block(0,0,6,6) = Ainv;
    Z.block(0,6,6,6) = ABRB;
    Z.block(6,0,6,6) = _Q * Ainv;
    Z.block(6,6,6,6) = A.transpose() + _Q * ABRB;

    Eigen::ComplexEigenSolver <Eigen::Matrix<double,2*6,2*6> > ces;
    ces.compute(Z);

    Eigen::Matrix<std::complex<double>,2*6,1> eigVal = ces.eigenvalues();
    Eigen::Matrix<std::complex<double>,2*6,2*6> eigVec = ces.eigenvectors();

    Eigen::Matrix<std::complex<double>,2*6,6> unstableEigVec;

    int ctr = 0;
    for (int i = 0; i < 2*6; i++) {
        if (eigVal(i).real()*eigVal(i).real() + eigVal(i).imag()*eigVal(i).imag() > 1) {
            unstableEigVec.col(ctr) = eigVec.col(i);
            ctr++;
            if (ctr > 6)
                break;
        }
    }

    Eigen::Matrix<std::complex<double>,6,6> U21inv = unstableEigVec.block(0,0,6,6).inverse();
    Eigen::Matrix<std::complex<double>,6,6> PP = unstableEigVec.block(6,0,6,6) * U21inv;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            P(i,j) = PP(i,j).real();
        }
    }
}