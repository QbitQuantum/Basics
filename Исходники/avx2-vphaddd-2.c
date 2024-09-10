static void
avx2_test (void)
{
  union256i_d s1, s2, res;
  int res_ref[8];
  int i, j;
  int fail = 0;


  for (i = 0; i < 256; i += 16)
    {
      s1.x = _mm256_loadu_si256 ((__m256i *) & vals[i]);
      s2.x = _mm256_loadu_si256 ((__m256i *) & vals[i + 8]);

      res.x = _mm256_hadd_epi32 (s1.x, s2.x);

      compute_phaddd256 (s1.a, s2.a, res_ref);

      fail += check_union256i_d (res, res_ref);
    }

  if (fail != 0)
    abort ();
}