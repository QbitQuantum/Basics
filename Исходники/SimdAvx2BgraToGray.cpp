 SIMD_INLINE __m256i BgraToGray32(__m256i bgra)
 {
     const __m256i g0a0 = _mm256_and_si256(_mm256_srli_si256(bgra, 1), K16_00FF);
     const __m256i b0r0 = _mm256_and_si256(bgra, K16_00FF);
     const __m256i weightedSum = _mm256_add_epi32(_mm256_madd_epi16(g0a0, K16_GREEN_0000), _mm256_madd_epi16(b0r0, K16_BLUE_RED));
     return _mm256_srli_epi32(_mm256_add_epi32(weightedSum, K32_ROUND_TERM), Base::BGR_TO_GRAY_AVERAGING_SHIFT);
 }