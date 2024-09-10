static inline int8_t _mm_hmax_epi8_rpl(__m128i a) {
    a = _mm_max_epi8(a, _mm_srli_si128(a, 8));
    a = _mm_max_epi8(a, _mm_srli_si128(a, 4));
    a = _mm_max_epi8(a, _mm_srli_si128(a, 2));
    a = _mm_max_epi8(a, _mm_srli_si128(a, 1));
    return _mm_extract_epi8(a, 0);
}