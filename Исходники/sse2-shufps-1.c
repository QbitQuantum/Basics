test (__m128 s1, __m128 s2)
{
  return _mm_shuffle_ps (s1, s2, MASK); 
}