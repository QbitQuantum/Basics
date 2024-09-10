void extern
avx512f_test (void)
{
  x = _mm512_mask_compress_ps (x, m, x);
  x = _mm512_maskz_compress_ps (m, x);

  _mm512_mask_compressstoreu_ps (p, m, x);
}