 template <bool align> SIMD_INLINE void VectorProduct(const __m256i & vertical, const uint8_t * horizontal, uint8_t * dst)
 {
     __m256i _horizontal = Load<align>((__m256i*)horizontal);
     __m256i lo = DivideI16By255(_mm256_mullo_epi16(vertical, _mm256_unpacklo_epi8(_horizontal, K_ZERO)));
     __m256i hi = DivideI16By255(_mm256_mullo_epi16(vertical, _mm256_unpackhi_epi8(_horizontal, K_ZERO)));
     Store<align>((__m256i*)dst, _mm256_packus_epi16(lo, hi));
 } 