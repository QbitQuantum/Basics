void drwnGaussian::evaluate(const vector<vector<double> >& x, vector<double>& p) const
{
    DRWN_ASSERT(x.size() == p.size());

    guaranteeInvSigma();
    for (unsigned i = 0; i < x.size(); i++) {
        DRWN_ASSERT(x[i].size() == (unsigned)_n);
        VectorXd z = Eigen::Map<const VectorXd>(&x[i][0], _n) - _mu;
        p[i] = -0.5 * (z.transpose() * (*_invSigma) * z)(0) + _logZ;
    }
}