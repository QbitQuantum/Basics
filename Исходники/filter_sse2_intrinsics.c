/* Bytewise c ? t : e. */
static __m128i if_then_else(__m128i c, __m128i t, __m128i e) {
#if PNG_INTEL_SSE_IMPLEMENTATION >= 3
   return _mm_blendv_epi8(e,t,c);
#else
   return _mm_or_si128(_mm_and_si128(c, t), _mm_andnot_si128(c, e));
#endif
}