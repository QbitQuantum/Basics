__m512i
f2 (__m512i x, __m512i y, __mmask16 m, int a)
{
  return _mm512_mask_srai_epi32 (y, m, x, a);
}