long double probability_functions::power_law_inverse(long double probability)
{
	long double d0, rho, lambda;

#if D0_1
	d0 = 1;
#endif

#if RHO_0_5
	rho = 0.5;
#endif
#if RHO_0_7
	rho = 0.7;
#endif
#if RHO_0_9
	rho = 0.9;
#endif

#if LAMBDA_0_75
	lambda = 0.75;
#endif
#if LAMBDA_1
	lambda = 1;
#endif
#if LAMBDA_1_25
	lambda = 1.25;
#endif

	//return (powl(rho / probability, 1.0 / lambda) - d0) / 10;
	return powl(rho / probability, 1 / lambda) - d0;

	return powl(rho / (probability + 0.1), 1 / lambda) - d0;
}