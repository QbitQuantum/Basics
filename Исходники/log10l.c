long double
log10l(long double x) {
	long double y, z;
	enum fp_direction_type rd;
	int n;

	if (!finitel(x))
		return (x + fabsl(x));	/* x is +-INF or NaN */
	else if (x > zero) {
		n = ilogbl(x);
		if (n < 0)
			n += 1;
		rd = __swapRD(fp_nearest);
		y = n;
		x = scalbnl(x, -n);
		z = y * log10_2lo + ivln10 * logl(x);
		z += y * log10_2hi;
		if (rd != fp_nearest)
			(void) __swapRD(rd);
		return (z);
	} else if (x == zero)	/* -INF */
		return (-one / zero);
	else			/* x <0 , return NaN */
		return (zero / zero);
}