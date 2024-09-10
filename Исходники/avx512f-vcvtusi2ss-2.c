static void
avx512f_test (void)
{
  union128 s1, res;
  unsigned s2;
  float res_ref[4];

  s1.x = _mm_set_ps (-24.43, 68.346, -43.35, 546.46);
  s2 = 0xFEDCA987;

  res.x = _mm_cvtu32_ss (s1.x, s2);

  compute_vcvtusi2ss (s1.a, s2, res_ref);

  if (check_union128 (res, res_ref))
    abort ();
}