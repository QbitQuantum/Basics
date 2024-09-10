double nsl_stats_quantile_sorted(const double d[], size_t stride, size_t n, double p, nsl_stats_quantile_type type) {

	switch(type) {
	case nsl_stats_quantile_type1:
		if (p == 0.0)
			return d[0];
		else
			return d[((int)ceil(n*p)-1)*stride];
	case nsl_stats_quantile_type2:
		if (p == 0.0)
                        return d[0];
		else if (p == 1.0)
                        return d[(n-1)*stride];
		else
			return (d[((int)ceil(n*p)-1)*stride]+d[((int)ceil(n*p+1)-1)*stride])/2.;
	case nsl_stats_quantile_type3:
		if(p <= 0.5/n)
			return d[0];
		else
			return d[(lrint(n*p)-1)*stride];
	case nsl_stats_quantile_type4:
		if(p < 1./n)
			return d[0];
		else if (p == 1.0)
			return d[(n-1)*stride];
		else {
			int i = floor(n*p);
			return d[(i-1)*stride]+(n*p-i)*(d[i*stride]-d[(i-1)*stride]);	
		}
	case nsl_stats_quantile_type5:
		if(p < 0.5/n)
			return d[0];
		else if (p >= (n-0.5)/n)
			return d[(n-1)*stride];
		else {
			int i = floor(n*p+0.5);
			return d[(i-1)*stride]+(n*p+0.5-i)*(d[i*stride]-d[(i-1)*stride]);	
		}
	case nsl_stats_quantile_type6:
		if(p < 1./(n+1.))
			return d[0];
		else if (p > n/(n+1.))
			return d[(n-1)*stride];
		else {
			int i = floor((n+1)*p);
			return d[(i-1)*stride]+((n+1)*p-i)*(d[i*stride]-d[(i-1)*stride]);	
		}
	case nsl_stats_quantile_type7:
		if (p == 1.0)
                        return d[(n-1)*stride];
                else {
			int i = floor((n-1)*p+1);
			return d[(i-1)*stride]+((n-1)*p+1-i)*(d[i*stride]-d[(i-1)*stride]);	
		}
	case nsl_stats_quantile_type8:
		if (p < 2./3./(n+1./3.))
			return d[0];
		else if (p >= (n-1./3.)/(n+1./3.))
			return d[(n-1)*stride];
		else {
			int i = floor((n+1./3.)*p+1./3.);
			return d[(i-1)*stride]+((n+1./3.)*p+1./3.-i)*(d[i*stride]-d[(i-1)*stride]);	
		}
	case nsl_stats_quantile_type9:
		if (p < 5./8./(n+1./4.))
			return d[0];
		else if (p >= (n-3./8.)/(n+1./4.))
			return d[(n-1)*stride];
		else {
			int i = floor((n+1./4.)*p+3./8.);
			return d[(i-1)*stride]+((n+1./4.)*p+3./8.-i)*(d[i*stride]-d[(i-1)*stride]);	
		}
	}

	return 0;
}