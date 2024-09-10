__complex__ float
__casinf (__complex__ float x)
{
  __complex__ float res;

  if (isnan (__real__ x) || isnan (__imag__ x))
    {
      if (__real__ x == 0.0)
	{
	  res = x;
	}
      else if (isinf (__real__ x) || isinf (__imag__ x))
	{
	  __real__ res = __nanf ("");
	  __imag__ res = __copysignf (HUGE_VALF, __imag__ x);
	}
      else
	{
	  __real__ res = __nanf ("");
	  __imag__ res = __nanf ("");
	}
    }
  else
    {
      __complex__ float y;

      __real__ y = -__imag__ x;
      __imag__ y = __real__ x;

      y = __casinhf (y);

      __real__ res = __imag__ y;
      __imag__ res = -__real__ y;
    }

  return res;
}