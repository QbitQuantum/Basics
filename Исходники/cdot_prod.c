int32_t dot_product(int16_t *x,
                    int16_t *y,
                    uint32_t N, //must be a multiple of 8
                    uint8_t output_shift)
{

  uint32_t n;

#if defined(__x86_64__) || defined(__i386__)
  __m128i *x128,*y128,mmtmp1,mmtmp2,mmtmp3,mmcumul,mmcumul_re,mmcumul_im;
  __m64 mmtmp7;
  __m128i minus_i = _mm_set_epi16(-1,1,-1,1,-1,1,-1,1);
  int32_t result;

  x128 = (__m128i*) x;
  y128 = (__m128i*) y;

  mmcumul_re = _mm_setzero_si128();
  mmcumul_im = _mm_setzero_si128();

  for (n=0; n<(N>>2); n++) {

    //printf("n=%d, x128=%p, y128=%p\n",n,x128,y128);
    //    print_shorts("x",&x128[0]);
    //    print_shorts("y",&y128[0]);

    // this computes Re(z) = Re(x)*Re(y) + Im(x)*Im(y)
    mmtmp1 = _mm_madd_epi16(x128[0],y128[0]);
    //    print_ints("re",&mmtmp1);
    // mmtmp1 contains real part of 4 consecutive outputs (32-bit)

    // shift and accumulate results
    mmtmp1 = _mm_srai_epi32(mmtmp1,output_shift);
    mmcumul_re = _mm_add_epi32(mmcumul_re,mmtmp1);
    //    print_ints("re",&mmcumul_re);


    // this computes Im(z) = Re(x)*Im(y) - Re(y)*Im(x)
    mmtmp2 = _mm_shufflelo_epi16(y128[0],_MM_SHUFFLE(2,3,0,1));
    //    print_shorts("y",&mmtmp2);
    mmtmp2 = _mm_shufflehi_epi16(mmtmp2,_MM_SHUFFLE(2,3,0,1));
    //    print_shorts("y",&mmtmp2);
    mmtmp2 = _mm_sign_epi16(mmtmp2,minus_i);
    //        print_shorts("y",&mmtmp2);

    mmtmp3 = _mm_madd_epi16(x128[0],mmtmp2);
    //        print_ints("im",&mmtmp3);
    // mmtmp3 contains imag part of 4 consecutive outputs (32-bit)

    // shift and accumulate results
    mmtmp3 = _mm_srai_epi32(mmtmp3,output_shift);
    mmcumul_im = _mm_add_epi32(mmcumul_im,mmtmp3);
    //    print_ints("im",&mmcumul_im);

    x128++;
    y128++;
  }

  // this gives Re Re Im Im
  mmcumul = _mm_hadd_epi32(mmcumul_re,mmcumul_im);
  //  print_ints("cumul1",&mmcumul);

  // this gives Re Im Re Im
  mmcumul = _mm_hadd_epi32(mmcumul,mmcumul);

  //  print_ints("cumul2",&mmcumul);


  //mmcumul = _mm_srai_epi32(mmcumul,output_shift);
  // extract the lower half
  mmtmp7 = _mm_movepi64_pi64(mmcumul);
  //  print_ints("mmtmp7",&mmtmp7);
  // pack the result
  mmtmp7 = _mm_packs_pi32(mmtmp7,mmtmp7);
  //  print_shorts("mmtmp7",&mmtmp7);
  // convert back to integer
  result = _mm_cvtsi64_si32(mmtmp7);

  _mm_empty();
  _m_empty();

  return(result);

#elif defined(__arm__)
  int16x4_t *x_128=(int16x4_t*)x;
  int16x4_t *y_128=(int16x4_t*)y;
  int32x4_t tmp_re,tmp_im;
  int32x4_t tmp_re1,tmp_im1;
  int32x4_t re_cumul,im_cumul;
  int32x2_t re_cumul2,im_cumul2;
  int32x4_t shift = vdupq_n_s32(-output_shift); 
  int32x2x2_t result2;
  int16_t conjug[4]__attribute__((aligned(16))) = {-1,1,-1,1} ;

  re_cumul = vdupq_n_s32(0);
  im_cumul = vdupq_n_s32(0); 

  for (n=0; n<(N>>2); n++) {

    tmp_re  = vmull_s16(*x_128++, *y_128++);
    //tmp_re = [Re(x[0])Re(y[0]) Im(x[0])Im(y[0]) Re(x[1])Re(y[1]) Im(x[1])Im(y[1])] 
    tmp_re1 = vmull_s16(*x_128++, *y_128++);
    //tmp_re1 = [Re(x1[1])Re(x2[1]) Im(x1[1])Im(x2[1]) Re(x1[1])Re(x2[2]) Im(x1[1])Im(x2[2])] 
    tmp_re  = vcombine_s32(vpadd_s32(vget_low_s32(tmp_re),vget_high_s32(tmp_re)),
                           vpadd_s32(vget_low_s32(tmp_re1),vget_high_s32(tmp_re1)));
    //tmp_re = [Re(ch[0])Re(rx[0])+Im(ch[0])Im(ch[0]) Re(ch[1])Re(rx[1])+Im(ch[1])Im(ch[1]) Re(ch[2])Re(rx[2])+Im(ch[2]) Im(ch[2]) Re(ch[3])Re(rx[3])+Im(ch[3])Im(ch[3])] 

    tmp_im  = vmull_s16(vrev32_s16(vmul_s16(*x_128++,*(int16x4_t*)conjug)),*y_128++);
    //tmp_im = [-Im(ch[0])Re(rx[0]) Re(ch[0])Im(rx[0]) -Im(ch[1])Re(rx[1]) Re(ch[1])Im(rx[1])]
    tmp_im1 = vmull_s16(vrev32_s16(vmul_s16(*x_128++,*(int16x4_t*)conjug)),*y_128++);
    //tmp_im1 = [-Im(ch[2])Re(rx[2]) Re(ch[2])Im(rx[2]) -Im(ch[3])Re(rx[3]) Re(ch[3])Im(rx[3])]
    tmp_im  = vcombine_s32(vpadd_s32(vget_low_s32(tmp_im),vget_high_s32(tmp_im)),
                           vpadd_s32(vget_low_s32(tmp_im1),vget_high_s32(tmp_im1)));
    //tmp_im = [-Im(ch[0])Re(rx[0])+Re(ch[0])Im(rx[0]) -Im(ch[1])Re(rx[1])+Re(ch[1])Im(rx[1]) -Im(ch[2])Re(rx[2])+Re(ch[2])Im(rx[2]) -Im(ch[3])Re(rx[3])+Re(ch[3])Im(rx[3])]

    re_cumul = vqaddq_s32(re_cumul,vqshlq_s32(tmp_re,shift));
    im_cumul = vqaddq_s32(im_cumul,vqshlq_s32(tmp_im,shift));
  }
  
  re_cumul2 = vpadd_s32(vget_low_s32(re_cumul),vget_high_s32(re_cumul));
  im_cumul2 = vpadd_s32(vget_low_s32(im_cumul),vget_high_s32(im_cumul));
  re_cumul2 = vpadd_s32(re_cumul2,re_cumul2);
  im_cumul2 = vpadd_s32(im_cumul2,im_cumul2);
  result2   = vzip_s32(re_cumul2,im_cumul2);
  return(vget_lane_s32(result2.val[0],0));
#endif
}