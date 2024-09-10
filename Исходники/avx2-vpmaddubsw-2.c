static void
avx2_test (void)
{
  union256i_w s1, s2, res;
  short res_ref[16];
  int i;
  int fail = 0;

  for (i = 0; i < 256; i += 16)
    {
      s1.x = _mm256_loadu_si256 ((__m256i *) & vals[i]);
      s2.x = _mm256_loadu_si256 ((__m256i *) & vals[i + 8]);

      res.x = _mm256_maddubs_epi16 (s1.x, s2.x);

      compute_pmaddubsw256 (s1.a, s2.a, res_ref);

      fail += check_union256i_w (res, res_ref);
    }

  if (fail != 0)
    abort ();
}