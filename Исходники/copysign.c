double
copysign (double x, double y)
{
  return (signbit (x) != signbit (y) ? - x : x);
}