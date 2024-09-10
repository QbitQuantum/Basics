long double
tanl(long double x)
{
	union IEEEl2bits z;
	int i, e0, s;
	double xd[NX], yd[PREC];
	long double hi, lo;

	z.e = x;
	s = z.bits.sign;
	z.bits.sign = 0;

	/* If x = +-0 or x is subnormal, then tan(x) = x. */
	if (z.bits.exp == 0)
		return (x);

	/* If x = NaN or Inf, then tan(x) = NaN. */
	if (z.bits.exp == 32767)
		return ((x - x) / (x - x));

	/* Optimize the case where x is already within range. */
	if (z.e < M_PI_4) {
		hi = __kernel_tanl(z.e, 0, 0);
		return (s ? -hi : hi);
	}

	/* Split z.e into a 24-bit representation. */
	e0 = ilogbl(z.e) - 23;
	z.e = scalbnl(z.e, -e0);
	for (i = 0; i < NX; i++) {
		xd[i] = (double)((int32_t)z.e);
		z.e = (z.e - xd[i]) * two24;
	}
	
	/* yd contains the pieces of xd rem pi/2 such that |yd| < pi/4. */
	e0 = __kernel_rem_pio2(xd, yd, e0, NX, PREC);

#if PREC == 2
	hi = (long double)yd[0] + yd[1];
	lo = yd[1] - (hi - yd[0]);
#else /* PREC == 3 */
	long double t;
	t = (long double)yd[2] + yd[1];
	hi = t + yd[0];
	lo = yd[0] - (hi - t);
#endif

	switch (e0 & 3) {
	case 0:
	case 2:
	    hi = __kernel_tanl(hi, lo, 0);
	    break;
	case 1:
	case 3:
	    hi = __kernel_tanl(hi, lo, 1);
	    break;
	}

	return (s ? -hi : hi);
}