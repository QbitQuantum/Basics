__m256d test__mm256_loadu_pd(void* p) {
  // CHECK: load <4 x double>* %{{.*}}, align 1
  return _mm256_loadu_pd(p);
}