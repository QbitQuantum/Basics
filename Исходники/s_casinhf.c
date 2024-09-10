__complex__ float
__casinhf (__complex__ float x)
{
  __complex__ float res;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (rcls <= FP_INFINITE || icls <= FP_INFINITE)
    {
      if (icls == FP_INFINITE)
	{
	  __real__ res = __copysignf (HUGE_VALF, __real__ x);

	  if (rcls == FP_NAN)
	    __imag__ res = __nanf ("");
	  else
	    __imag__ res = __copysignf (rcls >= FP_ZERO ? M_PI_2 : M_PI_4,
					__imag__ x);
	}
      else if (rcls <= FP_INFINITE)
	{
	  __real__ res = __real__ x;
	  if ((rcls == FP_INFINITE && icls >= FP_ZERO)
	      || (rcls == FP_NAN && icls == FP_ZERO))
	    __imag__ res = __copysignf (0.0, __imag__ x);
	  else
	    __imag__ res = __nanf ("");
	}
      else
	{
	  __real__ res = __nanf ("");
	  __imag__ res = __nanf ("");
	}
    }
  else if (rcls == FP_ZERO && icls == FP_ZERO)
    {
      res = x;
    }
  else
    {
      __complex__ float y;

      __real__ y = (__real__ x - __imag__ x) * (__real__ x + __imag__ x) + 1.0;
      __imag__ y = 2.0 * __real__ x * __imag__ x;

      y = __csqrtf (y);

      __real__ y += __real__ x;
      __imag__ y += __imag__ x;

      res = __clogf (y);
    }

  return res;
}