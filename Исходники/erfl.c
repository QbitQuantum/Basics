static long double expx2l (long double x)
{
	long double u, u1, m, f;

	x = fabsl (x);
	/* Represent x as an exact multiple of M plus a residual.
	   M is a power of 2 chosen so that exp(m * m) does not overflow
	   or underflow and so that |x - m| is small.  */
	m = MINV * floorl(M * x + 0.5L);
	f = x - m;

	/* x^2 = m^2 + 2mf + f^2 */
	u = m * m;
	u1 = 2 * m * f  +  f * f;

	if ((u + u1) > MAXLOGL)
		return (INFINITYL);

	/* u is exact, u1 is small.  */
	u = expl(u) * expl(u1);
	return (u);
}