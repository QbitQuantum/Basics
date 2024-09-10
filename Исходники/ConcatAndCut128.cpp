 constexpr static __m128d RightShift( __m128d input ) {
   return (__m128d)_mm_srli_si128( (__m128i)input, SHIFT );
 }