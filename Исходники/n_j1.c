double
y1(double x)
{
	double z, s, c, ss, cc, u, v;
    /* if Y1(NaN) is NaN, Y1(-inf) is NaN, Y1(inf) is 0 */
	if (!finite(x)) {
		if (!_IEEE) return (infnan(EDOM));
		else if (x < 0)
			return(zero/zero);
		else if (x > 0)
			return (0);
		else
			return(x);
	}
	if (x <= 0) {
		if (_IEEE && x == 0) return -one/zero;
		else if(x == 0) return(infnan(-ERANGE));
		else if(_IEEE) return (zero/zero);
		else return(infnan(EDOM));
	}
        if (x >= 2) {			 /* |x| >= 2.0 */
                s = sin(x);
                c = cos(x);
                ss = -s-c;
                cc = s-c;
		if (x < .5 * DBL_MAX) {	/* make sure x+x not overflow */
                    z = cos(x+x);
                    if ((s*c)>zero) cc = z/ss;
                    else            ss = z/cc;
                }
        /* y1(x) = sqrt(2/(pi*x))*(p1(x)*sin(x0)+q1(x)*cos(x0))
         * where x0 = x-3pi/4
         *      Better formula:
         *              cos(x0) = cos(x)cos(3pi/4)+sin(x)sin(3pi/4)
         *                      =  1/sqrt(2) * (sin(x) - cos(x))
         *              sin(x0) = sin(x)cos(3pi/4)-cos(x)sin(3pi/4)
         *                      = -1/sqrt(2) * (cos(x) + sin(x))
         * To avoid cancellation, use
         *              sin(x) +- cos(x) = -cos(2x)/(sin(x) -+ cos(x))
         * to compute the worse one.
         */
                if (_IEEE && x>two_129) {
			z = (invsqrtpi*ss)/sqrt(x);
                } else {
                    u = pone(x); v = qone(x);
                    z = invsqrtpi*(u*ss+v*cc)/sqrt(x);
                }
                return z;
        }
        if (x <= two_m54) {    /* x < 2**-54 */
            return (-tpi/x);
        }
        z = x*x;
        u = u0[0]+z*(u0[1]+z*(u0[2]+z*(u0[3]+z*u0[4])));
        v = one+z*(v0[0]+z*(v0[1]+z*(v0[2]+z*(v0[3]+z*v0[4]))));
        return (x*(u/v) + tpi*(j1(x)*log(x)-one/x));
}