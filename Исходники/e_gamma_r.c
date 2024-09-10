double
__ieee754_gamma_r (double x, int *signgamp)
{
  int32_t hx;
  u_int32_t lx;

  EXTRACT_WORDS (hx, lx, x);

  if (__glibc_unlikely (((hx & 0x7fffffff) | lx) == 0))
    {
      /* Return value for x == 0 is Inf with divide by zero exception.  */
      *signgamp = 0;
      return 1.0 / x;
    }
  if (__builtin_expect (hx < 0, 0)
      && (u_int32_t) hx < 0xfff00000 && __rint (x) == x)
    {
      /* Return value for integer x < 0 is NaN with invalid exception.  */
      *signgamp = 0;
      return (x - x) / (x - x);
    }
  if (__glibc_unlikely ((unsigned int) hx == 0xfff00000 && lx == 0))
    {
      /* x == -Inf.  According to ISO this is NaN.  */
      *signgamp = 0;
      return x - x;
    }
  if (__glibc_unlikely ((hx & 0x7ff00000) == 0x7ff00000))
    {
      /* Positive infinity (return positive infinity) or NaN (return
	 NaN).  */
      *signgamp = 0;
      return x + x;
    }

  if (x >= 172.0)
    {
      /* Overflow.  */
      *signgamp = 0;
      return DBL_MAX * DBL_MAX;
    }
  else if (x > 0.0)
    {
      *signgamp = 0;
      int exp2_adj;
      double ret = gamma_positive (x, &exp2_adj);
      return __scalbn (ret, exp2_adj);
    }
  else if (x >= -DBL_EPSILON / 4.0)
    {
      *signgamp = 0;
      return 1.0 / x;
    }
  else
    {
      double tx = __trunc (x);
      *signgamp = (tx == 2.0 * __trunc (tx / 2.0)) ? -1 : 1;
      if (x <= -184.0)
	/* Underflow.  */
	return DBL_MIN * DBL_MIN;
      double frac = tx - x;
      if (frac > 0.5)
	frac = 1.0 - frac;
      double sinpix = (frac <= 0.25
		       ? __sin (M_PI * frac)
		       : __cos (M_PI * (0.5 - frac)));
      int exp2_adj;
      double ret = M_PI / (-x * sinpix * gamma_positive (-x, &exp2_adj));
      return __scalbn (ret, -exp2_adj);
    }
}