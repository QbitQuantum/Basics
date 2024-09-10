/* map floating-point number x to integer relative to exponent e */
static Scalar
_t1(quantize, Scalar)(Scalar x, int e)
{
  return LDEXP(x, (CHAR_BIT * (int)sizeof(Scalar) - 2) - e);
}