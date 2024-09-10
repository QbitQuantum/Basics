__complex__ float
__cacoshf (__complex__ float x)
{
  __complex__ float res;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (rcls <= FP_INFINITE || icls <= FP_INFINITE)
    {
      if (icls == FP_INFINITE)
	{
	  __real__ res = HUGE_VALF;

	  if (rcls == FP_NAN)
	    __imag__ res = __nanf ("");
	  else
	    __imag__ res = __copysignf ((rcls == FP_INFINITE
					 ? (__real__ x < 0.0
					    ? M_PI - M_PI_4 : M_PI_4)
					 : M_PI_2), __imag__ x);
	}
      else if (rcls == FP_INFINITE)
	{
	  __real__ res = HUGE_VALF;

	  if (icls >= FP_ZERO)
	    __imag__ res = __copysignf (signbit (__real__ x) ? M_PI : 0.0,
					__imag__ x);
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
      __real__ res = 0.0;
      __imag__ res = __copysignf (M_PI_2, __imag__ x);
    }
  else
    {
#if 1
      __complex__ float y;

      __real__ y = (__real__ x - __imag__ x) * (__real__ x + __imag__ x) - 1.0;
      __imag__ y = 2.0 * __real__ x * __imag__ x;

      y = __csqrtf (y);

      if (__real__ x < 0.0)
	y = -y;

      __real__ y += __real__ x;
      __imag__ y += __imag__ x;

      res = __clogf (y);
#else
      float re2 = __real__ x * __real__ x;
      float im2 = __imag__ x * __imag__ x;
      float sq = re2 - im2 - 1.0;
      float ro = __ieee754_sqrtf (sq * sq + 4 * re2 * im2);
      float a = __ieee754_sqrtf ((sq + ro) / 2.0);
      float b = __ieee754_sqrtf ((-sq + ro) / 2.0);

      __real__ res = 0.5 * __ieee754_logf (re2 + __real__ x * 2 * a
					   + im2 + __imag__ x * 2 * b
					   + ro);
      __imag__ res = __ieee754_atan2f (__imag__ x + b, __real__ x + a);
#endif

      /* We have to use the positive branch.  */
      if (__real__ res < 0.0)
	res = -res;
    }

  return res;
}