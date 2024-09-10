__m256d test_mm256_nmsub_pd(__m256d a, __m256d b, __m256d c) {
  // CHECK: @llvm.x86.fma.vfnmsub.pd.256
  // CHECK-ASM: vfnmsubpd %ymm{{.*}}, %ymm{{.*}}, %ymm{{.*}}, %ymm{{.*}}
  return _mm256_nmsub_pd(a, b, c);
}