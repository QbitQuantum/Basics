long double atanl(long double x)
{
  return asinl(x / sqrtl(x * x + 1));
}