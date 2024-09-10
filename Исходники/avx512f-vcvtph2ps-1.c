void extern
avx512f_test (void)
{
  y = _mm512_cvtph_ps (x);
  y = _mm512_mask_cvtph_ps (y, 4, x);
  y = _mm512_maskz_cvtph_ps (6, x);
  y = _mm512_cvt_roundph_ps (x, _MM_FROUND_NO_EXC);
  y = _mm512_mask_cvt_roundph_ps (y, 4, x, _MM_FROUND_NO_EXC);
  y = _mm512_maskz_cvt_roundph_ps (6, x, _MM_FROUND_NO_EXC);
}