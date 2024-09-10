double
y1(double x)
{
	double z, s,c,ss,cc,u,v;
	int32_t hx,ix,lx;

	EXTRACT_WORDS(hx,lx,x);
        ix = 0x7fffffff&hx;
    /* if Y1(NaN) is NaN, Y1(-inf) is NaN, Y1(inf) is 0 */
	if(ix>=0x7ff00000) return  one/(x+x*x);
        if((ix|lx)==0) return -one/zero;
        if(hx<0) return zero/zero;
        if(ix >= 0x40000000) {  /* |x| >= 2.0 */
                s = sin(x);
                c = cos(x);
                ss = -s-c;
                cc = s-c;
                if(ix<0x7fe00000) {  /* make sure x+x not overflow */
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
                if(ix>0x48000000) z = (invsqrtpi*ss)/sqrt(x);
                else {
                    u = pone(x); v = qone(x);
                    z = invsqrtpi*(u*ss+v*cc)/sqrt(x);
                }
                return z;
        }
        if(ix<=0x3c900000) {    /* x < 2**-54 */
            return(-tpi/x);
        }
        z = x*x;
        u = U0[0]+z*(U0[1]+z*(U0[2]+z*(U0[3]+z*U0[4])));
        v = one+z*(V0[0]+z*(V0[1]+z*(V0[2]+z*(V0[3]+z*V0[4]))));
        return(x*(u/v) + tpi*(j1(x)*log(x)-one/x));
}