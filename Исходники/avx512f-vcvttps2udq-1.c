void extern
avx512f_test (void)
{
  res = _mm512_cvttps_epu32 (s);
  res = _mm512_mask_cvttps_epu32 (res, m, s);
  res = _mm512_maskz_cvttps_epu32 (m, s);
  res = _mm512_cvtt_roundps_epu32 (s, _MM_FROUND_NO_EXC);
  res = _mm512_mask_cvtt_roundps_epu32 (res, m, s, _MM_FROUND_NO_EXC);
  res = _mm512_maskz_cvtt_roundps_epu32 (m, s, _MM_FROUND_NO_EXC);
}