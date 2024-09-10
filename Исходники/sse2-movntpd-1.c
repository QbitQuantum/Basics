test (double *p, __m128d s)
{
  return _mm_stream_pd (p, s); 
}