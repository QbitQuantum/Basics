void test_mm512_mask_prefetch_i64scatter_ps(void *addr, __mmask16 mask, __m512i index) {
  // CHECK-LABEL: @test_mm512_mask_prefetch_i64scatter_ps
  // CHECK: @llvm.x86.avx512.scatterpf.qps.512
  return _mm512_mask_prefetch_i64scatter_ps(addr, mask, index, 1, 2); 
}