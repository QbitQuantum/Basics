__complex__ double
__cproj (__complex__ double x)
{
  if (isinf (__real__ x) || isinf (__imag__ x))
    {
      __complex__ double res;

      __real__ res = INFINITY;
      __imag__ res = __copysign (0.0, __imag__ x);

      return res;
    }

  return x;
}