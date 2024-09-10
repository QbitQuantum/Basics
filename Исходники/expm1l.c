long double expm1l(long double x)
{
	long double px, qx, xx;
	int k;

	/* Overflow.  */
	if (x > MAXLOGL)
		return huge*huge;  /* overflow */
	if (x == 0.0)
		return x;
	/* Minimum value.*/
	if (x < minarg)
		return -1.0;

	xx = C1 + C2;
	/* Express x = ln 2 (k + remainder), remainder not exceeding 1/2. */
	px = floorl(0.5 + x / xx);
	k = px;
	/* remainder times ln 2 */
	x -= px * C1;
	x -= px * C2;

	/* Approximate exp(remainder ln 2).*/
	px = (((( P4 * x + P3) * x + P2) * x + P1) * x + P0) * x;
	qx = (((( x + Q4) * x + Q3) * x + Q2) * x + Q1) * x + Q0;
	xx = x * x;
	qx = x + (0.5 * xx + xx * px / qx);

	/* exp(x) = exp(k ln 2) exp(remainder ln 2) = 2^k exp(remainder ln 2).
	 We have qx = exp(remainder ln 2) - 1, so
	 exp(x) - 1  =  2^k (qx + 1) - 1  =  2^k qx + 2^k - 1.  */
	px = scalbnl(1.0, k);
	x = px * qx + (px - 1.0);
	return x;
}