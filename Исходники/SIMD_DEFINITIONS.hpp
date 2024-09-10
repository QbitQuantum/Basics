/*
 * Bitwise NOT operation for reals
 */
inline __m256 not_ps(const __m256 x) {
    static const __m256i mask = _mm256_set1_epi32(0xFFFFFFFF);
    return _mm256_xor_ps(CAST_INT_TO_REAL_V(mask), x);
}