long double
coshl(long double x) {
	long double w, t;

	w = fabsl(x);
	if (!finitel(w))
		return (w + w);	/* x is INF or NaN */
	if (w < thr1) {
		if (w < tinyl)
			return (one + w);	/* inexact+directed rounding */
		t = expm1l(w);
		w = one + t;
		w = one + (t * t) / (w + w);
		return (w);
	}
	if (w < thr2) {
		t = expl(w);
		return (half * (t + one / t));
	}
	if (w <= lnovft)
		return (half * expl(w));
	return (scalbnl(expl((w - lnovft) - lnovlo), 16383));
}