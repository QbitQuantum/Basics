std::unique_ptr<MatrixXd> assemble_kkt(
        const std::vector<MatrixXd>& R, const std::vector<MatrixXd>& D)
{
    int n = R.size(), m = R[0].rows();
    assert(n > 0 && D.size() == n + 1);

    int kktSize = (2 * n + 1) * m;
    MatrixXd * pMat = new MatrixXd(kktSize, kktSize);
    pMat->setZero();

    for (int i = 0; i <= n; ++ i) {
        pMat->block(i * m, i * m, m, m) = D[i];
    }

    int halfSize = (n + 1) * m;
    for (int i = 0; i < n; ++ i) {
        pMat->block(halfSize + i * m, (i + 1) * m, m, m) = MatrixXd::Identity(m, m);
        pMat->block(halfSize + i * m, i * m, m, m) = -R[i];

        pMat->block((i + 1) * m, halfSize + i * m, m, m) = MatrixXd::Identity(m, m);
        pMat->block(i * m, halfSize + i * m, m, m) = -R[i].transpose();
    }

    return std::unique_ptr<MatrixXd>(pMat);
}