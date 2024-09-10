long double sinl(long double x)
{
  long double x_squared;
  long double sin_x;
  size_t i;

  /* Move x to [-pi, pi) */

  x = fmodl(x, 2 * M_PI);
  if (x >= M_PI)
    {
      x -= 2 * M_PI;
    }

  if (x < -M_PI)
    {
      x += 2 * M_PI;
    }

  /* Move x to [-pi/2, pi/2) */

  if (x >= M_PI_2)
    {
      x = M_PI - x;
    }

  if (x < -M_PI_2)
    {
      x = -M_PI - x;
    }

  x_squared = x * x;
  sin_x = 0.0;

  /* Perform Taylor series approximation for sin(x) with ten terms */

  for (i = 0; i < 10; i++)
    {
      if (i % 2 == 0)
        {
          sin_x += x * _ldbl_inv_fact[i];
        }
      else
        {
          sin_x -= x * _ldbl_inv_fact[i];
        }

      x *= x_squared;
    }

  return sin_x;
}