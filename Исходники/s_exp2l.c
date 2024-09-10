/*
 * exp2l(x): compute the base 2 exponential of x
 *
 * Accuracy: Peak error < 0.511 ulp.
 *
 * Method: (equally-spaced tables)
 *
 *   Reduce x:
 *     x = 2**k + y, for integer k and |y| <= 1/2.
 *     Thus we have exp2l(x) = 2**k * exp2(y).
 *
 *   Reduce y:
 *     y = i/TBLSIZE + z for integer i near y * TBLSIZE.
 *     Thus we have exp2(y) = exp2(i/TBLSIZE) * exp2(z),
 *     with |z| <= 2**-(TBLBITS+1).
 *
 *   We compute exp2(i/TBLSIZE) via table lookup and exp2(z) via a
 *   degree-6 minimax polynomial with maximum error under 2**-69.
 *   The table entries each have 104 bits of accuracy, encoded as
 *   a pair of double precision values.
 */
long double
exp2l(long double x)
{
	union IEEEl2bits u, v;
	long double r, z;
	long double twopk = 0, twopkp10000 = 0;
	uint32_t hx, ix, i0;
	int k;

	/* Filter out exceptional cases. */
	u.e = x;
	hx = u.xbits.expsign;
	ix = hx & EXPMASK;
	if (ix >= BIAS + 14) {		/* |x| >= 16384 or x is NaN */
		if (ix == BIAS + LDBL_MAX_EXP) {
			if (u.xbits.man != 1ULL << 63 || (hx & 0x8000) == 0)
				return (x + x);	/* x is +Inf or NaN */
			else
				return (0.0);	/* x is -Inf */
		}
		if (x >= 16384)
			return (huge * huge);	/* overflow */
		if (x <= -16446)
			return (twom10000 * twom10000);	/* underflow */
	} else if (ix <= BIAS - 66) {		/* |x| < 0x1p-66 */
		return (1.0 + x);
	}

#ifdef __i386__
	/*
	 * The default precision on i386 is 53 bits, so long doubles are
	 * broken. Call exp2() to get an accurate (double precision) result.
	 */
	if (fpgetprec() != FP_PE)
		return (exp2(x));
#endif

	/*
	 * Reduce x, computing z, i0, and k. The low bits of x + redux
	 * contain the 16-bit integer part of the exponent (k) followed by
	 * TBLBITS fractional bits (i0). We use bit tricks to extract these
	 * as integers, then set z to the remainder.
	 *
	 * Example: Suppose x is 0xabc.123456p0 and TBLBITS is 8.
	 * Then the low-order word of x + redux is 0x000abc12,
	 * We split this into k = 0xabc and i0 = 0x12 (adjusted to
	 * index into the table), then we compute z = 0x0.003456p0.
	 *
	 * XXX If the exponent is negative, the computation of k depends on
	 *     '>>' doing sign extension.
	 */
	u.e = x + redux;
	i0 = u.bits.manl + TBLSIZE / 2;
	k = (int)i0 >> TBLBITS;
	i0 = (i0 & (TBLSIZE - 1)) << 1;
	u.e -= redux;
	z = x - u.e;
	v.xbits.man = 1ULL << 63;
	if (k >= LDBL_MIN_EXP) {
		v.xbits.expsign = LDBL_MAX_EXP - 1 + k;
		twopk = v.e;
	} else {
		v.xbits.expsign = LDBL_MAX_EXP - 1 + k + 10000;
		twopkp10000 = v.e;
	}

	/* Compute r = exp2l(y) = exp2lt[i0] * p(z). */
	long double t_hi = tbl[i0];
	long double t_lo = tbl[i0 + 1];
	/* XXX This gives > 1 ulp errors outside of FE_TONEAREST mode */
	r = t_lo + (t_hi + t_lo) * z * (P1 + z * (P2 + z * (P3 + z * (P4
	    + z * (P5 + z * P6))))) + t_hi;

	/* Scale by 2**k. */
	if (k >= LDBL_MIN_EXP) {
		if (k == LDBL_MAX_EXP)
			return (r * 2.0 * 0x1p16383L);
		return (r * twopk);
	} else {
		return (r * twopkp10000 * twom10000);
	}
}