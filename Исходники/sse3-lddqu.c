static void
sse3_test_lddqu (double *i1, double *r)
{
  __m128i t1 = _mm_lddqu_si128 ((__m128i *) i1);

  _mm_storeu_si128 ((__m128i *) r, t1);
}