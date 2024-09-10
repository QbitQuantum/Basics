double
hypot(double x, double y)
{
	static double const zero=0;
	static double const one=1;
	static double const small=1.0E-18;	/* fl(1+small)==1 */
	static int const ibig=30;	/* fl(1+2**(2*ibig))==1 */
	double t;
	double r;
	int exp;

	if(finite(x)) {
	    if(finite(y)) {
		x=copysign(x,one);
		y=copysign(y,one);
		if(y > x) {
		    t=x; x=y; y=t;
		}
		if(x == zero) return(zero);
		if(y == zero) return(x);
		exp= logb(x);
		if(exp-(int)logb(y) > ibig ) {
		    /* raise inexact flag and return |x| */
		    (void volatile)(one+small);
		    return(x);
		}

	    /* start computing sqrt(x^2 + y^2) */
		r=x-y;
		if(r>y) { 	/* x/y > 2 */
		    r=x/y;
		    r=r+sqrt(one+r*r);
		} else {		/* 1 <= x/y <= 2 */
		    r/=y; t=r*(r+2.0);
		    r+=t/(sqrt2+sqrt(2.0+t));
		    r+=r2p1lo; r+=r2p1hi;
		}

		r=y/r;
		return(x+r);

	    }

	    else if(y==y)   	   /* y is +-INF */
		     return(copysign(y,one));
	    else
		     return(y);	   /* y is NaN and x is finite */

	} else if(x==x) {
	    return (copysign(x,one)); /* x is +-INF */
	} else if(finite(y)) {
	    return(x);		   /* x is NaN, y is finite */
#if !defined(vax)&&!defined(tahoe)
	} else if(y!=y) {
	    return(y);  /* x and y is NaN */
#endif	/* !defined(vax)&&!defined(tahoe) */
	} else {
	    return(copysign(y,one));   /* y is INF */
	}
}