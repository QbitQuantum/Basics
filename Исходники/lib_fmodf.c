float fmodf(float x, float div)
{
  float n0;

  x /= div;
  x = modff(x, &n0);
  x *= div;

  return x;
}