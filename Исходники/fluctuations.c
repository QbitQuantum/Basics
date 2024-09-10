/* ********************************************************************** */
static TBL_REAL interpol8(TBL_REAL xlo, TBL_REAL xhi, TBL_REAL x,
			  TBL_REAL ylo, TBL_REAL yhi,
			  TBL_REAL zlo, TBL_REAL zhi) {
    TBL_REAL	alpha, y, z;
    alpha = (x - xlo) / (xhi - xlo);
    y = ylo + alpha*(yhi - ylo);
    z = zlo + alpha*(zhi - zlo);
/* average */
/*    return(0.5*(y+z)); */
/* uniform distribution */
/*    return(y + drand48()*(z-y)); */
/* equal area */
    return((y+z) - COPYSIGN(SQRT(0.5*(y*y+z*z)), y));
}