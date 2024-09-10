  /* Fix the sign of y and return */
static double
__signArctan (double x, double y)
{
  return __copysign (y, x);
}