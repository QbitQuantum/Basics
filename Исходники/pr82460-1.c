__m512i
f3 (__m512i x, __m512i y, __m512i z)
{
  return _mm512_permutex2var_epi8 (y, x, z);
}