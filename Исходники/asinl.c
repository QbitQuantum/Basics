long double asinl(long double x)
{
	union ldshape u = {x};
	long double z, r, s;
	uint16_t e = u.i.se & 0x7fff;
	int sign = u.i.se >> 15;

	if (e >= 0x3fff) {   /* |x| >= 1 or nan */
		/* asin(+-1)=+-pi/2 with inexact */
		if (x == 1 || x == -1)
			return x*pio2_hi + 0x1p-120f;
		return 0/(x-x);
	}
	if (e < 0x3fff - 1) {  /* |x| < 0.5 */
		if (e < 0x3fff - (LDBL_MANT_DIG+1)/2) {
			/* return x with inexact if x!=0 */
			FORCE_EVAL(x + 0x1p120f);
			return x;
		}
		return x + x*__invtrigl_R(x*x);
	}
	/* 1 > |x| >= 0.5 */
	z = (1.0 - fabsl(x))*0.5;
	s = sqrtl(z);
	r = __invtrigl_R(z);
	if (CLOSETO1(u)) {
		x = pio2_hi - (2*(s+s*r)-pio2_lo);
	} else {
		long double f, c;
		u.f = s;
		CLEARBOTTOM(u);
		f = u.f;
		c = (z - f*f)/(s + f);
		x = 0.5*pio2_hi-(2*s*r - (pio2_lo-2*c) - (0.5*pio2_hi-2*f));
	}
	return sign ? -x : x;
}