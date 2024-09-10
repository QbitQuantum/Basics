__m128d
f3 (__m128d x, __m128d y)
{
  return _mm_cmpunord_sd (x, y);
}