__complex__ double
__casinh (__complex__ double x)
{
  __complex__ double res;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (rcls <= FP_INFINITE || icls <= FP_INFINITE)
    {
      if (icls == FP_INFINITE)
	{
	  __real__ res = __copysign (HUGE_VAL, __real__ x);

	  if (rcls == FP_NAN)
	    __imag__ res = __nan ("");
	  else
	    __imag__ res = __copysign (rcls >= FP_ZERO ? M_PI_2 : M_PI_4,
				       __imag__ x);
	}
      else if (rcls <= FP_INFINITE)
	{
	  __real__ res = __real__ x;
	  if ((rcls == FP_INFINITE && icls >= FP_ZERO)
	      || (rcls == FP_NAN && icls == FP_ZERO))
	    __imag__ res = __copysign (0.0, __imag__ x);
	  else
	    __imag__ res = __nan ("");
	}
      else
	{
	  __real__ res = __nan ("");
	  __imag__ res = __nan ("");
	}
    }
  else if (rcls == FP_ZERO && icls == FP_ZERO)
    {
      res = x;
    }
  else
    {
      res = __kernel_casinh (x, 0);
    }

  return res;
}