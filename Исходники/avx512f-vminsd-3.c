void
avx512f_test (void)
{
  int i, sign;
  union128d res1, res2, res3, res4, src1, src2;
  MASK_TYPE mask = 0;
  double res_ref[SIZE];

  sign = -1;
  for (i = 0; i < SIZE; i++)
    {
      src1.a[i] = 1.5 + 34.67 * i * sign;
      src2.a[i] = -22.17 * i * sign + 1.0;
      res1.a[i] = DEFAULT_VALUE;
      res3.a[i] = DEFAULT_VALUE;
      sign = sign * -1;
    }
 
  res1.x = _mm_mask_min_sd (res1.x, mask, src1.x, src2.x);
  res2.x = _mm_maskz_min_sd (mask, src1.x, src2.x);
  res3.x = _mm_mask_min_round_sd (res3.x, mask, src1.x, src2.x, _MM_FROUND_NO_EXC);
  res4.x = _mm_maskz_min_round_sd (mask, src1.x, src2.x, _MM_FROUND_NO_EXC);

  calc_min (res_ref, src1.a, src2.a);

  MASK_MERGE (d) (res_ref, mask, 1);
  if (check_union128d (res1, res_ref))
    abort ();

  MASK_ZERO (d) (res_ref, mask, 1);
  if (check_union128d (res2, res_ref))
    abort ();

  calc_min (res_ref, src1.a, src2.a);

  MASK_MERGE (d) (res_ref, mask, 1);
  if (check_union128d (res3, res_ref))
    abort ();

  MASK_ZERO (d) (res_ref, mask, 1);
  if (check_union128d (res4, res_ref))
    abort ();
}