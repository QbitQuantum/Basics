// Compute the sum of all pixel differences of this MB.
static INLINE int sum_diff_16x1(__m128i acc_diff) {
  const __m128i k_1 = _mm_set1_epi16(1);
  const __m128i acc_diff_lo =
      _mm_srai_epi16(_mm_unpacklo_epi8(acc_diff, acc_diff), 8);
  const __m128i acc_diff_hi =
      _mm_srai_epi16(_mm_unpackhi_epi8(acc_diff, acc_diff), 8);
  const __m128i acc_diff_16 = _mm_add_epi16(acc_diff_lo, acc_diff_hi);
  const __m128i hg_fe_dc_ba = _mm_madd_epi16(acc_diff_16, k_1);
  const __m128i hgfe_dcba =
      _mm_add_epi32(hg_fe_dc_ba, _mm_srli_si128(hg_fe_dc_ba, 8));
  const __m128i hgfedcba =
      _mm_add_epi32(hgfe_dcba, _mm_srli_si128(hgfe_dcba, 4));
  return _mm_cvtsi128_si32(hgfedcba);
}