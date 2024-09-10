static void
sse3_test_movddup_reg (double *i1, double *r)
{
  __m128d t1 = _mm_loadu_pd (i1);
  __m128d t2 = _mm_loadu_pd (&cnst1[0]);

  t1  = _mm_mul_pd (t1, t2);
  t2  = _mm_movedup_pd (t1);

  _mm_storeu_pd (r, t2);
}