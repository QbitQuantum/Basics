__m128i long2vector(long long __i)
{
  return _mm_set_epi64x (0, __i);
}