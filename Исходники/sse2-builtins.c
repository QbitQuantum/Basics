long long test_mm_cvtsi128_si64(__m128i A) {
  // DAG-LABEL: test_mm_cvtsi128_si64
  // DAG: extractelement <2 x i64> %{{.*}}, i32 0
  //
  // ASM-LABEL: test_mm_cvtsi128_si64
  // ASM: movd
  return _mm_cvtsi128_si64(A);
}