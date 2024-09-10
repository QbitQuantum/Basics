/******************************************************************
*
* SPLIT RADIX PRECOMPUTED AND VECTORIZED NON RECURSIVE FFT MULTIPLICATION
*
******************************************************************/
void sr_vector_nonrec_mul(ring_t *r, const ring_t *x, const ring_t *y){
  fft_vector_nonrec_forward(&vec_x,x);
  fft_vector_nonrec_forward(&vec_y,y);
  __m256d real_x,imag_x,real_y,imag_y,imag_temp,real_temp;
  // double a,b,c,d;
  for (int i = 0; i < CPLXDIM; i+=4)
  {
    real_x = _mm256_load_pd(vec_x.real+i);
    imag_x = _mm256_load_pd(vec_x.imag+i);
    real_y = _mm256_load_pd(vec_y.real+i);
    imag_y = _mm256_load_pd(vec_y.imag+i);

    //(a + ib) * (c + id) = (ac - bd) + i(ad+bc)
    //real_temp = bd
    real_temp = _mm256_mul_pd(imag_x,imag_y);
    //imag_temp = ad
    imag_temp = _mm256_mul_pd(real_x,imag_y);
    //REPLACED FOR COMMENTED SECTION
    //real_x = ac
    // real_x = _mm256_mul_pd(real_x,real_y);
    // //imag_x = bc
    // imag_x = _mm256_mul_pd(imag_x,real_y);
    // //real_x = ac - bd => real_x - real_temp
    // real_x = _mm256_sub_pd(real_x,real_temp);
    // //imag_x = ad + bc => imag_temp + imag_x
    // imag_x = _mm256_add_pd(imag_x,imag_temp);
    //THESE ARE NOT WORKING 
    real_x = _mm256_fmsub_pd(real_x,real_y,real_temp);
    imag_x = _mm256_fmadd_pd(imag_x,real_y,imag_temp);

    real_y = _mm256_set1_pd(CPLXDIM);
    real_x = _mm256_div_pd(real_x,real_y);
    imag_x = _mm256_div_pd(imag_x,real_y);

    _mm256_store_pd(vec_res.real+i,real_x);
    _mm256_store_pd(vec_res.imag+i,imag_x);

  }
  fft_vector_nonrec_backward(&vec_res,r);
}