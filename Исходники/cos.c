double
cos(double x)
{
	double y;

#if	defined(__IEEE_FP__)
	if (_isNaN(x)) {
		errno = EDOM;
		return x;		/* NaN: domain error, return NaN */
	} else if (_isInfinity(x)) {
		errno = EDOM;
		return 1.0;		/* [+-]Infinity: domain error, return 1.0 */
	}
#endif	/* defined(__IEEE_FP__) */

	if (x < -PI || x > PI) {
		x = fmod(x, TWOPI);
		if (x > PI)
			x = x - TWOPI;
		 else if (x < -PI)
			x = x + TWOPI;
	}
	if (x > HALFPI)
		return -(cos(x - PI));
	else if (x < -HALFPI)
		return -(cos(x + PI));
	else if (x > FOURTHPI)
		return sin(HALFPI - x);
	else if (x < -FOURTHPI)
		return sin(HALFPI + x);
	else if (x < COS_MIN && x > -COS_MIN)
		return sqrt(1.0 - (x * x));
	y = x / FOURTHPI;
	return _poly(ORDERP, P, y * y) / _poly(ORDERQ, Q, y * y);
}