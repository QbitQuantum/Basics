long double
hypotl(long double x, long double y)
{
	long double a=x,b=y,t1,t2,y1,y2,w;
	int32_t j,k,ha,hb;

	GET_HIGH_WORD(ha,x);
	ha &= 0x7fff;
	GET_HIGH_WORD(hb,y);
	hb &= 0x7fff;
	if(hb > ha) {a=y;b=x;j=ha; ha=hb;hb=j;} else {a=x;b=y;}
	a = fabsl(a);
	b = fabsl(b);
	if((ha-hb)>DESW(MANT_DIG+7)) {return a+b;} /* x/y > 2**(MANT_DIG+7) */
	k=0;
	if(ha > ESW(MAX_EXP/2-12)) {	/* a>2**(MAX_EXP/2-12) */
	   if(ha >= ESW(MAX_EXP)) {	/* Inf or NaN */
	       man_t manh, manl;
	       /* Use original arg order iff result is NaN; quieten sNaNs. */
	       w = fabsl(x+0.0)-fabsl(y+0.0);
	       GET_LDBL_MAN(manh,manl,a);
	       if (manh == LDBL_NBIT && manl == 0) w = a;
	       GET_LDBL_MAN(manh,manl,b);
	       if (hb >= ESW(MAX_EXP) && manh == LDBL_NBIT && manl == 0) w = b;
	       return w;
	   }
	   /* scale a and b by 2**-(MAX_EXP/2+88) */
	   ha -= DESW(MAX_EXP/2+88); hb -= DESW(MAX_EXP/2+88);
	   k += MAX_EXP/2+88;
	   SET_HIGH_WORD(a,ha);
	   SET_HIGH_WORD(b,hb);
	}
	if(hb < ESW(-(MAX_EXP/2-12))) {	/* b < 2**-(MAX_EXP/2-12) */
	    if(hb <= 0) {		/* subnormal b or 0 */
	        man_t manh, manl;
		GET_LDBL_MAN(manh,manl,b);
		if((manh|manl)==0) return a;
		t1=0;
		SET_HIGH_WORD(t1,ESW(MAX_EXP-2));	/* t1=2^(MAX_EXP-2) */
		b *= t1;
		a *= t1;
		k -= MAX_EXP-2;
	    } else {		/* scale a and b by 2^(MAX_EXP/2+88) */
		ha += DESW(MAX_EXP/2+88);
		hb += DESW(MAX_EXP/2+88);
		k -= MAX_EXP/2+88;
		SET_HIGH_WORD(a,ha);
		SET_HIGH_WORD(b,hb);
	    }
	}
    /* medium size a and b */
	w = a-b;
	if (w>b) {
	    t1 = a;
	    union IEEEl2bits uv;
	    uv.e = t1; uv.bits.manl = 0; t1 = uv.e;
	    t2 = a-t1;
	    w  = sqrtl(t1*t1-(b*(-b)-t2*(a+t1)));
	} else {
	    a  = a+a;
	    y1 = b;
	    union IEEEl2bits uv;
	    uv.e = y1; uv.bits.manl = 0; y1 = uv.e;
	    y2 = b - y1;
	    t1 = a;
	    uv.e = t1; uv.bits.manl = 0; t1 = uv.e;
	    t2 = a - t1;
	    w  = sqrtl(t1*y1-(w*(-w)-(t1*y2+t2*b)));
	}
	if(k!=0) {
	    u_int32_t high;
	    t1 = 1.0;
	    GET_HIGH_WORD(high,t1);
	    SET_HIGH_WORD(t1,high+DESW(k));
	    return t1*w;
	} else return w;
}