void static
avx512f_test (void)
{
  int i;
  union512 res;
  float res_ref[16];

  res.x = _mm512_setzero_ps ();

  for (i = 0; i < 16; i++)
    res_ref[i] = 0.0;

  if (check_union512 (res, res_ref))
    abort ();
}