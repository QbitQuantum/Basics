static void
sse2_test (void)
{
  double a[2];
  __m128d x = _mm_set1_pd(3);
  _mm_storeu_pd(a,x);
  if (a[0] != 3.0 || a[1] != 3.0)
    __builtin_abort ();
}