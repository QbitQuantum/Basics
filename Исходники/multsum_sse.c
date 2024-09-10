static void
multsum_f64_sse2_unroll4(double *dest,
     const double *src1, int sstr1,
     const double *src2, int sstr2,
     int n)
{
  __m128d t1, t2;
  union {
    __m128d reg;
    double vals[2];
  } sum;
  int i = 0;

  sum.reg = _mm_setzero_pd();
  while (i < n-3) {
    MULTSUM_SSE2_STRIDED(0);
    MULTSUM_SSE2_STRIDED(2);

    OIL_INCREMENT(src1, 4*sstr1);
    OIL_INCREMENT(src2, 4*sstr2);
    i += 4;
  }
  while (i < n-1) {
    MULTSUM_SSE2_STRIDED(0);

    OIL_INCREMENT(src1, 2*sstr1);
    OIL_INCREMENT(src2, 2*sstr2);
    i+=2;
  }
  *dest = sum.vals[0] + sum.vals[1];
  if (i < n) {
    *dest += (OIL_GET(src1,0,double)*OIL_GET(src2,0,double));
  }