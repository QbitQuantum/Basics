NaiveBayesClassifier::NaiveBayesClassifier(const vector<VectorXd>& x,
                                           const vector<int>& y) :
k(0), d(0), p(), mu(), var() {
    // n is the number of points
    unsigned n = x.size();
    assert(n > 0);
    assert(y.size() == n);

    // d is the dimensionality
    d = x[0].size();
    for (const VectorXd& v : x)
        assert(v.size() == d);

    // number of classes
    k = *(std::max_element(y.cbegin(), y.cend())) + 1;

    for (int i = 0; i < k; ++i) {
        // find all points in class i
        vector<VectorXd> xi;
        for (unsigned j = 0; j < n; ++j)
            if (y[j] == i)
                xi.push_back(x[j]);

        // ni is the number of points in class i
        int ni = xi.size();
        assert(ni > 0);

        // prior probability
        p.push_back((double)ni / (double)n);

        // class mean
        VectorXd m = VectorXd::Zero(d);
        for (const VectorXd& v : xi)
            m += v;
        m /= ni;
        mu.push_back(m);

        // centered data matrix
        MatrixXd z(d, ni);
        for (int j = 0; j < ni; ++j)
            z.col(j) = xi[j] - m;

        // class-specific attribute variances
        VectorXd variance(d);
        for (int j = 0; j < d; ++j) {
            VectorXd zj = z.row(j);
            variance(j) = (1.0/ni) * zj.dot(zj);
        }
        var.push_back(variance);
    }
}