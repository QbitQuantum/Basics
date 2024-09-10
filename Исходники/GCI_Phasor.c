int    GCI_Phasor(float xincr, float y[], int fit_start, int fit_end,
							  float *Z, float *U, float *V, float *taup, float *taum, float *tau, float *fitted, float *residuals,
							  float *chisq)
{
    // Z must contain a bg estimate
	// fitted and residuals must be arrays big enough to hold possibly fit_end floats.

	int   i, ret = PHASOR_ERR_NO_ERROR, nBins;
	float *data, u, v, A, w, I, Ifit, bg, chisq_local, res, sigma2;

	data = &(y[fit_start]);	
	nBins = (fit_end - fit_start);
	bg = *Z;
    if (!data)
        return (PHASOR_ERR_INVALID_DATA);
    if (nBins<0)
        return (PHASOR_ERR_INVALID_WINDOW);

	// rep frequency, lets use the period of the measurement, but we can stay in the units of bins
	w = 2.0f*3.1415926535897932384626433832795028841971f/(float)nBins; //2.0*PI/(float)nBins;
	setPhasorPeriod((float)nBins*xincr); // store the real phasor period used for future external use.

	// integral over data
	for (i=0, I=0.0f; i<nBins; i++) 
		I += (data[i]-bg);

	// Phasor coords
    // Take care that values correspond to the centre of the bin, hence i+0.5
	for (i=0, u=0.0f; i<nBins; i++) 
		u += (data[i]-bg) * cosf(w*((float)i+0.5f));
	u /= I;

	for (i=0, v=0.0f; i<nBins; i++) 
		v += (data[i]-bg) * sinf(w*((float)i+0.5f));
	v /= I;

	// taus, convert now to real time with xincr
	*taup = (xincr/w) * (v/u);
	*taum = (xincr/w) * sqrtf(1.0f/(u*u + v*v) - 1.0f);

	*tau = ((*taup) + (*taum))/2.0f;

	*U = u;
	*V = v;

	/* Now calculate the fitted curve and chi-squared if wanted. */
	if (fitted == NULL)
		return 0;

	memset(fitted, 0, (size_t)fit_end * sizeof(float));
	memset(residuals, 0, (size_t)fit_end * sizeof(float));
	// Madison report some "memory issue", and replaced the 2 line above with new arrays.
	// Not sure what that was but I breaks the filling of the fitted array, probably not allocating the arrays before calling

	// integral over nominal fit data
	for (Ifit=0.0f, i=fit_start; i<fit_end; i++) 
		Ifit += expf((float)(-(i-fit_start))*xincr/(*tau));
	// Estimate A
	A = I / Ifit;

	// Calculate fit
	for (i=fit_start; i<fit_end; i++){
		fitted[i] = bg + A * expf((float)(-(i-fit_start))*xincr/(*tau));
	}
	// OK, so now fitted contains our data for the timeslice of interest.
	// We can calculate a chisq value and plot the graph, along with
	// the residuals.

	if (residuals == NULL && chisq == NULL)
		return 0;

	chisq_local = 0.0f;
	for (i=0; i<fit_start; i++) {
		res = y[i]-fitted[i];
		if (residuals != NULL)
			residuals[i] = res;
	}


//	case NOISE_POISSON_FIT:
		/* Summation loop over all data */
		for (i=fit_start ; i<fit_end; i++) {
			res = y[i] - fitted[i];
			if (residuals != NULL)
				residuals[i] = res;
			/* don't let variance drop below 1 */
			sigma2 = (fitted[i] > 1 ? 1.0f/fitted[i] : 1.0f);
			chisq_local += res * res * sigma2;
		}

	if (chisq != NULL)
		*chisq = chisq_local;

	return (ret);
}