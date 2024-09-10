static void
avx2_test (void)
{
  union256i_w s1, s2, res;
  short res_ref[16];
  int i, j, sign = 1;
  int fail = 0;

  for (i = 0; i < 10; i++)
    {
      for (j = 0; j < 16; j++)
	{
	  s1.a[j] = j * i * sign;
	  s2.a[j] = (i + 2000) * sign;
	  sign = -sign;
	}

      res.x = _mm256_min_epi16 (s1.x, s2.x);

      compute_pminsw256 (s1.a, s2.a, res_ref);

      fail += check_union256i_w (res, res_ref);
    }

  if (fail != 0)
    abort ();
}