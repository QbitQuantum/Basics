double lgammafn(NMATH_STATE *state, double x)
{
    double ans, y, sinpiy;

/* For IEEE double precision DBL_EPSILON = 2^-52 = 2.220446049250313e-16 :
   xmax  = DBL_MAX / log(DBL_MAX) = 2^1024 / (1024 * log(2)) = 2^1014 / log(2)
   dxrel = sqrt(DBL_EPSILON) = 2^-26 = 5^26 * 1e-26 (is *exact* below !)
 */
#define xmax  2.5327372760800758e+305
#define dxrel 1.490116119384765696e-8

//    R_signgam = 1;

#ifdef IEEE_754
    if(ISNAN(x)) return x;
#endif

    if (x < 0 && fmod(floor(-x), 2.) == 0)
//	R_signgam = -1;

    if (x <= 0 && x == trunc(x)) { /* Negative integer argument */
	printf("lgammafn: range error"); 
	return INFINITY;/* +Inf, since lgamma(x) = log|gamma(x)| */
    }

    y = fabs(x);

    if (y <= 10)
	return log(fabs(gammafn(state,x)));
    /*
      ELSE  y = |x| > 10 ---------------------- */

    if (y > xmax) {
	printf("lgammafn: range error"); 
	return INFINITY;
    }

    if (x > 0) { /* i.e. y = x > 10 */
#ifdef IEEE_754
	if(x > 1e17)
	    return(x*(log(x) - 1.));
	else if(x > 4934720.)
	    return(M_LN_SQRT_2PI + (x - 0.5) * log(x) - x);
	else
#endif
	    return M_LN_SQRT_2PI + (x - 0.5) * log(x) - x + lgammacor(x);
    }
    /* else: x < -10; y = -x */
    sinpiy = fabs(sin(M_PI * y));

    if (sinpiy == 0) { /* Negative integer argument ===
			  Now UNNECESSARY: caught above */
	printf(" ** should NEVER happen! *** [lgamma.c: Neg.int, y=%g]\n",y);
	return NAN;
    }

    ans = M_LN_SQRT_PId2 + (x - 0.5) * log(y) - x - log(sinpiy) - lgammacor(y);

    if(fabs((x - trunc(x - 0.5)) * ans / x) < dxrel) {

	/* The answer is less than half precision because
	 * the argument is too near a negative integer. */

	printf("lgammafn: precision error"); 
    }

    return ans;
}