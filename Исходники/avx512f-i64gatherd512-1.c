void extern
avx512f_test (void)
{
  x = _mm512_i64gather_epi32 (idx, base, 8);
  x = _mm512_mask_i64gather_epi32 (x, m8, idx, base, 8);
}