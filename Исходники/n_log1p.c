double
log1p(double x)
{
	static const double zero=0.0, negone= -1.0, one=1.0,
		      half=1.0/2.0, small=1.0E-20;   /* 1+small == 1 */
	double z,s,t,c;
	int k;

	if (isnan(x))
		return (x);

	if(finite(x)) {
	   if( x > negone ) {

	   /* argument reduction */
	      if(copysign(x,one)<small) return(x);
	      k=logb(one+x); z=scalbn(x,-k); t=scalbn(one,-k);
	      if(z+t >= sqrt2 )
		  { k += 1 ; z *= half; t *= half; }
	      t += negone; x = z + t;
	      c = (t-x)+z ;		/* correction term for x */

 	   /* compute log(1+x)  */
              s = x/(2+x); t = x*x*half;
	      c += (k*ln2lo-c*x);
	      z = c+s*(t+__log__L(s*s));
	      x += (z - t) ;

	      return(k*ln2hi+x);
	   }
	/* end of if (x > negone) */

	    else {
#if defined(__vax__)
		if ( x == negone )
		    return (infnan(-ERANGE));	/* -INF */
		else
		    return (infnan(EDOM));	/* NaN */
#else	/* defined(__vax__) */
		/* x = -1, return -INF with signal */
		if ( x == negone ) return( negone/zero );

		/* negative argument for log, return NaN with signal */
	        else return ( zero / zero );
#endif	/* defined(__vax__) */
	    }
	}
    /* end of if (finite(x)) */

    /* log(-INF) is NaN */
	else if(x<0)
	     return(zero/zero);

    /* log(+INF) is INF */
	else return(x);
}