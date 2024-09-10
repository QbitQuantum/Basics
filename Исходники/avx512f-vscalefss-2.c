static void
avx512f_test (void)
{
  union128 res1, s1, s2;
  float res_ref[SIZE];
  int i;

  for (i = 0; i < SIZE; i++)
    {
      s1.a[i] = 11.5 * (i + 1);
      s2.a[i] = 10.5 * (i + 1);
    }

  res1.x = _mm_scalef_ss (s1.x, s2.x);

  compute_scalefss (s1.a, s2.a, res_ref);

  if (check_union128 (res1, res_ref))
    abort ();
}