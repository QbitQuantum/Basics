void extern
avx512dq_test (void)
{
  z = _mm512_or_pd (z, z);
  z = _mm512_mask_or_pd (z, m, z, z);
  z = _mm512_maskz_or_pd (m, z, z);

  y = _mm256_mask_or_pd (y, m, y, y);
  y = _mm256_maskz_or_pd (m, y, y);

  x = _mm_mask_or_pd (x, m, x, x);
  x = _mm_maskz_or_pd (m, x, x);
}