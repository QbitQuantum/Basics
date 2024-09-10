long double
__truncl (long double x)
{
  double xh, xl, hi, lo;

  ldbl_unpack (x, &xh, &xl);

  /* Return Inf, Nan, +/-0 unchanged.  */
  if (__builtin_expect (xh != 0.0
			&& __builtin_isless (__builtin_fabs (xh),
					     __builtin_inf ()), 1))
    {
      hi = __trunc (xh);
      if (hi != xh)
	{
	  /* The high part is not an integer; the low part does not
	     affect the result.  */
	  xh = hi;
	  xl = 0;
	}
      else
	{
	  /* The high part is a nonzero integer.  */
	  lo = xh > 0 ? __floor (xl) : __ceil (xl);
	  xh = hi;
	  xl = lo;
	  ldbl_canonicalize_int (&xh, &xl);
	}
    }

  return ldbl_pack (xh, xl);
}