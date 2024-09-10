double gammap (double a, double x)
{
  /** Incomplete Gammafunction **/
  if (x < 0 || a <= 0) return 0; /* invalid arguments */

  if (x < a+1)
     return gammap_sr(a,x,lgamma(a));
  else
     return 1-gammaq_cf(a,x,lgamma(a));
}