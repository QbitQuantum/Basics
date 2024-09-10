 SIMD_INLINE __m256i PermuteAndShiffle(__m256i bgr, __m256i permute, __m256i shuffle)
 {
     return _mm256_shuffle_epi8(_mm256_permutevar8x32_epi32(bgr, permute), shuffle);
 }