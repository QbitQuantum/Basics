void static
avx2_test (void)
{
  union128 s1;
  union256 res;
  float res_ref[8];
  int i, j;
  int fail = 0;

  for (i = 0; i < 10; i++)
    {
      s1.a[0] = i * 3.14;

      res.x = _mm256_broadcastss_ps (s1.x);

      for (j = 0; j < 8; j++)
	memcpy (res_ref + j, s1.a, 4);

      fail += check_union256 (res, res_ref);
    }

  if (fail != 0)
    abort ();

}