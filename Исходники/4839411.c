__m128i foo (__m128i a)
{
  __m128i tmp = a;

  return _mm_alignr_epi8(tmp, a, 4);
}