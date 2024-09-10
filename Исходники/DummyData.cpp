void convert_f32_bf16(float* in, libxsmm_bfloat16* out, int len)
{
  int i;

#ifdef _OPENMP
#pragma omp parallel for private(i)
#endif
  for ( i = 0; i < len; i+=16 ) {
    __m512  vfp32  = gxm_fp32_to_bfp16_rne_adjustment_avx512f( _mm512_loadu_ps( in+i ) );
    __m256i vbfp16 = gxm_fp32_to_bfp16_truncate_avx512f( vfp32 );
    _mm256_storeu_si256( (__m256i*)(out+i), vbfp16 );
  }
}