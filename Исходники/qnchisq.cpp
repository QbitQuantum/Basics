double qnchisq(double p, double n, double lambda, int lower_tail, int log_p)
{
    const double acu = 1e-12;
    const double Eps = 1e-6; /* must be > acu */

    double ux, lx, nx;

#ifdef IEEE_754
    if (ISNAN(p) || ISNAN(n) || ISNAN(lambda))
        return p + n + lambda;
#endif
    if (!R_FINITE(n)) ML_ERR_return_NAN;

    n = FLOOR(n + 0.5);
    if (n < 1 || lambda < 0) ML_ERR_return_NAN;

    R_Q_P01_check(p);

    if (p == R_DT_0)
        return 0;

    /* Invert pnchisq(.) finding an upper and lower bound;
       then interval halfing : */

    p = R_D_qIv(p);
    if(lower_tail) {
        for(ux = 1.; pnchisq_raw(ux, n, lambda, Eps, 128) < p * (1 + Eps);
            ux *= 2){}
        for(lx = ux; pnchisq_raw(lx, n, lambda, Eps, 128) > p * (1 - Eps);
            lx *= 0.5){}
    }
    else {
        for(ux = 1.; pnchisq_raw(ux, n, lambda, Eps, 128) + p < 1 + Eps;
            ux *= 2){}
        for(lx = ux; pnchisq_raw(lx, n, lambda, Eps, 128) + p > 1 - Eps;
            lx *= 0.5){}
    }
    p = R_D_Lval(p);
    do {
        nx = 0.5 * (lx + ux);
        if (pnchisq_raw(nx, n, lambda, acu, 1000) > p)
            ux = nx;
        else
            lx = nx;
    }
    while ((ux - lx) / nx > acu);
    return 0.5 * (ux + lx);
}