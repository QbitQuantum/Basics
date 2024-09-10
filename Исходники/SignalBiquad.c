void __hv_biquad_f_win32(SignalBiquad *o, hv_bInf_t *_bIn, hv_bInf_t *_bX0, hv_bInf_t *_bX1, hv_bInf_t *_bX2, hv_bInf_t *_bY1, hv_bInf_t *_bY2, hv_bOutf_t bOut) {
  hv_bInf_t bIn = *_bIn;
  hv_bInf_t bX0 = *_bX0;
  hv_bInf_t bX1 = *_bX1;
  hv_bInf_t bX2 = *_bX2;
  hv_bInf_t bY1 = *_bY1;
  hv_bInf_t bY2 = *_bY2;
#else
void __hv_biquad_f(SignalBiquad *o, hv_bInf_t bIn, hv_bInf_t bX0, hv_bInf_t bX1, hv_bInf_t bX2, hv_bInf_t bY1, hv_bInf_t bY2, hv_bOutf_t bOut) {
#endif
#if HV_SIMD_AVX
  __m256 a = _mm256_mul_ps(bIn, bX0);
  __m256 b = _mm256_mul_ps(o->xm1, bX1);
  __m256 c = _mm256_mul_ps(o->xm2, bX2);
  __m256 d = _mm256_add_ps(a, b);
  __m256 e = _mm256_add_ps(c, d); // bIn*bX0 + o->x1*bX1 + o->x2*bX2
  float y0 = e[0] - o->ym1*bY1[0] - o->ym2*bY2[0];
  float y1 = e[1] - y0*bY1[1] - o->ym1*bY2[1];
  float y2 = e[2] - y1*bY1[2] - y0*bY2[2];
  float y3 = e[3] - y2*bY1[3] - y1*bY2[3];
  float y4 = e[4] - y3*bY1[4] - y2*bY2[4];
  float y5 = e[5] - y4*bY1[5] - y3*bY2[5];
  float y6 = e[6] - y5*bY1[6] - y4*bY2[6];
  float y7 = e[7] - y6*bY1[7] - y5*bY2[7];

  o->xm2 = o->xm1;
  o->xm1 = bIn;
  o->ym1 = y7;
  o->ym2 = y6;

  *bOut = _mm256_set_ps(y7, y6, y5, y4, y3, y2, y1, y0);
#elif HV_SIMD_SSE
  __m128 a = _mm_mul_ps(bIn, bX0);
  __m128 b = _mm_mul_ps(o->xm1, bX1);
  __m128 c = _mm_mul_ps(o->xm2, bX2);
  __m128 d = _mm_add_ps(a, b);
  __m128 e = _mm_add_ps(c, d);

  const float *const bbe = (float *) &e;
  const float *const bbY1 = (float *) &bY1;
  const float *const bbY2 = (float *) &bY2;

  float y0 = bbe[0] - o->ym1*bbY1[0] - o->ym2*bbY2[0];
  float y1 = bbe[1] - y0*bbY1[1] - o->ym1*bbY2[1];
  float y2 = bbe[2] - y1*bbY1[2] - y0*bbY2[2];
  float y3 = bbe[3] - y2*bbY1[3] - y1*bbY2[3];

  o->xm2 = o->xm1;
  o->xm1 = bIn;
  o->ym1 = y3;
  o->ym2 = y2;

  *bOut = _mm_set_ps(y3, y2, y1, y0);
#elif HV_SIMD_NEON
  float32x4_t a = vmulq_f32(bIn, bX0);
  float32x4_t b = vmulq_f32(o->xm1, bX1);
  float32x4_t c = vmulq_f32(o->xm2, bX2);
  float32x4_t d = vaddq_f32(a, b);
  float32x4_t e = vaddq_f32(c, d);
  float y0 = e[0] - o->ym1*bY1[0] - o->ym2*bY2[0];
  float y1 = e[1] - y0*bY1[1] - o->ym1*bY2[1];
  float y2 = e[2] - y1*bY1[2] - y0*bY2[2];
  float y3 = e[3] - y2*bY1[3] - y1*bY2[3];

  o->xm2 = o->xm1;
  o->xm1 = bIn;
  o->ym1 = y3;
  o->ym2 = y2;

  *bOut = (float32x4_t) {y0, y1, y2, y3};
#else
  const float y = bIn*bX0 + o->xm1*bX1 + o->xm2*bX2 - o->ym1*bY1 - o->ym2*bY2;
  o->xm2 = o->xm1; o->xm1 = bIn;
  o->ym2 = o->ym1; o->ym1 = y;
  *bOut = y;
#endif
}