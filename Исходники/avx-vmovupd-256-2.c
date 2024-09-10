test (double *e, __m256d a)
{
  return _mm256_storeu_pd (e, a);
}