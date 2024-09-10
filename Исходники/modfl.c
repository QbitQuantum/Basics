long double
modfl (long double x, long double *iptr)
{
  if (isfinite (x))
    {
      long double integer_part = truncl (x);
      *iptr = integer_part;
      return x - integer_part;
    }
  else
    {
      if (isinf (x))
        {
          *iptr = x;
          return 1.0L / x;
        }
      else /* isnanl (x) */
        {
          *iptr = x;
          return x;
        }
    }
}