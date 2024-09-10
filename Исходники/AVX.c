void THFloatVector_adds_AVX(float *y, const float *x, const float c, const ptrdiff_t n) {
  ptrdiff_t i;
  __m256 YMM15 = _mm256_set_ps(c, c, c, c, c, c, c, c);
  __m256 YMM0, YMM1;
  for (i=0; i<=((n)-16); i+=16) {
    YMM0 = _mm256_loadu_ps(x+i);
    YMM1 = _mm256_loadu_ps(x+i+8);
    YMM0 = _mm256_add_ps(YMM0, YMM15);
    YMM1 = _mm256_add_ps(YMM1, YMM15);
    _mm256_storeu_ps(y+i, YMM0);
    _mm256_storeu_ps(y+i+8, YMM1);
  }
  for (; i<(n); i++) {
    y[i] = x[i] + c;
  }
}