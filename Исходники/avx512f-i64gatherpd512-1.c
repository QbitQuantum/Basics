void extern
avx512f_test (void)
{
  x = _mm512_i64gather_pd (idx, base, 8);
  x = _mm512_mask_i64gather_pd (x, m8, idx, base, 8);
}