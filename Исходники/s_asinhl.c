long double
asinhl(long double x)
{
	long double t, w;
	uint16_t hx, ix;

	ENTERI();
	GET_LDBL_EXPSIGN(hx, x);
	ix = hx & 0x7fff;
	if (ix >= 0x7fff) RETURNI(x+x);	/* x is inf, NaN or misnormal */
	if (ix < BIAS + EXP_TINY) {	/* |x| < TINY, or misnormal */
	    if (huge + x > one) RETURNI(x);	/* return x inexact except 0 */
	}
	if (ix >= BIAS + EXP_LARGE) {	/* |x| >= LARGE, or misnormal */
	    w = logl(fabsl(x))+ln2;
	} else if (ix >= 0x4000) {	/* LARGE > |x| >= 2.0, or misnormal */
	    t = fabsl(x);
	    w = logl(2.0*t+one/(sqrtl(x*x+one)+t));
	} else {		/* 2.0 > |x| >= TINY, or misnormal */
	    t = x*x;
	    w =log1pl(fabsl(x)+t/(one+sqrtl(one+t)));
	}
	RETURNI((hx & 0x8000) == 0 ? w : -w);
}