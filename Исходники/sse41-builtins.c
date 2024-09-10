__m128i test_mm_stream_load_si128(__m128i const *a) {
  // CHECK-LABEL: test_mm_stream_load_si128
  // CHECK: load <2 x i64>, <2 x i64>* %{{.*}}, align 16, !nontemporal
  return _mm_stream_load_si128(a);
}