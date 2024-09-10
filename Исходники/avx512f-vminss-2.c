void
avx512f_test (void)
{
  int i, sign;
  union128 res1, res2, res3, src1, src2;
  MASK_TYPE mask = MASK_VALUE;
  float res_ref[SIZE];

  sign = -1;
  for (i = 0; i < SIZE; i++)
    {
      src1.a[i] = 1.5 + 34.67 * i * sign;
      src2.a[i] = -22.17 * i * sign + 1.0;
      sign = sign * -1;
    }
  for (i = 0; i < SIZE; i++)
      res2.a[i] = DEFAULT_VALUE;

  res1.x = _mm_min_round_ss (src1.x, src2.x, _MM_FROUND_NO_EXC);
  res2.x = _mm_mask_min_round_ss (res2.x, mask, src1.x, src2.x, _MM_FROUND_NO_EXC);
  res3.x = _mm_maskz_min_round_ss (mask, src1.x, src2.x, _MM_FROUND_NO_EXC);

  calc_min (res_ref, src1.a, src2.a);

  if (check_union128 (res1, res_ref))
    abort();
  
  MASK_MERGE () (res_ref, mask, 1);
  if (check_union128 (res2, res_ref))
    abort ();

  MASK_ZERO () (res_ref, mask, 1);
  if (check_union128 (res3, res_ref))
    abort ();
}