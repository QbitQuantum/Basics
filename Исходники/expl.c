long double expl(long double x)
{
	long double px, xx;
	int k;

	if (isnan(x))
		return x;
	if (x > 11356.5234062941439488L) /* x > ln(2^16384 - 0.5) */
		return x * 0x1p16383L;
	if (x < -11399.4985314888605581L) /* x < ln(2^-16446) */
		return -0x1p-16445L/x;

	/* Express e**x = e**f 2**k
	 *   = e**(f + k ln(2))
	 */
	px = floorl(LOG2E * x + 0.5);
	k = px;
	x -= px * LN2HI;
	x -= px * LN2LO;

	/* rational approximation of the fractional part:
	 * e**x =  1 + 2x P(x**2)/(Q(x**2) - x P(x**2))
	 */
	xx = x * x;
	px = x * __polevll(xx, P, 2);
	x = px/(__polevll(xx, Q, 3) - px);
	x = 1.0 + 2.0 * x;
	return scalbnl(x, k);
}