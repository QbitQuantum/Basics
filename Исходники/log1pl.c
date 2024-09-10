long double log1pl(long double xm1)
{
	long double x, y, z;
	int e;

	if (isnan(xm1))
		return xm1;
	if (xm1 == INFINITY)
		return xm1;
	if (xm1 == 0.0)
		return xm1;

	x = xm1 + 1.0;

	/* Test for domain errors.  */
	if (x <= 0.0) {
		if (x == 0.0)
			return -1/x; /* -inf with divbyzero */
		return 0/0.0f; /* nan with invalid */
	}

	/* Separate mantissa from exponent.
	   Use frexp so that denormal numbers will be handled properly.  */
	x = frexpl(x, &e);

	/* logarithm using log(x) = z + z^3 P(z)/Q(z),
	   where z = 2(x-1)/x+1)  */
	if (e > 2 || e < -2) {
		if (x < SQRTH) { /* 2(2x-1)/(2x+1) */
			e -= 1;
			z = x - 0.5;
			y = 0.5 * z + 0.5;
		} else { /*  2 (x-1)/(x+1)   */
			z = x - 0.5;
			z -= 0.5;
			y = 0.5 * x  + 0.5;
		}
		x = z / y;
		z = x*x;
		z = x * (z * __polevll(z, R, 3) / __p1evll(z, S, 3));
		z = z + e * C2;
		z = z + x;
		z = z + e * C1;
		return z;
	}

	/* logarithm using log(1+x) = x - .5x**2 + x**3 P(x)/Q(x) */
	if (x < SQRTH) {
		e -= 1;
		if (e != 0)
			x = 2.0 * x - 1.0;
		else
			x = xm1;
	} else {
		if (e != 0)
			x = x - 1.0;
		else
			x = xm1;
	}
	z = x*x;
	y = x * (z * __polevll(x, P, 6) / __p1evll(x, Q, 6));
	y = y + e * C2;
	z = y - 0.5 * z;
	z = z + x;
	z = z + e * C1;
	return z;
}