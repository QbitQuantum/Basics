void static
avx2_test (void)
{
  int i;
  union128i_d idx;
  union128d res;
  double s1[2], res_ref[2] = { 0 };

  for (i = 0; i < 2; ++i)
    {
      /* Set some stuff */
      s1[i] = 2.718281828459045 * (i + 1) * (i + 2);

      /* About to gather in reverse order,
         divide by 2 to demonstrate scale */
      idx.a[i] = (16 - (i + 1) * 8) >> 1;
    }

  res.x = _mm_i32gather_pd (s1, idx.x, 2);

  compute_i32gatherpd (s1, idx.a, 2, res_ref);

  if (check_union128d (res, res_ref) != 0)
    abort ();
}