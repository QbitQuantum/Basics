void extern
avx512f_test (void)
{
  res = _mm512_cvtps_epi32 (s);
  res = _mm512_mask_cvtps_epi32 (res, m, s);
  res = _mm512_maskz_cvtps_epi32 (m, s);
  res = _mm512_cvt_roundps_epi32 (s, _MM_FROUND_TO_NEAREST_INT | _MM_FROUND_NO_EXC);
  res = _mm512_mask_cvt_roundps_epi32 (res, m, s, _MM_FROUND_TO_POS_INF | _MM_FROUND_NO_EXC);
  res = _mm512_maskz_cvt_roundps_epi32 (m, s, _MM_FROUND_TO_ZERO | _MM_FROUND_NO_EXC);
}