 SIMD_INLINE void InterpolateX2(const __m128i * alpha, __m128i * buffer)
 {
     __m128i src = _mm_load_si128(buffer);
     __m128i a = _mm_load_si128(alpha);
     __m128i u = _mm_madd_epi16(_mm_and_si128(src, K16_00FF), a);
     __m128i v = _mm_madd_epi16(_mm_and_si128(_mm_srli_si128(src, 1), K16_00FF), a);
     _mm_store_si128(buffer, _mm_or_si128(u, _mm_slli_si128(v, 2)));
 }