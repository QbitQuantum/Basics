void extern
avx512f_test (void)
{
  x = _mm512_mask_compress_epi64 (x, m, x);
  x = _mm512_maskz_compress_epi64 (m, x);

  _mm512_mask_compressstoreu_epi64 (p, m, x);
}