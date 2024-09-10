__complex__ double
__csinh (__complex__ double x)
{
  __complex__ double retval;
  int negate = signbit (__real__ x);
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  __real__ x = fabs (__real__ x);

  if (rcls >= FP_ZERO)
    {
      /* Real part is finite.  */
      if (icls >= FP_ZERO)
	{
	  /* Imaginary part is finite.  */
	  double sinh_val = __ieee754_sinh (__real__ x);
	  double cosh_val = __ieee754_cosh (__real__ x);
	  double sinix, cosix;

	  __sincos (__imag__ x, &sinix, &cosix);

	  __real__ retval = sinh_val * cosix;
	  __imag__ retval = cosh_val * sinix;

	  if (negate)
	    __real__ retval = -__real__ retval;
	}
      else
	{
	  if (rcls == FP_ZERO)
	    {
	      /* Real part is 0.0.  */
	      __real__ retval = __copysign (0.0, negate ? -1.0 : 1.0);
	      __imag__ retval = __nan ("") + __nan ("");

#ifdef FE_INVALID
	      if (icls == FP_INFINITE)
		feraiseexcept (FE_INVALID);
#endif
	    }
	  else
	    {
	      __real__ retval = __nan ("");
	      __imag__ retval = __nan ("");

#ifdef FE_INVALID
	      feraiseexcept (FE_INVALID);
#endif
	    }
	}
    }
  else if (rcls == FP_INFINITE)
    {
      /* Real part is infinite.  */
      if (icls == FP_ZERO)
	{
	  /* Imaginary part is 0.0.  */
	  __real__ retval = negate ? -HUGE_VAL : HUGE_VAL;
	  __imag__ retval = __imag__ x;
	}
      else if (icls > FP_ZERO)
	{
	  /* Imaginary part is finite.  */
	  double sinix, cosix;

	  __sincos (__imag__ x, &sinix, &cosix);

	  __real__ retval = __copysign (HUGE_VAL, cosix);
	  __imag__ retval = __copysign (HUGE_VAL, sinix);

	  if (negate)
	    __real__ retval = -__real__ retval;
	}
      else
	{
	  /* The addition raises the invalid exception.  */
	  __real__ retval = HUGE_VAL;
	  __imag__ retval = __nan ("") + __nan ("");

#ifdef FE_INVALID
	  if (icls == FP_INFINITE)
	    feraiseexcept (FE_INVALID);
#endif
	}
    }
  else
    {
      __real__ retval = __nan ("");
      __imag__ retval = __imag__ x == 0.0 ? __imag__ x : __nan ("");
    }

  return retval;
}