double complex
csqrt(double complex z)
{
	double complex result;
	double a, b;
	double t;
	int scale;

	a = creal(z);
	b = cimag(z);

	/* Handle special cases. */
	if (z == 0)
		return (cpack(0, b));
	if (isinf(b))
		return (cpack(INFINITY, b));
	if (isnan(a)) {
		t = (b - b) / (b - b);	/* raise invalid if b is not a NaN */
		return (cpack(a, t));	/* return NaN + NaN i */
	}
	if (isinf(a)) {
		/*
		 * csqrt(inf + NaN i)  = inf +  NaN i
		 * csqrt(inf + y i)    = inf +  0 i
		 * csqrt(-inf + NaN i) = NaN +- inf i
		 * csqrt(-inf + y i)   = 0   +  inf i
		 */
		if (signbit(a))
			return (cpack(fabs(b - b), copysign(a, b)));
		else
			return (cpack(a, copysign(b - b, b)));
	}
	/*
	 * The remaining special case (b is NaN) is handled just fine by
	 * the normal code path below.
	 */

	/* Scale to avoid overflow. */
	if (fabs(a) >= THRESH || fabs(b) >= THRESH) {
		a *= 0.25;
		b *= 0.25;
		scale = 1;
	} else {
		scale = 0;
	}

	/* Algorithm 312, CACM vol 10, Oct 1967. */
	if (a >= 0) {
		t = sqrt((a + hypot(a, b)) * 0.5);
		result = cpack(t, b / (2 * t));
	} else {
		t = sqrt((-a + hypot(a, b)) * 0.5);
		result = cpack(fabs(b) / (2 * t), copysign(t, b));
	}

	/* Rescale. */
	if (scale)
		return (result * 2);
	else
		return (result);
}