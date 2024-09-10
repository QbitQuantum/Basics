double
__modf (double x, double *iptr)
{
  if (__builtin_isinf (x))
    {
      *iptr = x;
      return __copysign (0.0, x);
    }
  else if (__builtin_isnan (x))
    {
      *iptr = NAN;
      return NAN;
    }

  if (x >= 0.0)
    {
      *iptr = __floor (x);
      return __copysign (x - *iptr, x);
    }
  else
    {
      *iptr = __ceil (x);
      return __copysign (x - *iptr, x);
    }
}