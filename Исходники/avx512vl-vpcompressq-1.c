void extern
avx512vl_test (void)
{
  x1 = _mm256_mask_compress_epi64 (x1, m, x1);
  x2 = _mm_mask_compress_epi64 (x2, m, x2);

  x1 = _mm256_maskz_compress_epi64 (m, x1);
  x2 = _mm_maskz_compress_epi64 (m, x2);

  _mm256_mask_compressstoreu_epi64 (p, m, x1);
  _mm_mask_compressstoreu_epi64 (p, m, x2);
}