 SIMD_INLINE __m256i SquaredDifference(__m256i a, __m256i b)
 {
     const __m256i lo = SubUnpackedU8<0>(a, b);
     const __m256i hi = SubUnpackedU8<1>(a, b);
     return _mm256_add_epi32(_mm256_madd_epi16(lo, lo), _mm256_madd_epi16(hi, hi));
 }