 SIMD_INLINE __m128i TextureBoostedSaturatedGradient16(__m128i difference, __m128i saturation, const __m128i & boost)
 {
     return _mm_mullo_epi16(_mm_max_epi16(K_ZERO, _mm_add_epi16(saturation, _mm_min_epi16(difference, saturation))), boost);
 }