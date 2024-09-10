__m128i
foo (const __m128i x, const __m128i y)
{
  return _mm_cmpeq_epi64 (x, y);
}