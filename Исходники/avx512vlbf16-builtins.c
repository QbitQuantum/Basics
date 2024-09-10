__m512bh test_mm512_maskz_cvtne2ps2bf16(__m512 A, __m512 B, __mmask32 U) {
  // CHECK-LABEL: @test_mm512_maskz_cvtne2ps2bf16
  // CHECK: @llvm.x86.avx512bf16.cvtne2ps2bf16.512
  // CHECK: select <32 x i1> %{{.*}}, <32 x i16> %{{.*}}, <32 x i16> %{{.*}}
  // CHECK: ret <32 x i16> %{{.*}}
  return _mm512_maskz_cvtne2ps_pbh(U, A, B);
}