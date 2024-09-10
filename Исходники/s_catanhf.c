__complex__ float
__catanhf (__complex__ float x)
{
  __complex__ float res;
  int rcls = fpclassify (__real__ x);
  int icls = fpclassify (__imag__ x);

  if (__builtin_expect (rcls <= FP_INFINITE || icls <= FP_INFINITE, 0))
    {
      if (icls == FP_INFINITE)
	{
	  __real__ res = __copysignf (0.0, __real__ x);
	  __imag__ res = __copysignf (M_PI_2, __imag__ x);
	}
      else if (rcls == FP_INFINITE || rcls == FP_ZERO)
	{
	  __real__ res = __copysignf (0.0, __real__ x);
	  if (icls >= FP_ZERO)
	    __imag__ res = __copysignf (M_PI_2, __imag__ x);
	  else
	    __imag__ res = __nanf ("");
	}
      else
	{
	  __real__ res = __nanf ("");
	  __imag__ res = __nanf ("");
	}
    }
  else if (__builtin_expect (rcls == FP_ZERO && icls == FP_ZERO, 0))
    {
      res = x;
    }
  else
    {
      float i2 = __imag__ x * __imag__ x;

      float num = 1.0 + __real__ x;
      num = i2 + num * num;

      float den = 1.0 - __real__ x;
      den = i2 + den * den;

      __real__ res = 0.25 * (__ieee754_logf (num) - __ieee754_logf (den));

      den = 1 - __real__ x * __real__ x - i2;

      __imag__ res = 0.5 * __ieee754_atan2f (2.0 * __imag__ x, den);
    }

  return res;
}