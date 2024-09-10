__m128i test_mm_i64gather_epi64(long long const *b, __m128i c) {
  // CHECK: @llvm.x86.avx2.gather.q.q
  return _mm_i64gather_epi64(b, c, 2);
}