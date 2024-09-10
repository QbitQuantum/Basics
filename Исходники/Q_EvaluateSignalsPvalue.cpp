// constructor for the case treatment and control
Pvalues::Pvalues(int length, int q_min, int q_max, int t_f, int t_r, int c_f, int c_r)
{
	n=2*q_max;
	has_control=true;
	
	// calculate probility of success for treatment and control
	// --------------------------------------------------------
	
	long double lambda_t = (q_max-q_min) * (t_r/(long double)length);
	long double rate_t = (t_f/(long double)length) * (1-expl(-lambda_t));
	p_t = 1 - exp(-rate_t*2);
	
	long double lambda_c = (q_max-q_min) * (c_r/(long double)length);
	long double rate_c = (c_f/(long double)length) * (1-expl(-lambda_c));
	p_c = 1 - exp(-rate_c*2);
	
	// init binomial distribution
	// --------------------------
	
	boost::math::binomial_distribution<long double> BinomialTreatment(n,p_t);
	boost::math::binomial_distribution<long double> BinomialControl(n,p_c);	
	
	// init p-values from -n to n
	// --------------------------
	
	std::map<int, long double> DiffBinom;
	for(int d=-n;d<=n;d++)
	{
		for(int k=0;k<=(n-abs(d));k++)
		{
			if(0<=d)
			{
				DiffBinom[d]=DiffBinom[d]+pdf(BinomialTreatment,(k+abs(d)))*pdf(BinomialControl,k);
			}
			else
			{
				DiffBinom[d]=DiffBinom[d]+pdf(BinomialControl,k+abs(d))*pdf(BinomialTreatment,k);
			}
		}
	}
	
	long double pval=0;
	for(int d=n;d>=-n;d--)
	{
		pval=pval+DiffBinom[d];
		p_values[d]=pval;
		p_values_10log[d]=-log10l(pval);
	}
}