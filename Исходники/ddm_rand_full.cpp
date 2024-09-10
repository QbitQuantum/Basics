/** the gateway function */
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    /* [t, b] = ddm_rand_full(mu, sig2, b_lo, b_up, 
                              delta_t, n[, inv_leak[, seed]]) */

    /* Check argument number */
    if (nlhs != 2) {
        mexErrMsgIdAndTxt("ddm_rand_full:WrongOutputs", 
                          "Wrong number of output arguments");
    }
    if (nrhs < 6) {
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInputs",
                          "Too few input arguments");
    }

    /* Process first 8 arguments */
    if (!MEX_ARGIN_IS_REAL_VECTOR(0))
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInput",
                          "First input argument expected to be a vector");
    if (!MEX_ARGIN_IS_REAL_VECTOR(1))
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInput",
                          "Second input argument expected to be a vector");
    if (!MEX_ARGIN_IS_REAL_VECTOR(2))
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInput",
                          "Third input argument expected to be a vector");
    if (!MEX_ARGIN_IS_REAL_VECTOR(3))
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInput",
                          "Fourth input argument expected to be a vector");
    if (!MEX_ARGIN_IS_REAL_DOUBLE(4))
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInput",
                          "Fifth input argument expected to be a double");
    if (!MEX_ARGIN_IS_REAL_DOUBLE(5))
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInput",
                          "Sixth input argument expected to be a double");
    if (nrhs >= 7 && !MEX_ARGIN_IS_REAL_DOUBLE(6))
        mexErrMsgIdAndTxt("ddm_rand_sym:WrongInput",
                          "Seventh input argument expected to be a double");
    if (nrhs >= 8 && !MEX_ARGIN_IS_REAL_DOUBLE(7))
        mexErrMsgIdAndTxt("ddm_rand_sym:WrongInput",
                          "Eighth input argument expected to be a double");
    int mu_size = std::max(mxGetN(prhs[0]), mxGetM(prhs[0]));
    int sig2_size = std::max(mxGetN(prhs[1]), mxGetM(prhs[1]));
    int b_lo_size = std::max(mxGetN(prhs[2]), mxGetM(prhs[2]));
    int b_up_size = std::max(mxGetN(prhs[3]), mxGetM(prhs[3]));
    ExtArray mu(ExtArray::shared_noowner(mxGetPr(prhs[0])), mu_size);
    ExtArray sig2(ExtArray::shared_noowner(mxGetPr(prhs[1])), sig2_size);
    ExtArray b_lo(ExtArray::shared_noowner(mxGetPr(prhs[2])), b_lo_size);
    ExtArray b_up(ExtArray::shared_noowner(mxGetPr(prhs[3])), b_up_size);
    ExtArray b_lo_deriv = ExtArray::const_array(0.0);
    ExtArray b_up_deriv = ExtArray::const_array(0.0);
    double delta_t = mxGetScalar(prhs[4]);
    int n = (int) mxGetScalar(prhs[5]);
    if (delta_t <= 0.0)
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInput",
                          "delta_t needs to be larger than 0.0");
    if (n <= 0)
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInput",
                          "n needs to be larger than 1");
    bool has_leak = false;
    double inv_leak = 0.0;
    if (nrhs >= 7) {
        inv_leak = mxGetScalar(prhs[6]);
        has_leak = (inv_leak != 0.0);
        if (inv_leak < 0.0)
            mexErrMsgIdAndTxt("ddm_rand_full:WrongInput",
                              "inv_leak needs to be non-negative");
    }
    int rngseed = 0;
    if (nrhs >= 8)
        rngseed = (int) mxGetScalar(prhs[7]);
    if (nrhs > 8)
        mexErrMsgIdAndTxt("ddm_rand_full:WrongInputs",
                          "Too many input arguments");

    /* reserve space for output */
    plhs[0] = mxCreateDoubleMatrix(1, n, mxREAL);
    plhs[1] = mxCreateLogicalMatrix(1, n);
    double* t = mxGetPr(plhs[0]);
    mxLogical* b = mxGetLogicals(plhs[1]);

    /* perform sampling */
    DMBase* dm = nullptr;
    if (has_leak)
        dm = DMBase::create(mu, sig2, b_lo, b_up, b_lo_deriv, b_up_deriv,
                            delta_t, inv_leak);
    else
        dm = DMBase::create(mu, sig2, b_lo, b_up, b_lo_deriv, b_up_deriv,
                            delta_t);
    DMBase::rngeng_t rngeng;
    if (rngseed == 0) rngeng.seed(std::random_device()());
    else rngeng.seed(rngseed);
    for (int i = 0; i < n; ++i) {
        DMSample s = dm->rand(rngeng);
        t[i] = s.t();
        b[i] = s.upper_bound() ? 1 : 0;
    }
    delete dm;
}