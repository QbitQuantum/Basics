static void
avx2_test (void)
{
  union256i_w s1, s2, res;
  unsigned short res_ref[16];
  int i, j;
  int fail = 0;

  for (i = 0; i < 10; i++)
    {
      for (j = 0; j < 16; j++)
	{
	  s1.a[j] = j * i;
	  s2.a[j] = i + 2000;
	}

      res.x = _mm256_min_epu16 (s1.x, s2.x);

      compute_pminuw256 ((unsigned short *) s1.a,
			 (unsigned short *) s2.a, (unsigned short *) res_ref);

      fail += check_union256i_w (res, res_ref);
    }

  if (fail != 0)
    abort ();
}