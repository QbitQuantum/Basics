test (double *e, __m128d a)
{
  return _mm_storel_pd (e, a); 
}