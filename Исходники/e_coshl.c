long double
coshl(long double x)
{
	long double t,w;
	int32_t ex;
	u_int32_t mx,lx;

    /* High word of |x|. */
	GET_LDOUBLE_WORDS(ex,mx,lx,x);
	ex &= 0x7fff;

    /* x is INF or NaN */
	if(ex==0x7fff) return x*x;

    /* |x| in [0,0.5*ln2], return 1+expm1l(|x|)^2/(2*expl(|x|)) */
	if(ex < 0x3ffd || (ex == 0x3ffd && mx < 0xb17217f7u)) {
	    t = expm1l(fabsl(x));
	    w = one+t;
	    if (ex<0x3fbc) return w;	/* cosh(tiny) = 1 */
	    return one+(t*t)/(w+w);
	}

    /* |x| in [0.5*ln2,22], return (exp(|x|)+1/exp(|x|)/2; */
	if (ex < 0x4003 || (ex == 0x4003 && mx < 0xb0000000u)) {
		t = expl(fabsl(x));
		return half*t+half/t;
	}

    /* |x| in [22, ln(maxdouble)] return half*exp(|x|) */
	if (ex < 0x400c || (ex == 0x400c && mx < 0xb1700000u))
		return half*expl(fabsl(x));

    /* |x| in [log(maxdouble), log(2*maxdouble)) */
	if (ex == 0x400c && (mx < 0xb174ddc0u
			     || (mx == 0xb174ddc0u && lx < 0x31aec0ebu)))
	{
	    w = expl(half*fabsl(x));
	    t = half*w;
	    return t*w;
	}

    /* |x| >= log(2*maxdouble), cosh(x) overflow */
	return huge*huge;
}