test (__m128 a, __m64 *p)
{
  return _mm_loadh_pi (a, p); 
}