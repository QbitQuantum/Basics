float ceilf(float x)
{
  float x1 = x;

  modff(x, &x);
  if (x1 > 0.0F && fabsf(x1 - x) > 0.0F)
    {
      x += 1.0F;
    }

  return x;
}