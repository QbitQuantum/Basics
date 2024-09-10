void extern
avx512vl_test (void)
{
  x1 = _mm256_mask_compress_ps (x1, m, x1);
  x2 = _mm_mask_compress_ps (x2, m, x2);

  x1 = _mm256_maskz_compress_ps (m, x1);
  x2 = _mm_maskz_compress_ps (m, x2);

  _mm256_mask_compressstoreu_ps (p, m, x1);
  _mm_mask_compressstoreu_ps (p, m, x2);
}