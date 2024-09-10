void extern
avx512f_test (void)
{
  x = _mm512_mask_compress_epi8 (x, m, x);
  x = _mm512_maskz_compress_epi8 (m, x);

  _mm512_mask_compressstoreu_epi8 (p, m, x);
}