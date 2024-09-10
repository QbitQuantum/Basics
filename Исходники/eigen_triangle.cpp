// full reorthogonalization
double                  EigenTriangle::solve(int maxIter)
{
    int n = graph -> VertexCount();
    srand(time(0));
    // check if rows == cols()
    if (maxIter > n)
        maxIter = n;
    vector<VectorXd> v;
    v.push_back(VectorXd::Random(n));
    v[0] = v[0] / v[0].norm();
    VectorXd alpha(n);
    VectorXd beta(n + 1);
    beta[0] = 0;
    VectorXd w;
    int last = 0;
    printf("%d\n", maxIter);
    for (int i = 0; i < maxIter; i ++)
    {
        if (i * 100 / maxIter > last + 10 || i == maxIter - 1)
        {
            last = (i + 1) * 100 / maxIter;
            std::cout << "\r" << "[EigenTriangle] Processing " << last << "% ..." << std::flush;
        }
        w = adjMatrix * v[i];
        alpha[i] = w.dot(v[i]);
        if (i == maxIter - 1)
            break;
        w -= alpha[i] * v[i];
        if (i > 0)
            w -= beta[i] * v[i - 1];
        beta[i + 1] = w.norm();
        v.push_back(w / beta[i + 1]);
        for (int j = 0; j <= i; j ++)
        {
            v[i + 1] = v[i + 1] - v[i + 1].dot(v[j]) * v[j];
        }
    }
    printf("\n");
    int k = maxIter;
    MatrixXd T = MatrixXd::Zero(k, k);
    for (int i = 0; i < k; i ++)
    {
        T(i, i) = alpha[i];
        if (i < k - 1)
            T(i, i + 1) = beta[i + 1];
        if (i > 0)
            T(i, i - 1) = beta[i];
    }
    //std::cout << T << std::endl;

    Eigen::EigenSolver<MatrixXd> eigenSolver;
    eigenSolver.compute(T, /* computeEigenvectors = */ false);
    Eigen::VectorXcd eigens = eigenSolver.eigenvalues();
    double res = 0;
    for (int i = 0; i < eigens.size(); i ++)
    {
        std::complex<double> tmp = eigens[i];
        res += pow(tmp.real(), 3);
        printf("%.5lf\n", tmp.real());
    }
    res /= 6;
    return res;
}