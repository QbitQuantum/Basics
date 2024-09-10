__complex__ double
__casin (__complex__ double x)
{
  __complex__ double res;

  if (isnan (__real__ x) || isnan (__imag__ x))
    {
      if (__real__ x == 0.0)
	{
	  res = x;
	}
      else if (isinf (__real__ x) || isinf (__imag__ x))
	{
	  __real__ res = __nan ("");
	  __imag__ res = __copysign (HUGE_VAL, __imag__ x);
	}
      else
	{
	  __real__ res = __nan ("");
	  __imag__ res = __nan ("");
	}
    }
  else
    {
      __complex__ double y;

      __real__ y = -__imag__ x;
      __imag__ y = __real__ x;

      y = __casinh (y);

      __real__ res = __imag__ y;
      __imag__ res = -__real__ y;
    }

  return res;
}