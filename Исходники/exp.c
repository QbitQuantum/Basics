double exp(double x)
{
	double_t hi, lo, c, xx, y;
	int k, sign;
	uint32_t hx;

	GET_HIGH_WORD(hx, x);
	sign = hx>>31;
	hx &= 0x7fffffff;  /* high word of |x| */

	/* special cases */
	if (hx >= 0x4086232b) {  /* if |x| >= 708.39... */
		if (isnan(x))
			return x;
		if (x > 709.782712893383973096) {
			/* overflow if x!=inf */
			x *= 0x1p1023;
			return x;
		}
		if (x < -708.39641853226410622) {
			/* underflow if x!=-inf */
			FORCE_EVAL((float)(-0x1p-149/x));
			if (x < -745.13321910194110842)
				return 0;
		}
	}

	/* argument reduction */
	if (hx > 0x3fd62e42) {  /* if |x| > 0.5 ln2 */
		if (hx >= 0x3ff0a2b2)  /* if |x| >= 1.5 ln2 */
			k = (int)(invln2*x + half[sign]);
		else
			k = 1 - sign - sign;
		hi = x - k*ln2hi;  /* k*ln2hi is exact here */
		lo = k*ln2lo;
		x = hi - lo;
	} else if (hx > 0x3e300000)  {  /* if |x| > 2**-28 */
		k = 0;
		hi = x;
		lo = 0;
	} else {
		/* inexact if x!=0 */
		FORCE_EVAL(0x1p1023 + x);
		return 1 + x;
	}

	/* x is now in primary range */
	xx = x*x;
	c = x - xx*(__EXP_P1+xx*(__EXP_P2+xx*(__EXP_P3+xx*(__EXP_P4+xx*__EXP_P5))));
	y = 1 + (x*c/(2-c) - lo + hi);
	if (k == 0)
		return y;
	return scalbn(y, k);
}