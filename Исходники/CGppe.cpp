void CGppe::Approx_CGppe_Laplace(const VectorXd & theta_x, const VectorXd& theta_t, const double& sigma, const MatrixXd& t, const MatrixXd &x, const TypePair & all_pairs,
                               const VectorXd & idx_global, const VectorXd& idx_global_1, const VectorXd& idx_global_2,
                               const VectorXd& ind_t, const VectorXd& ind_x, int M, int N)
{
    //Parameters function initialization
    double eps = 1E-6, psi_new, psi_old;
    M = all_pairs.rows();
    int n = M * N;
    f = VectorXd::Zero(n);
    VectorXd fvis = VectorXd::Zero(idx_global.rows());
    VectorXd deriv;
    double loglike = 0;

    covfunc_t->SetTheta(theta_t);
    covfunc_x->SetTheta(theta_x);

    MatrixXd Kt = covfunc_t->ComputeGrandMatrix(t);
    Kx = covfunc_x->ComputeGrandMatrix(x);

    MatrixXd K = GetMat(Kt, ind_t, ind_t).array() * GetMat(Kx, ind_x, ind_x).array();

    loglike = log_likelihood( sigma, all_pairs, idx_global_1, idx_global_2, M, N);
    Kinv = K.inverse();
    psi_new = loglike - 0.5 * fvis.transpose() * Kinv * fvis;
    psi_old = INT_MIN;
    while ((psi_new - psi_old) > eps)
    {
        psi_old = psi_new;
        deriv = deriv_log_likelihood_CGppe_fast( sigma, all_pairs, idx_global_1, idx_global_2, M, N);
        W = -deriv2_log_likelihood_CGppe_fast(sigma, all_pairs, idx_global_1, idx_global_2, M, N);
        W = GetMat(W, idx_global, idx_global);
        llt.compute(W + Kinv);
        L = llt.matrixL(); //no need to extract the triangular matrix here
        fvis = llt.solve(GetVec(deriv, idx_global) + W * fvis);
        for (int w = 0;w < idx_global.rows();w++)
        {
            f(idx_global(w)) = fvis(w);
        }
        loglike = log_likelihood( sigma, all_pairs, idx_global_1, idx_global_2, M, N);
        psi_new = loglike - 0.5 * fvis.transpose() * Kinv * fvis;
    }





}