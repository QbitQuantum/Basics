/* see https://en.wikipedia.org/wiki/Chebyshev_polynomials */
double nsl_sf_poly_chebyshev_T(int n, double x) {
	if(fabs(x) <= 1)
		return cos(n*acos(x));
	else if (x > 1)
		return cosh(n*acosh(x));
	else 
		return pow(-1.,n)*cosh(n*acosh(-x));
}