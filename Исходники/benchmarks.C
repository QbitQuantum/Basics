TwoDoubles f19(double* x) {
    /* F8F2 sum of Griewank-Rosenbrock 2-D blocks*/
    int i, j, rseed; /*Loop over dim*/
    static unsigned int funcId = 19;
    double scales, F2, tmp = 0., tmp2, Fadd, Fval, Ftrue = 0.;
    TwoDoubles res;

    if (!isInitDone)
    {
        rseed = funcId + 10000 * trialid;
        /*INITIALIZATION*/
        Fopt = computeFopt(funcId, trialid);
        /* computeXopt(rseed, DIM); Xopt is not used.*/
        scales = fmax(1., sqrt(DIM) / 8.);
        computeRotation(rotation, rseed, DIM);
        for (i = 0; i < DIM; i ++)
        {
            for (j = 0; j < DIM; j++)
            {
                linearTF[i][j] = scales * rotation[i][j];
            }
        }
        for (i = 0; i < DIM; i++)
        {
            Xopt[i] = 0.;
            for (j = 0; j < DIM; j++)
            {
                Xopt[i] += linearTF[j][i] * 0.5/scales/scales;
            }
        }
        isInitDone = 1;
    }
    Fadd = Fopt;
    /* BOUNDARY HANDLING*/

    /* TRANSFORMATION IN SEARCH SPACE*/
    for (i = 0; i < DIM; i++) {
        tmx[i] = 0.5;
        for (j = 0; j < DIM; j++) {
            tmx[i] += linearTF[i][j] * x[j];
        }
    }

    /* COMPUTATION core*/
    for (i = 0; i < DIM - 1; i++)
    {
        tmp2 = tmx[i] * tmx[i] -tmx[i+1];
        F2 = 100. * tmp2 * tmp2;
        tmp2 = 1 - tmx[i];
        F2 += tmp2 * tmp2;
        tmp += F2 / 4000. - cos(F2);
    }
    Ftrue = 10. + 10. * tmp / (double)(DIM - 1);

    Ftrue += Fadd;
    Fval = Ftrue; /* without noise*/

    res.Fval = Fval;
    res.Ftrue = Ftrue;
    return res;
}