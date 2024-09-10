void static
avx2_test (void)
{
  union128i_q s1, s2, res;
  long long int res_ref[2];
  int i, j, sign = 2;
  int fail = 0;

  for (i = 0; i < 10; i++)
    {
      for (j = 0; j < 2; j++)
	{
	  s1.a[j] = j * i * sign;
	  s2.a[j] = (j + i) >> 2;
	  sign = -sign;
	}

      res.x = _mm_sllv_epi64 (s1.x, s2.x);

      compute_psllvq128 (s1.a, s2.a, res_ref);

      fail += check_union128i_q (res, res_ref);
    }

  if (fail != 0)
    abort ();
}