double
gsl_asinh (const double x)
{
  double a = fabs (x);
  double s = (x < 0) ? -1 : 1;

  if (a > 1 / GSL_SQRT_DBL_EPSILON)
    {
      return s * (log (a) + M_LN2);
    }
  else if (a > 2)
    {
      return s * log (2 * a + 1 / (a + sqrt (a * a + 1)));
    }
  else if (a > GSL_SQRT_DBL_EPSILON)
    {
      double a2 = a * a;
      return s * log1p (a + a2 / (1 + sqrt (1 + a2)));
    }
  else
    {
      return x;
    }
}