double
ceil(double x)
{

#if	defined(__IEEE_FP__)
	if (_isNaN(x)) {
		errno = EDOM;
		return x;		/* NaN: domain error, return NaN */
	}
	if (_isInfinity(x))
		return x;		/* [+-]Infinity: no error, return x */
#endif	/* defined(__IEEE_FP__) */

	return (modf(x, &x) > 0.0) ? x + 1.0 : x;
}