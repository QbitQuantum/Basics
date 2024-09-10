void grscc<G>::initcsct()
{
    const matrix<G> stategen = getstategen();
    const matrix<G> eye = matrix<G>::eye(this->nu);
    matrix<G> Gi;
    // determine period
    int L;
    Gi = stategen;
    for (L = 1; (eye + Gi).max() > 0; L++)
        Gi *= stategen;
    trace << "DEBUG (grscc): period = " << L << std::endl;
    // correspondence table has first index for N%L, second index for S_N^0
    csct.init(L, this->num_states());
    // go through all combinations (except N%L=0, which is illegal) and fill in
    Gi = eye;
    for (int i = 1; i < L; i++)
    {
        Gi *= stategen;
        const matrix<G> IGi = eye + Gi;
        // check if matrix is non-invertible
        if (IGi.rank() < IGi.size().rows())
        {
            // clear circulation table to indicate we cannot do this
            csct.init(0, 0);
            return;
        }
        // compute inverse and determine circulation values at this offset
        const matrix<G> A = IGi.inverse();
        for (int j = 0; j < this->num_states(); j++)
        {
            vector<G> statevec = A * ccfsm<G>::convert(j, ccfsm<G>::nu);
            csct(i, j) = ccfsm<G>::convert(statevec);
        }
    }
}