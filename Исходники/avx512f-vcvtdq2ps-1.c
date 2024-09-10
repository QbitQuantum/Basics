void extern
avx512f_test (void)
{
  res = _mm512_cvtepi32_ps (s);
  res = _mm512_mask_cvtepi32_ps (res, m, s);
  res = _mm512_maskz_cvtepi32_ps (m, s);
  res = _mm512_cvt_roundepi32_ps (s, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  res = _mm512_mask_cvt_roundepi32_ps (res, m, s, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
  res = _mm512_maskz_cvt_roundepi32_ps (m, s, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}