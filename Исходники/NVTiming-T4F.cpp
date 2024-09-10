double NegBinomial(int kk, double rr, double pp)
{
	double log_pmf = 0;

	if ((kk>=0)&&(rr>0)&&(pp>=0)&&(pp<=1))
		log_pmf = lgamma(kk+rr) - lgamma(kk+1) - lgamma(rr)  + log(1-pp)*rr + log(pp)*kk;

	return exp(log_pmf);
}