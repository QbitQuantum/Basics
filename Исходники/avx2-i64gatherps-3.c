void extern
avx2_test (void)
{
  x = _mm_mask_i64gather_ps (x, base, idx, x, 1);
}