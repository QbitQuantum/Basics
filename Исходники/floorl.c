long double
floorl(long double x) {
	long double t;

	if (!finitel(x))
		return (x + x);
	t = rintl(x);
	if (t <= x)
		return (t);		/* already floor(x) */
	else 				/* x < t case: return t-1  */
	    return (copysignl(t - qone, x));
}