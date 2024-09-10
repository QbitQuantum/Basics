void extern
avx512dq_test (void)
{
  z = _mm512_range_round_ps (z, z, 15, _MM_FROUND_NO_EXC);
  z = _mm512_range_ps (z, z, 15);
  y = _mm256_range_ps (y, y, 15);
  x = _mm_range_ps (x, x, 15);

  z = _mm512_mask_range_round_ps (z, m16, z, z, 15, _MM_FROUND_NO_EXC);
  z = _mm512_mask_range_ps (z, m16, z, z, 15);
  y = _mm256_mask_range_ps (y, m8, y, y, 15);
  x = _mm_mask_range_ps (x, m8, x, x, 15);

  z = _mm512_maskz_range_round_ps (m16, z, z, 15, _MM_FROUND_NO_EXC);
  z = _mm512_maskz_range_ps (m16, z, z, 15);
  y = _mm256_maskz_range_ps (m8, y, y, 15);
  x = _mm_maskz_range_ps (m8, x, x, 15);
}