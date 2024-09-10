DOUBLE
LOGB (DOUBLE x)
{
  if (isfinite (x))
    {
      if (x == L_(0.0))
        /* Return -Infinity.  */
        return - HUGEVAL;
      else
        {
          int e;

          (void) FREXP (x, &e);
          return (DOUBLE) (e - 1);
        }
    }
  else
    {
      if (ISNAN (x))
        return x; /* NaN */
      else
        /* Return +Infinity.  */
        return HUGEVAL;
    }
}