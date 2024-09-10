long double complex
csqrtl(long double complex z)
{
	long double complex result;
	long double a, b;
	long double t;
	int scale;

	a = creall(z);
	b = cimagl(z);

	/* Handle special cases. */
	if (z == 0)
		return (cpackl(0, b));
	if (isinf(b))
		return (cpackl(INFINITY, b));
	if (isnan(a)) {
		t = (b - b) / (b - b);	/* raise invalid if b is not a NaN */
		return (cpackl(a, t));	/* return NaN + NaN i */
	}
	if (isinf(a)) {
		/*
		 * csqrt(inf + NaN i)  = inf +  NaN i
		 * csqrt(inf + y i)    = inf +  0 i
		 * csqrt(-inf + NaN i) = NaN +- inf i
		 * csqrt(-inf + y i)   = 0   +  inf i
		 */
		if (signbit(a))
			return (cpackl(fabsl(b - b), copysignl(a, b)));
		else
			return (cpackl(a, copysignl(b - b, b)));
	}
	/*
	 * The remaining special case (b is NaN) is handled just fine by
	 * the normal code path below.
	 */

	/* Scale to avoid overflow. */
	if (fabsl(a) >= THRESH || fabsl(b) >= THRESH) {
		a *= 0.25;
		b *= 0.25;
		scale = 1;
	} else {
		scale = 0;
	}

	/* Algorithm 312, CACM vol 10, Oct 1967. */
	if (a >= 0) {
		t = sqrtl((a + hypotl(a, b)) * 0.5);
		result = cpackl(t, b / (2 * t));
	} else {
		t = sqrtl((-a + hypotl(a, b)) * 0.5);
		result = cpackl(fabsl(b) / (2 * t), copysignl(t, b));
	}

	/* Rescale. */
	if (scale)
		return (result * 2);
	else
		return (result);
}