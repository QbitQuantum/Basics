void static
avx512f_test (void)
{
  union128d res1, s1, s2;
  double res_ref[SIZE];
  int i;

  for (i = 0; i < SIZE; i++)
    {
      s1.a[i] = 11.5 * (i + 1);
      s2.a[i] = 10.5 * (i + 1);
    }

  res1.x = _mm_scalef_sd (s1.x, s2.x);

  compute_scalefsd (s1.a, s2.a, res_ref);

  if (check_union128d (res1, res_ref))
    abort ();
}