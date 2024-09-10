int __attribute__((target("avx"))) bar(__m256i a) {
  return _mm256_extract_epi32(a, 3);
}