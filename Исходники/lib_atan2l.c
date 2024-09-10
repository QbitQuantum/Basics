long double atan2l(long double y, long double x)
{

  if (y == 0.0)
    {
      if (x >= 0.0)
        {
          return 0.0;
        }
      else
        {
          return M_PI;
        }
    }
  else if (y > 0.0)
    {
      if (x == 0.0)
        {
          return M_PI_2;
        }
      else if (x > 0.0)
        {
          return atanl(y / x);
        }
      else
        {
          return M_PI - atanl(y / x);
        }
    }
  else
    {
      if (x == 0.0)
        {
          return M_PI + M_PI_2;
        }
      else if (x > 0.0)
        {
          return 2 * M_PI - atanl(y / x);
        }
      else
        {
          return M_PI + atanl(y / x);
        }
    }
}