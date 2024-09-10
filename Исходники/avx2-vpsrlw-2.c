void static
avx2_test (void)
{
  union256i_w s1, res;
  union128i_q s2;
  short res_ref[16];
  int i, j;
  int fail = 0;

  for (i = 0; i < 10; i++)
    {
      for (j = 0; j < 16; j++)
	s1.a[j] = j * i;

      s2.a[0] = i;

      res.x = _mm256_srl_epi16 (s1.x, s2.x);

      compute_psrlw256 (s1.a, s2.a, res_ref);

      fail += check_union256i_w (res, res_ref);

      if (fail)
	{
	  for (j = 0; j < 16; ++j)
	    printf ("%d <->%d\n", res.a[j], res_ref[j]);
	  abort ();
	}
    }

  if (fail != 0)
    abort ();
}