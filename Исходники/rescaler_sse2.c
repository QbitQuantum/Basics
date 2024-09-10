static WEBP_INLINE void ProcessRow_Floor_SSE2(const __m128i* const A0,
                                              const __m128i* const A1,
                                              const __m128i* const A2,
                                              const __m128i* const A3,
                                              const __m128i* const mult,
                                              uint8_t* const dst) {
  const __m128i mask = _mm_set_epi32(0xffffffffu, 0, 0xffffffffu, 0);
  const __m128i B0 = _mm_mul_epu32(*A0, *mult);
  const __m128i B1 = _mm_mul_epu32(*A1, *mult);
  const __m128i B2 = _mm_mul_epu32(*A2, *mult);
  const __m128i B3 = _mm_mul_epu32(*A3, *mult);
  const __m128i D0 = _mm_srli_epi64(B0, WEBP_RESCALER_RFIX);
  const __m128i D1 = _mm_srli_epi64(B1, WEBP_RESCALER_RFIX);
#if (WEBP_RESCALER_RFIX < 32)
  const __m128i D2 =
      _mm_and_si128(_mm_slli_epi64(B2, 32 - WEBP_RESCALER_RFIX), mask);
  const __m128i D3 =
      _mm_and_si128(_mm_slli_epi64(B3, 32 - WEBP_RESCALER_RFIX), mask);
#else
  const __m128i D2 = _mm_and_si128(B2, mask);
  const __m128i D3 = _mm_and_si128(B3, mask);
#endif
  const __m128i E0 = _mm_or_si128(D0, D2);
  const __m128i E1 = _mm_or_si128(D1, D3);
  const __m128i F = _mm_packs_epi32(E0, E1);
  const __m128i G = _mm_packus_epi16(F, F);
  _mm_storel_epi64((__m128i*)dst, G);
}