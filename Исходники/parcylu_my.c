double for_large_negative(double a, double x)
{
	double d3, d6, v_ax, X, theta, d9, d12;

	const double MY_PI = acos(-1);

	// Abramowitz and Stegun page 690 19.10.13

	d3 = (x*x*x/48.0+a*x/2.0)/a;

	d6 = 3.0*x*x/4.0 - 2.0*a;

	d9 = (-7*x*x*x*x*x*x*x*x*x/5760 - 7*a*x*x*x*x*x*x*x/320 - 49*a*a*x*x*x*x*x/320 
		+ 31*a*a*a*x*x*x/12 - 19*a*a*a*a*x)/(a*a*a);

	d12 = 153*x*x*x*x/8 - 186*a*x*x + 80*a*a;

	// from A/S 19.10.1

	X = sqrt(x*x+4.0*a);

	theta = fabs(x)*X/4.0 + a*asinh(fabs(x)/(2*sqrt(a)));  // notice the fabs()'s I need this to get the correct
																													// theta when x is negative (not completely clear from
	                                                       // A/S I think)

	// A/S 19.10.4

	v_ax = -0.5*log(X) -d3/(X*X*X) + d6/(X*X*X*X*X*X) - d9/(X*X*X*X*X*X*X*X*X)
		+ d12/(X*X*X*X*X*X*X*X*X*X*X*X);


	// from 19.10.3

	return 0.25*log(2*MY_PI) - 0.5*log(th_Gamma(0.5+a)) + theta + v_ax;
}