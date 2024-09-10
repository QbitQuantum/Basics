double
modf(double value, double *iptr)
{
	DOUBLE u;
	register int exp;
#if	defined(__IEEE_DP_FP__)
	register int n;
#endif	/* defined(__IEEE_DP_FP__) */

	/* Special cases: NaN and infinities. */
	if (_isNaN(value)) {
		errno = EDOM;		/* NaN: domain error */
		*iptr = value;		/* integer part is NaN */
		return value;		/* fractional part NaN */
	} else if (_isInfinity(value)) {
		*iptr = value;
		return 0.0;		/* [+-]Infinity: no error, fraction is 0 */
	}

	/* Truncation is easy if value fits in a long. */
	if (value >= (double)LONG_MIN && value <= (double)LONG_MAX) {
		*iptr = (double)(long)value;	/* truncate to integer part */
		return value - *iptr;		/* return fractional part */
	}

	/* If the unbiased exponent is large, there are no fraction bits. */
	u.d = value;
	exp = u.D.exponent - EXP_BIAS;
	if (exp >= DBL_MANT_DIG) {
		*iptr = value;
		return 0.;
	}

#if	defined(__IEEE_DP_FP__)
	/*
	 * Last resort: brute force.
	 * This code is required only for double precision representation;
	 * for single precision, value < LONG_MIN || value > LONG_MAX
	 * guarantees that exp >= DBL_MANT_DIG (i.e., there are
	 * more bits in a long than in the significand).
	 * Shift the significand right by n = DBL_MANT_DIG - 1 - exp bits,
	 * then shift it left by n bits, to clobber the fraction bits,
	 * leaving only the integer bits.
	 * Finally, subtract from the original value to get the fraction.
	 */
	n = DBL_MANT_DIG - 1 - exp;		/* shift count */
	if (n < CHAR_BIT * sizeof(unsigned long)) {
		/* Shift by fewer bits than a long; high unchanged. */
		u.D.frac_low = (u.D.frac_low >> n) << n;
	} else {