double qpois(double p, double lambda, int lower_tail, int log_p)
{
    double mu, sigma, gamma, z, y;
#ifdef IEEE_754
    if (ISNAN(p) || ISNAN(lambda))
	return p + lambda;
#endif
    if(!R_FINITE(lambda))
	ML_ERR_return_NAN;
    if(lambda < 0) ML_ERR_return_NAN;
    R_Q_P01_check(p);
    if(lambda == 0) return 0;
    if(p == R_DT_0) return 0;
    if(p == R_DT_1) return ML_POSINF;

    mu = lambda;
    sigma = sqrt(lambda);
    /* gamma = sigma; PR#8058 should be kurtosis which is mu^-0.5 */
    gamma = 1.0/sigma;

    /* Note : "same" code in qpois.c, qbinom.c, qnbinom.c --
     * FIXME: This is far from optimal [cancellation for p ~= 1, etc]: */
    if(!lower_tail || log_p) {
	p = R_DT_qIv(p); /* need check again (cancellation!): */
	if (p == 0.) return 0;
	if (p == 1.) return ML_POSINF;
    }
    /* temporary hack --- FIXME --- */
    if (p + 1.01*DBL_EPSILON >= 1.) return ML_POSINF;

    /* y := approx.value (Cornish-Fisher expansion) :  */
    z = qnorm(p, 0., 1., /*lower_tail*/TRUE, /*log_p*/FALSE);
#ifdef HAVE_NEARBYINT
    y = nearbyint(mu + sigma * (z + gamma * (z*z - 1) / 6));
#else
    y = round(mu + sigma * (z + gamma * (z*z - 1) / 6));
#endif

    z = ppois(y, lambda, /*lower_tail*/TRUE, /*log_p*/FALSE);

    /* fuzz to ensure left continuity; 1 - 1e-7 may lose too much : */
    p *= 1 - 64*DBL_EPSILON;

    /* If the mean is not too large a simple search is OK */
    if(lambda < 1e5) return do_search(y, &z, p, lambda, 1);
    /* Otherwise be a bit cleverer in the search */
    {
	double incr = floor(y * 0.001), oldincr;
	do {
	    oldincr = incr;
	    y = do_search(y, &z, p, lambda, incr);
	    incr = fmax2(1, floor(incr/100));
	} while(oldincr > 1 && incr > lambda*1e-15);
	return y;
    }
}