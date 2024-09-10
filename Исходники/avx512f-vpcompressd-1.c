void extern
avx512f_test (void)
{
  x = _mm512_mask_compress_epi32 (x, m, x);
  x = _mm512_maskz_compress_epi32 (m, x);

  _mm512_mask_compressstoreu_epi32 (p, m, x);
}