long double frexpl(long double x, int *exponent)
{
  *exponent = (int)ceill(log2(x));
  return x / ldexpl(1.0, *exponent);
}