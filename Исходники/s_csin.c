__complex__ double
__csin (__complex__ double x)
{
  __complex__ double retval;
  int negate = signbit (__real__ x);
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  __real__ x = fabs (__real__ x);

  if (__glibc_likely (icls >= FP_ZERO))
    {
      /* Imaginary part is finite.  */
      if (__glibc_likely (rcls >= FP_ZERO))
	{
	  /* Real part is finite.  */
	  const int t = (int) ((DBL_MAX_EXP - 1) * M_LN2);
	  double sinix, cosix;

	  if (__glibc_likely (rcls != FP_SUBNORMAL))
	    {
	      __sincos (__real__ x, &sinix, &cosix);
	    }
	  else
	    {
	      sinix = __real__ x;
	      cosix = 1.0;
	    }

	  if (fabs (__imag__ x) > t)
	    {
	      double exp_t = __ieee754_exp (t);
	      double ix = fabs (__imag__ x);
	      if (signbit (__imag__ x))
		cosix = -cosix;
	      ix -= t;
	      sinix *= exp_t / 2.0;
	      cosix *= exp_t / 2.0;
	      if (ix > t)
		{
		  ix -= t;
		  sinix *= exp_t;
		  cosix *= exp_t;
		}
	      if (ix > t)
		{
		  /* Overflow (original imaginary part of x > 3t).  */
		  __real__ retval = DBL_MAX * sinix;
		  __imag__ retval = DBL_MAX * cosix;
		}
	      else
		{
		  double exp_val = __ieee754_exp (ix);
		  __real__ retval = exp_val * sinix;
		  __imag__ retval = exp_val * cosix;
		}
	    }
	  else
	    {
	      __real__ retval = __ieee754_cosh (__imag__ x) * sinix;
	      __imag__ retval = __ieee754_sinh (__imag__ x) * cosix;
	    }

	  if (negate)
	    __real__ retval = -__real__ retval;

	  if (fabs (__real__ retval) < DBL_MIN)
	    {
	      volatile double force_underflow
		= __real__ retval * __real__ retval;
	      (void) force_underflow;
	    }
	  if (fabs (__imag__ retval) < DBL_MIN)
	    {
	      volatile double force_underflow
		= __imag__ retval * __imag__ retval;
	      (void) force_underflow;
	    }
	}
      else
	{
	  if (icls == FP_ZERO)
	    {
	      /* Imaginary part is 0.0.  */
	      __real__ retval = __nan ("");
	      __imag__ retval = __imag__ x;

	      if (rcls == FP_INFINITE)
		feraiseexcept (FE_INVALID);
	    }
	  else
	    {
	      __real__ retval = __nan ("");
	      __imag__ retval = __nan ("");

	      feraiseexcept (FE_INVALID);
	    }
	}
    }
  else if (icls == FP_INFINITE)
    {
      /* Imaginary part is infinite.  */
      if (rcls == FP_ZERO)
	{
	  /* Real part is 0.0.  */
	  __real__ retval = __copysign (0.0, negate ? -1.0 : 1.0);
	  __imag__ retval = __imag__ x;
	}
      else if (rcls > FP_ZERO)
	{
	  /* Real part is finite.  */
	  double sinix, cosix;

	  if (__glibc_likely (rcls != FP_SUBNORMAL))
	    {
	      __sincos (__real__ x, &sinix, &cosix);
	    }
	  else
	    {
	      sinix = __real__ x;
	      cosix = 1.0;
	    }

	  __real__ retval = __copysign (HUGE_VAL, sinix);
	  __imag__ retval = __copysign (HUGE_VAL, cosix);

	  if (negate)
	    __real__ retval = -__real__ retval;
	  if (signbit (__imag__ x))
	    __imag__ retval = -__imag__ retval;
	}
      else
	{
	  /* The addition raises the invalid exception.  */
	  __real__ retval = __nan ("");
	  __imag__ retval = HUGE_VAL;

	  if (rcls == FP_INFINITE)
	    feraiseexcept (FE_INVALID);
	}
    }
  else
    {
      if (rcls == FP_ZERO)
	__real__ retval = __copysign (0.0, negate ? -1.0 : 1.0);
      else
	__real__ retval = __nan ("");
      __imag__ retval = __nan ("");
    }

  return retval;
}