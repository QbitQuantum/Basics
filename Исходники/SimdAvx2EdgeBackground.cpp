 SIMD_INLINE __m256i AdjustEdge(const __m256i &count, const __m256i & value, const __m256i & mask, const __m256i & threshold)
 {
     const __m256i inc = _mm256_and_si256(mask, Greater8u(count, threshold));
     const __m256i dec = _mm256_and_si256(mask, Lesser8u(count, threshold));
     return _mm256_subs_epu8(_mm256_adds_epu8(value, inc), dec);
 }