void extern
avx512vl_test (void)
{
  y = _mm256_mask_xor_epi64 (y, m, y, y);
  y = _mm256_maskz_xor_epi64 (m, y, y);

  x = _mm_mask_xor_epi64 (x, m, x, x);
  x = _mm_maskz_xor_epi64 (m, x, x);
}