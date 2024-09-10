void static
avx2_test (void)
{
  union256i_b s1, res;
  char res_ref[32];
  int i, j;
  int fail = 0;

  for (i = 0; i < 10; i++)
    {
      for (j = 0; j < 32; j++)
	s1.a[j] = j * i;

      res.x = _mm256_slli_si256 (s1.x, N);

      compute_pslldq256 (s1.a, res_ref);

      fail += check_union256i_b (res, res_ref);
    }

  if (fail != 0)
    abort ();
}