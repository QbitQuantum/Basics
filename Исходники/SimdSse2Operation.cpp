 template <> SIMD_INLINE __m128i OperationBinary8u<SimdOperationBinary8uSaturatedSubtraction>(const __m128i & a, const __m128i & b)
 {
     return _mm_subs_epu8(a, b);
 }