static void
avx512f_test (void)
{
  union128d s1, s2, res1;
  double res_ref[2];

  s1.x = _mm_set_pd (-3.0, 111.111);
  s2.x = _mm_set_pd (222.222, 4.0);

  res1.x = _mm_rsqrt14_sd (s1.x, s2.x);

  compute_vrsqrt14sd (s1.a, s2.a, res_ref);

  if (check_fp_union128d (res1, res_ref))
    abort ();
}