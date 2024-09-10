__m256d test_mm256_fmsubadd_pd(__m256d a, __m256d b, __m256d c) {
  // CHECK: @llvm.x86.fma.vfmsubadd.pd.256
  return _mm256_fmsubadd_pd(a, b, c);
}