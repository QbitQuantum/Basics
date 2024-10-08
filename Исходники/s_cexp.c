__complex__ double
__cexp (__complex__ double x)
{
  __complex__ double retval;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (rcls >= FP_ZERO)
    {
      /* Real part is finite.  */
      if (icls >= FP_ZERO)
	{
	  /* Imaginary part is finite.  */
	  double exp_val = __ieee754_exp (__real__ x);
	  double sinix, cosix;

	  __sincos (__imag__ x, &sinix, &cosix);

	  if (isfinite (exp_val))
	    {
	      __real__ retval = exp_val * cosix;
	      __imag__ retval = exp_val * sinix;
	    }
	  else
	    {
	      __real__ retval = __copysign (exp_val, cosix);
	      __imag__ retval = __copysign (exp_val, sinix);
	    }
	}
      else
	{
	  /* If the imaginary part is +-inf or NaN and the real part
	     is not +-inf the result is NaN + iNaN.  */
	  __real__ retval = __nan ("");
	  __imag__ retval = __nan ("");

#ifdef FE_INVALID
	  feraiseexcept (FE_INVALID);
#endif
	}
    }
  else if (rcls == FP_INFINITE)
    {
      /* Real part is infinite.  */
      if (icls >= FP_ZERO)
	{
	  /* Imaginary part is finite.  */
	  double value = signbit (__real__ x) ? 0.0 : HUGE_VAL;

	  if (icls == FP_ZERO)
	    {
	      /* Imaginary part is 0.0.  */
	      __real__ retval = value;
	      __imag__ retval = __imag__ x;
	    }
	  else
	    {
	      double sinix, cosix;

	      __sincos (__imag__ x, &sinix, &cosix);

	      __real__ retval = __copysign (value, cosix);
	      __imag__ retval = __copysign (value, sinix);
	    }
	}
      else if (signbit (__real__ x) == 0)
	{
	  __real__ retval = HUGE_VAL;
	  __imag__ retval = __nan ("");

#ifdef FE_INVALID
	  if (icls == FP_INFINITE)
	    feraiseexcept (FE_INVALID);
#endif
	}
      else
	{
	  __real__ retval = 0.0;
	  __imag__ retval = __copysign (0.0, __imag__ x);
	}
    }
  else
    {
      /* If the real part is NaN the result is NaN + iNaN.  */
      __real__ retval = __nan ("");
      __imag__ retval = __nan ("");

#ifdef FE_INVALID
      if (rcls != FP_NAN || icls != FP_NAN)
	feraiseexcept (FE_INVALID);
#endif
    }

  return retval;
}