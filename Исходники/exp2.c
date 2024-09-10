double
exp2(double x) {
	int	ix, hx, k;
	double	t;

	ix = ((int *)&x)[HIWORD];
	hx = ix & ~0x80000000;

	if (hx >= 0x4090e000) {	/* |x| >= 1080 or x is nan */
		if (hx >= 0x7ff00000) {	/* x is inf or nan */
			if (ix == 0xfff00000 && ((int *)&x)[LOWORD] == 0)
				return (zero);
			return (x * x);
		}
		t = (ix < 0)? tiny : huge;
		return (t * t);
	}

	if (hx < 0x3fe00000) {	/* |x| < 0.5 */
		if (hx < 0x3c000000)
			return (one + x);
		return (exp(ln2 * x));
	}

	k = (int)x;
	if (x != (double)k)
		k = (int)((ix < 0)? x - half : x + half);
	return (scalbn(exp(ln2 * (x - (double)k)), k));
}