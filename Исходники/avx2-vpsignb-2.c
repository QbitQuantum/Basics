void static
avx2_test (void)
{
  union256i_b s1, s2, res;
  char res_ref[32];
  int i, j;
  int fail = 0;

  for (i = 0; i < 10; i++)
    {
      for (j = 0; j < 32; j++)
	{
	  s1.a[j] = j * i;
	  s2.a[j] = j + 20;
	}

      res.x = _mm256_sign_epi8 (s1.x, s2.x);
      compute_psignb256 (s1.a, s2.a, res_ref);

      fail += check_union256i_b (res, res_ref);
    }

  if (fail != 0)
    abort ();
}