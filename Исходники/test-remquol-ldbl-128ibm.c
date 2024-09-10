static long double
wrap_remquol (long double x, long double y)
{
  int quo;
  return remquol (x, y, &quo);
}