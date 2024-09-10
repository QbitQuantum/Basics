__complex__ long double
__ccoshl (__complex__ long double x)
{
  __complex__ long double retval;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (__builtin_expect (rcls >= FP_ZERO, 1))
    {
      /* Real part is finite.  */
      if (__builtin_expect (icls >= FP_ZERO, 1))
	{
	  /* Imaginary part is finite.  */
	  const int t = (int) ((LDBL_MAX_EXP - 1) * M_LN2l);
	  long double sinix, cosix;

	  __sincosl (__imag__ x, &sinix, &cosix);

	  if (fabsl (__real__ x) > t)
	    {
	      long double exp_t = __ieee754_expl (t);
	      long double rx = fabsl (__real__ x);
	      if (signbit (__real__ x))
		sinix = -sinix;
	      rx -= t;
	      sinix *= exp_t / 2.0L;
	      cosix *= exp_t / 2.0L;
	      if (rx > t)
		{
		  rx -= t;
		  sinix *= exp_t;
		  cosix *= exp_t;
		}
	      if (rx > t)
		{
		  /* Overflow (original real part of x > 3t).  */
		  __real__ retval = LDBL_MAX * cosix;
		  __imag__ retval = LDBL_MAX * sinix;
		}
	      else
		{
		  long double exp_val = __ieee754_expl (rx);
		  __real__ retval = exp_val * cosix;
		  __imag__ retval = exp_val * sinix;
		}
	    }
	  else
	    {
	      __real__ retval = __ieee754_coshl (__real__ x) * cosix;
	      __imag__ retval = __ieee754_sinhl (__real__ x) * sinix;
	    }
	}
      else
	{
	  __imag__ retval = __real__ x == 0.0 ? 0.0 : __nanl ("");
	  __real__ retval = __nanl ("") + __nanl ("");

	  if (icls == FP_INFINITE)
	    feraiseexcept (FE_INVALID);
	}
    }
  else if (__builtin_expect (rcls == FP_INFINITE, 1))
    {
      /* Real part is infinite.  */
      if (__builtin_expect (icls > FP_ZERO, 1))
	{
	  /* Imaginary part is finite.  */
	  long double sinix, cosix;

	  __sincosl (__imag__ x, &sinix, &cosix);

	  __real__ retval = __copysignl (HUGE_VALL, cosix);
	  __imag__ retval = (__copysignl (HUGE_VALL, sinix)
			     * __copysignl (1.0, __real__ x));
	}
      else if (icls == FP_ZERO)
	{
	  /* Imaginary part is 0.0.  */
	  __real__ retval = HUGE_VALL;
	  __imag__ retval = __imag__ x * __copysignl (1.0, __real__ x);
	}
      else
	{
	  /* The addition raises the invalid exception.  */
	  __real__ retval = HUGE_VALL;
	  __imag__ retval = __nanl ("") + __nanl ("");

	  if (icls == FP_INFINITE)
	    feraiseexcept (FE_INVALID);
	}
    }
  else
    {
      __real__ retval = __nanl ("");
      __imag__ retval = __imag__ x == 0.0 ? __imag__ x : __nanl ("");
    }

  return retval;
}