long double
asinhl(long double x) {
	long double t, w;

	w = fabsl(x);
	if (isnanl(x))
		return (x + x);	/* x is NaN */
	if (w < tiny) {
#ifndef lint
		volatile long double dummy = x + big;	/* inexact if x != 0 */
#endif
		return (x);	/* tiny x */
	} else if (w < big) {
		t = one / w;
		return (copysignl(log1pl(w + w / (t + sqrtl(one + t * t))), x));
	} else
		return (copysignl(logl(w) + ln2, x));
}