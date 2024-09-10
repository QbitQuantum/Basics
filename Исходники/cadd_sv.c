int add_vector32_scalar(short *x, 
			int alpha, 
			short *y, 
			unsigned int N)
{
  unsigned int i;                 // loop counter

  __m128i *x_128; 
  __m128i *y_128; 

  x_128 = (__m128i *)&x[0];
  y_128 = (__m128i *)&y[0];

  alpha_128 = _mm_setr_epi32(alpha,0,alpha,0);

  // we compute 4 cpx multiply for each loop
  for(i=0;i<(N>>3);i++)
  {
    y_128[0] = _mm_add_epi32(alpha_128, x_128[0]);
    y_128[1] = _mm_add_epi32(alpha_128, x_128[1]);
    y_128[2] = _mm_add_epi32(alpha_128, x_128[2]);
    y_128[3] = _mm_add_epi32(alpha_128, x_128[3]);


    x_128+=4;
    y_128 +=4;

  }
  return (0);
}