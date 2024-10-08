LDOUBLE attribute_hidden
pnbeta_raw(double x, double o_x, double a, double b, double ncp)
{
    /* o_x  == 1 - x  but maybe more accurate */

    /* change errmax and itrmax if desired;
     * original (AS 226, R84) had  (errmax; itrmax) = (1e-6; 100) */
    const static double errmax = 1.0e-9;
    const int    itrmax = 10000;  /* 100 is not enough for pf(ncp=200)
				     see PR#11277 */

    double a0, lbeta, c, errbd, x0, temp, tmp_c;
    int j, ierr;

    LDOUBLE ans, ax, gx, q, sumq;

    if (ncp < 0. || a <= 0. || b <= 0.) ML_ERR_return_NAN;

    if(x < 0. || o_x > 1. || (x == 0. && o_x == 1.)) return 0.;
    if(x > 1. || o_x < 0. || (x == 1. && o_x == 0.)) return 1.;

    c = ncp / 2.;

	/* initialize the series */

    x0 = floor(fmax2(c - 7. * sqrt(c), 0.));
    a0 = a + x0;
    lbeta = lgammafn(a0) + lgammafn(b) - lgammafn(a0 + b);
    /* temp = pbeta_raw(x, a0, b, TRUE, FALSE), but using (x, o_x): */
    bratio(a0, b, x, o_x, &temp, &tmp_c, &ierr, FALSE);

    gx = exp(a0 * log(x) + b * (x < .5 ? log1p(-x) : log(o_x))
	     - lbeta - log(a0));
    if (a0 > a)
	q = exp(-c + x0 * log(c) - lgammafn(x0 + 1.));
    else
	q = exp(-c);

    sumq = 1. - q;
    ans = ax = q * temp;

	/* recurse over subsequent terms until convergence is achieved */
    j = (int) x0;
    do {
	j++;
	temp -= (double) gx;
	gx *= x * (a + b + j - 1.) / (a + j);
	q *= c / j;
	sumq -= q;
	ax = temp * q;
	ans += ax;
	errbd = (double)((temp - gx) * sumq);
    }
    while (errbd > errmax && j < itrmax + x0);

    if (errbd > errmax)
	ML_ERROR(ME_PRECISION, "pnbeta");
    if (j >= itrmax + x0)
	ML_ERROR(ME_NOCONV, "pnbeta");

    return ans;
}