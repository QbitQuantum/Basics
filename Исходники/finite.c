fpclass_t
fpclass(double x)
{
	int	sign, exp;

	exp = EXPONENT(x);
	sign = SIGNBIT(x);
	if (exp == 0) { /* de-normal or zero */
		if (HIFRACTION(x) || LOFRACTION(x)) /* de-normal */
			return (sign ? FP_NDENORM : FP_PDENORM);
		else
			return (sign ? FP_NZERO : FP_PZERO);
	}
	if (exp == MAXEXP) { /* infinity or NaN */
		if ((HIFRACTION(x) == 0) && (LOFRACTION(x) == 0)) /* infinity */
			return (sign ? FP_NINF : FP_PINF);
		else
			if (QNANBIT(x))
			/* hi-bit of mantissa set - quiet nan */
				return (FP_QNAN);
			else	return (FP_SNAN);
	}
	/* if we reach here we have non-zero normalized number */
	return (sign ? FP_NNORM : FP_PNORM);
}