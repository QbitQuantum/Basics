int32_t
__ieee754_rem_pio2f (float x, float *y)
{
  float ax, z, n, r, w, t, e0;
  float tx[3];
  int32_t i, nx;

  ax = __builtin_fabsf (x);
  if (ax <= pio4)
    {
      y[0] = x;
      y[1] = 0;
      return 0;
    }
  if (ax < pio3_4)
    {
      if (x > 0)
	{
	  z = x - pio2_1;
	  if (!__float_and_test28 (ax, pio2_24b))
	    {
	      y[0] = z - pio2_1t;
	      y[1] = (z - y[0]) - pio2_1t;
	    }
	  else
	    {
	      z -= pio2_2;
	      y[0] = z - pio2_2t;
	      y[1] = (z - y[0]) - pio2_2t;
	    }
	  return 1;
	}
      else
	{
	  z = x + pio2_1;
	  if (!__float_and_test28 (ax, pio2_24b))
	    {
	      y[0] = z + pio2_1t;
	      y[1] = (z - y[0]) + pio2_1t;
	    }
	  else
	    {
	      z += pio2_2;
	      y[0] = z + pio2_2t;
	      y[1] = (z - y[0]) + pio2_2t;
	    }
	  return -1;
	}
    }
  if (ax <= pio2_2e7)
    {
      n = __floorf (ax * invpio2 + half);
      i = (int32_t) n;
      r = ax - n * pio2_1;
      w = n * pio2_1t;		/* 1st round good to 40 bit */
      if (i < 32 && !__float_and_test24 (ax, npio2_hw[i - 1]))
	{
	  y[0] = r - w;
	}
      else
	{
	  float i, j;
	  j = __float_and8 (ax);
	  y[0] = r - w;
	  i = __float_and8 (y[0]);
	  if (j / i > 256.0 || j / i < 3.9062500e-3)
	    {			/* 2nd iterations needed, good to 57 */
	      t = r;
	      w = n * pio2_2;
	      r = t - w;
	      w = n * pio2_2t - ((t - r) - w);
	      y[0] = r - w;
	      i = __float_and8 (y[0]);
	      if (j / i > 33554432 || j / i < 2.9802322e-8)
		{		/* 3rd iteration needed, 74 bits acc */
		  t = r;
		  w = n * pio2_3;
		  r = t - w;
		  w = n * pio2_3t - ((t - r) - w);
		  y[0] = r - w;
		}
	    }
	}
      y[1] = (r - y[0]) - w;
      if (x < 0)
	{
	  y[0] = -y[0];
	  y[1] = -y[1];
	  return -i;
	}
      else
	{
	  return i;
	}
    }

  /* all other (large) arguments */
  if (isnanf (x) || isinff (x))
    {
      y[0] = y[1] = x - x;
      return 0;
    }

  /* set z = scalbn(|x|,ilogb(x)-7) */
  e0 = __float_and8 (ax / 128.0);
  z = ax / e0;

  tx[0] = __floorf (z);
  z = (z - tx[0]) * two8;
  tx[1] = __floorf (z);
  z = (z - tx[1]) * two8;
  tx[2] = __floorf (z);

  nx = 3;
  while (tx[nx - 1] == zero)
    nx--;

  i = __fp_kernel_rem_pio2f (tx, y, e0, nx);
  if (x < 0)
    {
      y[0] = -y[0];
      y[1] = -y[1];
      return -i;
    }
  return i;
}