void drwnNNGraphMLearner::subGradientStep(const MatrixXd& G, double alpha)
{
    DRWN_FCN_TIC;

    // gradient step
    _M -= alpha * G;

    // project onto psd
    SelfAdjointEigenSolver<MatrixXd> es;
    es.compute(_M);

    const VectorXd d = es.eigenvalues().real();
    if ((d.array() < 0.0).any()) {
        const MatrixXd V = es.eigenvectors();
        _M = V * d.cwiseMax(VectorXd::Constant(d.rows(), DRWN_EPSILON)).asDiagonal() * V.inverse();
    }

    DRWN_FCN_TOC;
}