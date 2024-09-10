static double
neg_gam(double x)
{
	int sgn = 1;
	struct Double lg, lsine;
	double y, z;

	y = ceil(x);
	if (y == x)		/* Negative integer. */
		if (_IEEE)
			return ((x - x) / zero);
		else
			return (infnan(ERANGE));
	z = y - x;
	if (z > 0.5)
		z = one - z;
	y = 0.5 * y;
	if (y == ceil(y))
		sgn = -1;
	if (z < .25)
		z = sin(M_PI*z);
	else
		z = cos(M_PI*(0.5-z));
	/* Special case: G(1-x) = Inf; G(x) may be nonzero. */
	if (x < -170) {
		if (x < -190)
			return ((double)sgn*tiny*tiny);
		y = one - x;		/* exact: 128 < |x| < 255 */
		lg = large_gam(y);
		lsine = __log__D(M_PI/z);	/* = TRUNC(log(u)) + small */
		lg.a -= lsine.a;		/* exact (opposite signs) */
		lg.b -= lsine.b;
		y = -(lg.a + lg.b);
		z = (y + lg.a) + lg.b;
		y = __exp__D(y, z);
		if (sgn < 0) y = -y;
		return (y);
	}
	y = one-x;
	if (one-y == x)
		y = tgamma(y);
	else		/* 1-x is inexact */
		y = -x*tgamma(-x);
	if (sgn < 0) y = -y;
	return (M_PI / (y*z));
}