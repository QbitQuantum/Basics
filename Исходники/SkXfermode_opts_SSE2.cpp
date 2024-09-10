static inline __m128i SkMin32_SSE2(const __m128i& a, const __m128i& b) {
    __m128i cmp = _mm_cmplt_epi32(a, b);
    return _mm_or_si128(_mm_and_si128(cmp, a), _mm_andnot_si128(cmp, b));
}