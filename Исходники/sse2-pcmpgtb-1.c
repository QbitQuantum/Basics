test (__m128i s1, __m128i s2)
{
  return _mm_cmpgt_epi8 (s1, s2); 
}