static void
scalarmultiply_f64_ns_sse2_unroll2 (double *dest, double *src1, double *val, int n)
{
  __m128d xmm1;

  /* Initial operations to align the destination pointer */
  for (; ((long)dest & 15) && (n > 0); n--) {
    *dest++ = *src1++ * *val;
  }
  xmm1 = _mm_load_pd1(val);
  for (; n >= 4; n -= 4) {
    __m128d xmm0;
    xmm0 = _mm_loadu_pd(src1);
    xmm0 = _mm_mul_pd(xmm0, xmm1);
    _mm_store_pd(dest, xmm0);
    xmm0 = _mm_loadu_pd(src1 + 2);
    xmm0 = _mm_mul_pd(xmm0, xmm1);
    _mm_store_pd(dest + 2, xmm0);
    dest += 4;
    src1 += 4;
  }
  for (; n > 0; n--) {
    *dest++ = *src1++ * *val;
  }
}