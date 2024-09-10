__m128d
f3 (__m128d x, __m128d y)
{
  return _mm_cmpord_sd (x, y);
}