unsigned int vp9_avg_4x4_sse2(const uint8_t *s, int p) {
  __m128i s0, s1, u0;
  unsigned int avg = 0;
  u0  = _mm_setzero_si128();
  s0 = _mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i *)(s)), u0);
  s1 = _mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i *)(s + p)), u0);
  s0 = _mm_adds_epu16(s0, s1);
  s1 = _mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i *)(s + 2 * p)), u0);
  s0 = _mm_adds_epu16(s0, s1);
  s1 = _mm_unpacklo_epi8(_mm_loadl_epi64((const __m128i *)(s + 3 * p)), u0);
  s0 = _mm_adds_epu16(s0, s1);

  s0 = _mm_adds_epu16(s0, _mm_srli_si128(s0, 4));
  s0 = _mm_adds_epu16(s0, _mm_srli_epi64(s0, 16));
  avg = _mm_extract_epi16(s0, 0);
  return (avg + 8) >> 4;
}