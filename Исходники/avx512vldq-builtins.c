__m256 test_mm256_maskz_xor_ps (__mmask8 __U, __m256 __A, __m256 __B) {
  // CHECK-LABEL: @test_mm256_maskz_xor_ps
  // CHECK: xor <8 x i32> %{{.*}}, %{{.*}}
  // CHECK: select <8 x i1> %{{.*}}, <8 x float> %{{.*}}, <8 x float> %{{.*}}
  return (__m256) _mm256_maskz_xor_ps (__U, __A, __B);
}