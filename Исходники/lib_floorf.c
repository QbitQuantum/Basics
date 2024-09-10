float floorf(float x)
{
  modff(x, &x);
  if (x < 0.0)
    {
      x -= 1.0;
    }

  return x;
}