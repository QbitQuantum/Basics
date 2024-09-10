int rotate_cpx_vector(int16_t *x,
                      int16_t *alpha,
                      int16_t *y,
                      uint32_t N,
                      uint16_t output_shift)
{
  // Multiply elementwise two complex vectors of N elements
  // x        - input 1    in the format  |Re0  Im0 |,......,|Re(N-1) Im(N-1)|
  //            We assume x1 with a dynamic of 15 bit maximum
  //
  // alpha      - input 2    in the format  |Re0 Im0|
  //            We assume x2 with a dynamic of 15 bit maximum
  //
  // y        - output     in the format  |Re0  Im0|,......,|Re(N-1) Im(N-1)|
  //
  // N        - the size f the vectors (this function does N cpx mpy. WARNING: N>=4;
  //
  // log2_amp - increase the output amplitude by a factor 2^log2_amp (default is 0)
  //            WARNING: log2_amp>0 can cause overflow!!

  uint32_t i;                 // loop counter


  simd_q15_t *y_128,alpha_128;
  int32_t *xd=(int32_t *)x; 

#if defined(__x86_64__) || defined(__i386__)
  __m128i shift = _mm_cvtsi32_si128(output_shift);
  register simd_q15_t m0,m1,m2,m3;

  ((int16_t *)&alpha_128)[0] = alpha[0];
  ((int16_t *)&alpha_128)[1] = -alpha[1];
  ((int16_t *)&alpha_128)[2] = alpha[1];
  ((int16_t *)&alpha_128)[3] = alpha[0];
  ((int16_t *)&alpha_128)[4] = alpha[0];
  ((int16_t *)&alpha_128)[5] = -alpha[1];
  ((int16_t *)&alpha_128)[6] = alpha[1];
  ((int16_t *)&alpha_128)[7] = alpha[0];
#elif defined(__arm__)
  int32x4_t shift;
  int32x4_t ab_re0,ab_re1,ab_im0,ab_im1,re32,im32;
  int16_t reflip[8]  __attribute__((aligned(16))) = {1,-1,1,-1,1,-1,1,-1};
  int32x4x2_t xtmp;

  ((int16_t *)&alpha_128)[0] = alpha[0];
  ((int16_t *)&alpha_128)[1] = alpha[1];
  ((int16_t *)&alpha_128)[2] = alpha[0];
  ((int16_t *)&alpha_128)[3] = alpha[1];
  ((int16_t *)&alpha_128)[4] = alpha[0];
  ((int16_t *)&alpha_128)[5] = alpha[1];
  ((int16_t *)&alpha_128)[6] = alpha[0];
  ((int16_t *)&alpha_128)[7] = alpha[1];
  int16x8_t bflip = vrev32q_s16(alpha_128);
  int16x8_t bconj = vmulq_s16(alpha_128,*(int16x8_t *)reflip);
  shift = vdupq_n_s32(-output_shift);
#endif
  y_128 = (simd_q15_t *) y;


  for(i=0; i<N>>2; i++) {
#if defined(__x86_64__) || defined(__i386__)
    m0 = _mm_setr_epi32(xd[0],xd[0],xd[1],xd[1]);
    m1 = _mm_setr_epi32(xd[2],xd[2],xd[3],xd[3]);
    m2 = _mm_madd_epi16(m0,alpha_128); //complex multiply. result is 32bit [Re Im Re Im]
    m3 = _mm_madd_epi16(m1,alpha_128); //complex multiply. result is 32bit [Re Im Re Im]
    m2 = _mm_sra_epi32(m2,shift);        // shift right by shift in order to  compensate for the input amplitude
    m3 = _mm_sra_epi32(m3,shift);        // shift right by shift in order to  compensate for the input amplitude

    y_128[0] = _mm_packs_epi32(m2,m3);        // pack in 16bit integers with saturation [re im re im re im re im]
#elif defined(__arm__)

  ab_re0 = vmull_s16(((int16x4_t*)xd)[0],((int16x4_t*)&bconj)[0]);
  ab_re1 = vmull_s16(((int16x4_t*)xd)[1],((int16x4_t*)&bconj)[1]);
  ab_im0 = vmull_s16(((int16x4_t*)xd)[0],((int16x4_t*)&bflip)[0]);
  ab_im1 = vmull_s16(((int16x4_t*)xd)[1],((int16x4_t*)&bflip)[1]);
  re32 = vshlq_s32(vcombine_s32(vpadd_s32(((int32x2_t*)&ab_re0)[0],((int32x2_t*)&ab_re0)[1]),
                                vpadd_s32(((int32x2_t*)&ab_re1)[0],((int32x2_t*)&ab_re1)[1])),
                   shift);
  im32 = vshlq_s32(vcombine_s32(vpadd_s32(((int32x2_t*)&ab_im0)[0],((int32x2_t*)&ab_im0)[1]),
                                vpadd_s32(((int32x2_t*)&ab_im1)[0],((int32x2_t*)&ab_im1)[1])),
                   shift);

  xtmp = vzipq_s32(re32,im32);
  
  y_128[0] = vcombine_s16(vmovn_s32(xtmp.val[0]),vmovn_s32(xtmp.val[1]));

#endif

    xd+=4;
    y_128+=1;
  }


  _mm_empty();
  _m_empty();

  return(0);
}