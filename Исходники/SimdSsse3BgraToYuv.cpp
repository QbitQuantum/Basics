 template <bool align> SIMD_INLINE __m128i LoadAndConvertY16(const __m128i * bgra, __m128i & b16_r16, __m128i & g16_1)
 {
     __m128i _b16_r16[2], _g16_1[2];
     LoadPreparedBgra16<align>(bgra + 0, _b16_r16[0], _g16_1[0]);
     LoadPreparedBgra16<align>(bgra + 1, _b16_r16[1], _g16_1[1]);
     b16_r16 = _mm_hadd_epi32(_b16_r16[0], _b16_r16[1]);
     g16_1 = _mm_hadd_epi32(_g16_1[0], _g16_1[1]);
     return SaturateI16ToU8(_mm_add_epi16(K16_Y_ADJUST, _mm_packs_epi32(BgrToY32(_b16_r16[0], _g16_1[0]), BgrToY32(_b16_r16[1], _g16_1[1]))));
 }