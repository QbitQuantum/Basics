int mult_cpx_vector(int16_t *x1, //Q15
                    int16_t *x2,//Q13
                    int16_t *y,
                    uint32_t N,
                    int output_shift)
{
  // Multiply elementwise x1 with x2.
  // x1       - input 1    in the format  |Re0 Im0 Re1 Im1|,......,|Re(N-2)  Im(N-2) Re(N-1) Im(N-1)|
  //            We assume x1 with a dinamic of 15 bit maximum
  //
  // x2       - input 2    in the format  |Re0 Im0 Re1 Im1|,......,|Re(N-2)  Im(N-2) Re(N-1) Im(N-1)|
  //            We assume x2 with a dinamic of 14 bit maximum
  ///
  // y        - output     in the format  |Re0 Im0 Re1 Im1|,......,|Re(N-2)  Im(N-2) Re(N-1) Im(N-1)|
  //
  // N        - the size f the vectors (this function does N cpx mpy. WARNING: N>=4;
  //
  // output_shift  - shift to be applied to generate output
  uint32_t i;                 // loop counter
  simd_q15_t *x1_128;
  simd_q15_t *x2_128;
  simd_q15_t *y_128;
  simd_q15_t tmp_re,tmp_im;
  simd_q15_t tmpy0,tmpy1;
  x1_128 = (simd_q15_t *)&x1[0];
  x2_128 = (simd_q15_t *)&x2[0];
  y_128  = (simd_q15_t *)&y[0];
  //print_shorts("x1_128:",&x1_128[0]);
 // print_shorts("x2_128:",&x2_128[0]);

  //right shift by 13 while p_a * x0 and 15 while
  // we compute 4 cpx multiply for each loop
  for(i=0; i<(N>>2); i++) {
    tmp_re = _mm_sign_epi16(*x1_128,*(__m128i*)&conjug2[0]);// Q15
    //print_shorts("tmp_re1:",&tmp_re[i]);
    tmp_re = _mm_madd_epi16(tmp_re,*x2_128); //Q28
    //print_ints("tmp_re2:",&tmp_re[i]);
    tmp_im = _mm_shufflelo_epi16(*x1_128,_MM_SHUFFLE(2,3,0,1)); //Q15
    //print_shorts("tmp_im1:",&tmp_im[i]);
    tmp_im = _mm_shufflehi_epi16(tmp_im,_MM_SHUFFLE(2,3,0,1)); //Q15
    //print_shorts("tmp_im2:",&tmp_im[i]);
    tmp_im = _mm_madd_epi16(tmp_im, *x2_128); //Q28
    //print_ints("tmp_im3:",&tmp_im[i]);
    tmp_re = _mm_srai_epi32(tmp_re,output_shift);//Q(28-shift)
    //print_ints("tmp_re shifted:",&tmp_re[i]);
    tmp_im = _mm_srai_epi32(tmp_im,output_shift); //Q(28-shift)
    //print_ints("tmp_im shifted:",&tmp_im[i]);
    tmpy0  = _mm_unpacklo_epi32(tmp_re,tmp_im); //Q(28-shift)
    //print_ints("unpack lo :",&tmpy0[i]);
    tmpy1  = _mm_unpackhi_epi32(tmp_re,tmp_im); //Q(28-shift)
    //print_ints("mrc rho0:",&tmpy1[i]);
    *y_128 = _mm_packs_epi32(tmpy0,tmpy1); //must be Q15
    //print_shorts("*y_128:",&y_128[i]);
    x1_128++;
    x2_128++;
    y_128++;
  }
  _mm_empty();
  _m_empty();
  return(0);
}