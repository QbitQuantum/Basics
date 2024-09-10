int
main ()
{
  /* Zero.  */
  ASSERT (ceilf (0.0f) == 0.0f);
  ASSERT (ceilf (-zero) == 0.0f);
  /* Positive numbers.  */
  ASSERT (ceilf (0.3f) == 1.0f);
  ASSERT (ceilf (0.7f) == 1.0f);
  ASSERT (ceilf (1.0f) == 1.0f);
  ASSERT (ceilf (1.001f) == 2.0f);
  ASSERT (ceilf (1.5f) == 2.0f);
  ASSERT (ceilf (1.999f) == 2.0f);
  ASSERT (ceilf (2.0f) == 2.0f);
  ASSERT (ceilf (65535.99f) == 65536.0f);
  ASSERT (ceilf (65536.0f) == 65536.0f);
  ASSERT (ceilf (2.341e31f) == 2.341e31f);
  /* Negative numbers.  */
  ASSERT (ceilf (-0.3f) == 0.0f);
  ASSERT (ceilf (-0.7f) == 0.0f);
  ASSERT (ceilf (-1.0f) == -1.0f);
  ASSERT (ceilf (-1.5f) == -1.0f);
  ASSERT (ceilf (-1.999f) == -1.0f);
  ASSERT (ceilf (-2.0f) == -2.0f);
  ASSERT (ceilf (-65535.99f) == -65535.0f);
  ASSERT (ceilf (-65536.0f) == -65536.0f);
  ASSERT (ceilf (-2.341e31f) == -2.341e31f);
  /* Infinite numbers.  */
  ASSERT (ceilf (1.0f / 0.0f) == 1.0f / 0.0f);
  ASSERT (ceilf (-1.0f / 0.0f) == -1.0f / 0.0f);
  /* NaNs.  */
  ASSERT (isnanf (ceilf (NaNf ())));

  return 0;
}