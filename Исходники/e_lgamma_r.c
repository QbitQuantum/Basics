static double
sin_pi(double x)
{
	double y,z;
	int n,ix;

	GET_HIGH_WORD(ix,x);
	ix &= 0x7fffffff;

	if(ix<0x3fd00000) return __sin(pi*x);
	y = -x;		/* x is assume negative */

    /*
     * argument reduction, make sure inexact flag not raised if input
     * is an integer
     */
	z = __floor(y);
	if(z!=y) {				/* inexact anyway */
	    y  *= 0.5;
	    y   = 2.0*(y - __floor(y));		/* y = |x| mod 2.0 */
	    n   = (int) (y*4.0);
	} else {
	    if(ix>=0x43400000) {
		y = zero; n = 0;                 /* y must be even */
	    } else {
		if(ix<0x43300000) z = y+two52;	/* exact */
		GET_LOW_WORD(n,z);
		n &= 1;
		y  = n;
		n<<= 2;
	    }
	}
	switch (n) {
	    case 0:   y =  __sin(pi*y); break;
	    case 1:
	    case 2:   y =  __cos(pi*(0.5-y)); break;
	    case 3:
	    case 4:   y =  __sin(pi*(one-y)); break;
	    case 5:
	    case 6:   y = -__cos(pi*(y-1.5)); break;
	    default:  y =  __sin(pi*(y-2.0)); break;
	    }
	return -y;
}