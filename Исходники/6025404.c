void foo(__m128i *a, __m128i *b, __m128i c, __m128i d, __m128i e)
{
  *a = _mm_maddubs_epi16(c, d);
  *b = _mm_maddubs_epi16(c, e);
}