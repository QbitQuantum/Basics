void gblas_quantizer::quantization(const double* input, double* output, int rows, int cols)
{
  std::cerr << "Deprecated method: gblas_quantizer::quantization()" << std::endl;
  exit(0);
  
  //  for (int i=0; i < rows; i++)
  //  {
  //    for (int j=0; j < cols; j++)
  //    {
  //      output[i*cols + j] = quantize_sample(&input[i*cols + j]);
  //    }
  //  }
  
  //  for (int i=0; i < rows*cols; i++)
  //  {
  //    output[i] = (int)(input[i]/gblas_status.q_step + ZERO_DOT_FIVE); //quantize_sample(&input[i]);
  //  }
  __m128d curr;
  __m128d inv_q_step  = _mm_div_pd(_mm_set1_pd(1.0), _mm_set1_pd(q_step));
  const double* in_p  = input;
  double* out_p = output;
  
  for (int i=((rows*cols) >> 1); i > 0; i--)
  {
    curr = _mm_load_pd(in_p); in_p += 2;
    curr = _mm_mul_pd(curr, inv_q_step);    
    curr = _mm_add_pd(curr, _MM_ZERO_DOT_FIVE_D);
    curr = _mm_cvtepi32_pd(_mm_cvttpd_epi32(curr));
    _mm_store_pd(out_p, curr);  out_p += 2;
  }
}