int mult_cpx_vector_h(short *x1, 
		      short *x2, 
		      short *y, 
		      unsigned int N, 
		      unsigned short output_shift,
		      short sign)
{
  // Multiply elementwise the complex vector x1 with the complex conjugate of the complex vecotr x2 of N elements and adds it to the vector y.
  // x1       - input 1    in the format  |Re0  Im0 Re0 Im0|,......,|Re(N-1)  Im(N-1) Re(N-1) Im(N-1)|
  //            We assume x1 with a dinamic of 15 bit maximum
  //
  // x2       - input 2    in the format  |Re0 Im0 Re0 Im0|,......,|Re(N-1) Im(N-1) Re(N-1) Im(N-1)|
  //            We assume x2 with a dinamic of 14 bit maximum
  //
  // y        - output     in the format  |Re0  Im0 Re0 Im0|,......,|Re(N-1)  Im(N-1) Re(N-1) Im(N-1)|
  //
  // N        - the size f the vectors (this function does N cpx mpy. WARNING: N>=4;
  //
  // log2_amp - increase the output amplitude by a factor 2^log2_amp (default is 0)
  //            WARNING: log2_amp>0 can cause overflow!!
  // sign     - +1..add, -1..substract

  unsigned int i;                 // loop counter

  register __m128i m0,m1,m2;

  short *temps;
  int *tempd;

  __m128i *x1_128; 
  __m128i *x2_128; 
  __m128i *y_128; 
  __m128i mask;

  __m128i temp;

  shift = _mm_cvtsi32_si128(output_shift);
  x1_128 = (__m128i *)&x1[0];
  x2_128 = (__m128i *)&x2[0];
  y_128 = (__m128i *)&y[0];

  if (sign == -1)
    mask = (__m128i) _mm_set_epi16 (-1,1,-1,-1,-1,1,-1,-1);
  else
    mask = (__m128i) _mm_set_epi16 (1,-1,1,1,1,-1,1,1);

  // we compute 2*4 cpx multiply for each loop
  for(i=0;i<(N>>3);i++)
  {
    
    //    printf("i=%d\n",i);

    // unroll 1
    //    temps = (short *)x1_128;
    //    printf("x1 : %d,%d,%d,%d,%d,%d,%d,%d\n",temps[0],temps[1],temps[2],temps[3],temps[4],temps[5],temps[6],temps[7]);
    m1 = x1_128[0];
    m2 = x2_128[0];

    //    temps = (short *)&x2_128[0];
    //    printf("x2 : %x,%x,%x,%x,%x,%x,%x,%x\n",temps[0],temps[1],temps[2],temps[3],temps[4],temps[5],temps[6],temps[7]);

    // bring x2 in conjugate form
    // the first two instructions might be replaced with a single one in SSE3
    m2 = _mm_shufflelo_epi16(m2,_MM_SHUFFLE(0,1,3,2));
    m2 = _mm_shufflehi_epi16(m2,_MM_SHUFFLE(0,1,3,2));
    m2 = _mm_mullo_epi16(m2, mask);

    //    temp = m2;
    //    temps = (short *)&temp;
    //    printf("x2 conj : %x,%x,%x,%x,%x,%x,%x,%x\n",temps[0],temps[1],temps[2],temps[3],temps[4],temps[5],temps[6],temps[7]);

    m0 = _mm_madd_epi16(m1,m2); //pmaddwd_r2r(mm1,mm0);         // 1- compute x1[0]*x2[0]

    //    temp = m0;

    //    tempd = &temp;
    //    printf("m0 : %d,%d,%d,%d\n",tempd[0],tempd[1],tempd[2],tempd[3]);

    m0 = _mm_sra_epi32(m0,shift);        // 1- shift right by shift in order to  compensate for the input amplitude

    //    temp = m0;

    //    tempd = (int *)&temp;
    //  printf("m0 : %d,%d,%d,%d\n",tempd[0],tempd[1],tempd[2],tempd[3]);

    m0 = _mm_packs_epi32(m0,m0);        // 1- pack in a 128 bit register [re im re im]
    m0 = _mm_unpacklo_epi32(m0,m0);        // 1- pack in a 128 bit register [re im re im]

    y_128[0] = _mm_add_epi16(m0,y_128[0]);

    //    temps = (short *)&y_128[0];
    //    printf("y0 : %d,%d,%d,%d,%d,%d,%d,%d\n",temps[0],temps[1],temps[2],temps[3],temps[4],temps[5],temps[6],temps[7]);

    // unroll 2
    m1 = x1_128[1];
    m2 = x2_128[1];

    m2 = _mm_shufflelo_epi16(m2,_MM_SHUFFLE(0,1,3,2));
    m2 = _mm_shufflehi_epi16(m2,_MM_SHUFFLE(0,1,3,2));
    m2 = _mm_mullo_epi16(m2, mask);

    m0 = _mm_madd_epi16(m1,m2); //pmaddwd_r2r(mm1,mm0);         // 1- compute x1[0]*x2[0]

    m0 = _mm_sra_epi32(m0,shift);        // 1- shift right by shift in order to  compensate for the input amplitude

    m0 = _mm_packs_epi32(m0,m0);        // 1- pack in a 128 bit register [re im re im]
    m0 = _mm_unpacklo_epi32(m0,m0);        // 1- pack in a 128 bit register [re im re im]

    y_128[1] = _mm_add_epi16(m0,y_128[1]);

    // unroll 3
    m1 = x1_128[2];
    m2 = x2_128[2];

    m2 = _mm_shufflelo_epi16(m2,_MM_SHUFFLE(0,1,3,2));
    m2 = _mm_shufflehi_epi16(m2,_MM_SHUFFLE(0,1,3,2));
    m2 = _mm_mullo_epi16(m2, mask);

    m0 = _mm_madd_epi16(m1,m2); //pmaddwd_r2r(mm1,mm0);         // 1- compute x1[0]*x2[0]

    m0 = _mm_sra_epi32(m0,shift);        // 1- shift right by shift in order to  compensate for the input amplitude

    m0 = _mm_packs_epi32(m0,m0);        // 1- pack in a 128 bit register [re im re im]
    m0 = _mm_unpacklo_epi32(m0,m0);        // 1- pack in a 128 bit register [re im re im]

    y_128[2] = _mm_add_epi16(m0,y_128[2]);


    // unroll 4
    m1 = x1_128[3];
    m2 = x2_128[3];

    m2 = _mm_shufflelo_epi16(m2,_MM_SHUFFLE(0,1,3,2));
    m2 = _mm_shufflehi_epi16(m2,_MM_SHUFFLE(0,1,3,2));
    m2 = _mm_mullo_epi16(m2, mask);

    m0 = _mm_madd_epi16(m1,m2); //pmaddwd_r2r(mm1,mm0);         // 1- compute x1[0]*x2[0]

    m0 = _mm_sra_epi32(m0,shift);        // 1- shift right by shift in order to  compensate for the input amplitude

    m0 = _mm_packs_epi32(m0,m0);        // 1- pack in a 128 bit register [re im re im]
    m0 = _mm_unpacklo_epi32(m0,m0);        // 1- pack in a 128 bit register [re im re im]

    y_128[3] = _mm_add_epi16(m0,y_128[3]);

    x1_128+=4;
    x2_128+=4;
    y_128 +=4;
    //    printf("x1_128 = %p, x2_128 =%p,  y_128=%p\n",x1_128,x2_128,y_128);

  }


  _mm_empty();
  _m_empty();

  return(0);
}