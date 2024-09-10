long double asinl(long double x)
{
  long double y, y_sin, y_cos;

  y = 0;

  while (1)
    {
      y_sin = sinl(y);
      y_cos = cosl(y);

      if (y > M_PI_2 || y < -M_PI_2)
        {
          y = fmodl(y, M_PI);
        }

      if (y_sin + LDBL_EPSILON >= x && y_sin - LDBL_EPSILON <= x)
        {
          break;
        }

      y = y - (y_sin - x) / y_cos;
    }

  return y;
}