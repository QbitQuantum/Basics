int ilogbf(float x)
{
  if (x == 0.0)
    return FP_ILOGB0;
  if (isinf(x))
    return INT_MAX;
  if (isnan(x))
    return FP_ILOGBNAN;
  return (int) logbf(x);
}