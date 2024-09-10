static REAL dotp_sse(REAL a[], REAL b[])
{
#ifdef __SSE__
  /* This is taken from speex's inner product implementation */
  int j;
  REAL sum;
  __m128 acc = _mm_setzero_ps();

  for (j=0;j<NLMS_LEN;j+=8)
  {
    acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load_ps(a+j), _mm_loadu_ps(b+j)));
    acc = _mm_add_ps(acc, _mm_mul_ps(_mm_load_ps(a+j+4), _mm_loadu_ps(b+j+4)));
  }
  acc = _mm_add_ps(acc, _mm_movehl_ps(acc, acc));
  acc = _mm_add_ss(acc, _mm_shuffle_ps(acc, acc, 0x55));
  _mm_store_ss(&sum, acc);

  return sum;
#else
  return dotp(a, b);
#endif
}