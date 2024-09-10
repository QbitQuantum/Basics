void extern
avx512f_test (void)
{
  res = _mm512_cvtpd_epi32 (s);
  res = _mm512_mask_cvtpd_epi32 (res, m, s);
  res = _mm512_maskz_cvtpd_epi32 (m, s);
  res = _mm512_cvt_roundpd_epi32 (s, _MM_FROUND_TO_NEAREST_INT);
  res = _mm512_mask_cvt_roundpd_epi32 (res, m, s, _MM_FROUND_TO_POS_INF);
  res = _mm512_maskz_cvt_roundpd_epi32 (m, s, _MM_FROUND_TO_ZERO);
}