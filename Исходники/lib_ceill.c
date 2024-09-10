long double ceill(long double x)
{
  modfl(x, &x);
  if (x > 0.0)
    {
      x += 1.0;
    }

  return x;
}