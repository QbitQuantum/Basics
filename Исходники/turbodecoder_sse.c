/* Computes the horizontal MAX from 8 16-bit integers using the minpos_epu16 SSE4.1 instruction */
static inline int16_t hMax(__m128i buffer)
{
  __m128i tmp1 = _mm_sub_epi8(_mm_set1_epi16(0x7FFF), buffer);
  __m128i tmp3 = _mm_minpos_epu16(tmp1);
  return (int16_t)(_mm_cvtsi128_si32(tmp3));
}