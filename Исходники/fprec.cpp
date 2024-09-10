double fprec(double x, double digits)
{
    double l10, pow10, sgn, p10, P10;
    int e10, e2, do_round, dig;
    /* Max.expon. of 10 (=308.2547) */
    const double max10e = numeric_limits<double>::max_exponent * M_LOG10_2;

#ifdef IEEE_754
    if (ISNAN(x) || ISNAN(digits))
	return x + digits;
    if (!R_FINITE(x)) return x;
    if (!R_FINITE(digits)) {
	if(digits > 0) return x;
	else return 0;
    }
#endif
    if(x == 0) return x;
    dig = (int)FLOOR(digits+0.5);
    if (dig > MAX_DIGITS) {
	return x;
    } else if (dig < 1)
	dig = 1;

    sgn = 1.0;
    if(x < 0.0) {
	sgn = -sgn;
	x = -x;
    }
    l10 = log10(x);
    e10 = (int)(dig-1-FLOOR(l10));
    if(fabs(l10) < max10e - 2) {
	p10 = 1.0;
	if(e10 > max10e) {
	    p10 =  std::pow(10., e10-max10e);
	    e10 = static_cast<int>(max10e);
	} else if(e10 < - max10e) {
	    p10 =  std::pow(10., e10+max10e);
	    e10 = static_cast<int>(-max10e);	
	}
	pow10 = std::pow(10., e10);
	return(sgn*(FLOOR((x*pow10)*p10+0.5)/pow10)/p10);
    } else { /* -- LARGE or small -- */
	do_round = max10e - l10	 >= std::pow(10., -dig);
	e2 = dig + ((e10>0)? 1 : -1) * MAX_DIGITS;
	p10 = std::pow(10., e2);	x *= p10;
	P10 = std::pow(10., e10-e2);	x *= P10;
	/*-- p10 * P10 = 10 ^ e10 */
	if(do_round) x += 0.5;
	x = FLOOR(x) / p10;
	return(sgn*x/P10);
    }
}