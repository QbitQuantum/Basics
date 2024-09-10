 SIMD_INLINE __m128i BgraToGray32(__m128i bgra)
 {
     const __m128i g0a0 = _mm_and_si128(_mm_srli_si128(bgra, 1), K16_00FF);
     const __m128i b0r0 = _mm_and_si128(bgra, K16_00FF);
     const __m128i weightedSum = _mm_add_epi32(_mm_madd_epi16(g0a0, K16_GREEN_0000), _mm_madd_epi16(b0r0, K16_BLUE_RED));
     return _mm_srli_epi32(_mm_add_epi32(weightedSum, K32_ROUND_TERM), Base::BGR_TO_GRAY_AVERAGING_SHIFT);
 }