uint_fast64_t fp64enc(fp64_t input)
{
    fp64_t d_mant;
    unsigned int u_exp;
    uint_fast64_t u_mant;
    bool neg;
    int s_exp;
    uint_fast64_t bytes;

    switch (fpclassify(input)) {
    default:
	abort();
	break;

    case FP_ZERO:
	neg = signbit(input);
	u_mant = 0;
	u_exp = 0;
	break;

    case FP_INFINITE:
	neg = signbit(input);
	u_mant = 0;
	u_exp = EXPONENT_MASK;
	break;

    case FP_NAN:
	neg = false;
	u_mant = 1;
	u_exp = EXPONENT_MASK;
	break;

    case FP_SUBNORMAL:
    case FP_NORMAL:
	/* Handle normal and subnormal together.  The number might be
	   one class for double, but another for binary64. */

	/* Decompose the input into a significand (mantissa + 1) and
	   an exponent. */
	d_mant = XORP_FP64(frexp)(input, &s_exp);

	/* Extract the sign bit from the mantissa. */
	neg = signbit(input);
	d_mant = XORP_FP64(fabs)(d_mant);

	/* Offset the exponent so it can be represented as an unsigned
	   value. */
	s_exp += EXPONENT_BIAS;

	/* Now we find out whether the number we represent is normal,
	   subnormal, or overflows binary64. */
	if (s_exp >= (long) EXPONENT_MASK) {
	    /* The number is too big for binary64, so use the maximum
	       value. */
	    u_mant = MANTISSA_MASK;
	    u_exp = EXPONENT_MASK - 1u;
	} else if (s_exp <= 0) {
	    /* The number is subnormal in binary64. */

	    /* Shift the mantissa so that it's exponent would be 0. */
	    u_mant = XORP_FP64(ldexp)(d_mant, MANTISSA_BIT);

	    u_mant >>= -s_exp;
	    u_exp = 0;
	} else {