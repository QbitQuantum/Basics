/// CURRENTLY SAME CODE AS SCALAR !!
/// REPLACE HERE WITH SSE intrinsics
static void partialButterflyInverse16_simd(short *src, short *dst, int shift)
{

  int add = 1<<(shift-1);

//we cast the original 16X16 matrix to an SIMD vector type
    __m128i *g_aiT16_vec  = (__m128i *)g_aiT16; 


//We cast the input source (which is basically random numbers(see the main function for details)) to an SIMD vector type
//We also cast the output to an SIMD vector type
  __m128i *in_vec = (__m128i *) src;   
  __m128i *out_vec = (__m128i *) dst;

//we declare an 8X8 array and cast it to an SIMD vector type
  short gt[8][8] __attribute__ ((aligned (16)));
  __m128i *gt_vec = (__m128i *)gt;

//we declare an 16X16 array and cast it to an SIMD vector type
  short random[16][16] __attribute__ ((aligned (16)));
  __m128i *random_vec = (__m128i *)random;  
  

trans_g_aiT16(g_aiT16_vec,gt_vec);

tranpose8x8(in_vec,2, random_vec,0);
tranpose8x8(in_vec,3, random_vec,8);
tranpose8x8(in_vec,0, random_vec,16);
tranpose8x8(in_vec,1, random_vec,24);

  for (int j=0; j<16; j++)
  {
    /* Utilizing symmetry properties to the maximum to minimize the number of multiplications */
      
    __m128i I0 = _mm_load_si128 (&random_vec[j]); 
    __m128i II0 = _mm_load_si128 (&random_vec[j+16]); 

  // for (int k=0; k<8; k++)
          //here we are loading up the transposed values in the initial matrix
          //multiplying it with the input numbers to produce intermediate 32-bit integers
          // we then sum up adjacent pairs of 32-bit integers and store them in the destination register
        __m128i I1 = _mm_load_si128 (&gt_vec[0]);   
        __m128i I2 = _mm_madd_epi16 (I1, I0);
         
        __m128i I3 = _mm_load_si128 (&gt_vec[1]);   
        __m128i I4 = _mm_madd_epi16 (I3, I0);
   
        __m128i I5 = _mm_load_si128 (&gt_vec[2]);   
        __m128i I6 = _mm_madd_epi16 (I5, I0);

        __m128i I7 = _mm_load_si128 (&gt_vec[3]);   
        __m128i I8 = _mm_madd_epi16 (I7, I0);

        __m128i I9 = _mm_load_si128 (&gt_vec[4]);   
        __m128i I10 = _mm_madd_epi16 (I9, I0);

        __m128i I11 = _mm_load_si128 (&gt_vec[5]);   
        __m128i I12 = _mm_madd_epi16 (I11, I0);

        __m128i I13 = _mm_load_si128 (&gt_vec[6]);   
        __m128i I14 = _mm_madd_epi16 (I13, I0);

        __m128i I15 = _mm_load_si128 (&gt_vec[7]);   
        __m128i I16 = _mm_madd_epi16 (I15, I0);

        //horizontally add the partial results obtained from thee previous step
       __m128i A1 =_mm_hadd_epi32 (I2, I4);
       __m128i A2 =_mm_hadd_epi32 (I6, I8);
       __m128i R1 =_mm_hadd_epi32 (A1, A2);

       __m128i A3 =_mm_hadd_epi32 (I10, I12);
       __m128i A4 =_mm_hadd_epi32 (I14, I16);
       __m128i R2 =_mm_hadd_epi32 (A3, A4);
 
   
      //  O[k] = T[0]+T[1]+T[2]+T[3];    
            
  //  for (int k=0; k<4; k++)
 //   {
       //load the original matrix values, multiply it with the random values
       //store the low bits to I2 and the hi bits to I3
       I1 = _mm_load_si128 (&gt_vec[8]);       
       I2 = _mm_mullo_epi16 (I1, II0);
       I3 = _mm_mulhi_epi16 (I1, II0);

      __m128i lowI23 = _mm_unpacklo_epi16(I2,I3);
      __m128i hiI23 = _mm_unpackhi_epi16(I2,I3);    
      __m128i temp1 = _mm_add_epi32(lowI23,hiI23);
      __m128i temp5 = _mm_hsub_epi32 (lowI23, hiI23);

       I4 = _mm_load_si128 (&gt_vec[9]);       
       I5 = _mm_mullo_epi16 (I4, II0);
       I6 = _mm_mulhi_epi16 (I4, II0);
      __m128i lowI56 = _mm_unpacklo_epi16(I5,I6);
      __m128i hiI56 = _mm_unpackhi_epi16(I5,I6);    
      __m128i temp2 = _mm_add_epi32(lowI56,hiI56);  
      __m128i temp6 = _mm_hsub_epi32 (lowI56, hiI56);   
             
       I7 = _mm_load_si128 (&gt_vec[10]);      
       I8 = _mm_mullo_epi16 (I7, II0);
       I9 = _mm_mulhi_epi16 (I7, II0);
      __m128i lowI89 = _mm_unpacklo_epi16(I8,I9);
      __m128i hiI89 = _mm_unpackhi_epi16(I8,I9);    
      __m128i temp3 = _mm_add_epi32(lowI89,hiI89);  
      __m128i temp7 = _mm_hsub_epi32 (lowI89, hiI89);    

       I10 = _mm_load_si128 (&gt_vec[11]);       
       I11 = _mm_mullo_epi16 (I10, II0);
       I12 = _mm_mulhi_epi16 (I10, II0);
      __m128i lowI1112 = _mm_unpacklo_epi16(I11,I12);
      __m128i hiI1112 = _mm_unpackhi_epi16(I11,I12);    
      __m128i temp4 = _mm_add_epi32(lowI1112,hiI1112);  
      __m128i temp8 = _mm_hsub_epi32 (lowI1112, hiI1112);   
 
       __m128i A5 =_mm_hadd_epi32 (temp1, temp2);
       __m128i A6 =_mm_hadd_epi32 (temp3, temp4);
       __m128i R3 =_mm_hadd_epi32 (A5, A6);

       __m128i A7 =_mm_hadd_epi32 (temp8, temp7);
       __m128i A8 =_mm_hadd_epi32 (temp6, temp5);
       __m128i R4 =_mm_hadd_epi32 (A7, A8);

///////////////////////////
         __m128i add_reg = _mm_set1_epi32(add);

         __m128i sum_vec0 = _mm_add_epi32(R3,R1);        
         sum_vec0 = _mm_add_epi32(sum_vec0,add_reg);
         sum_vec0 = _mm_srai_epi32(sum_vec0, shift); // shift right
	 
         
         __m128i sum_vec1 = _mm_add_epi32(R4,R2);
         sum_vec1 = _mm_add_epi32(sum_vec1,add_reg);
         sum_vec1 = _mm_srai_epi32(sum_vec1, shift); // shift right

	 __m128i finalres0 = _mm_packs_epi32(sum_vec0, sum_vec1); // shrink packed 32bit to packed 16 bit and saturate
         _mm_store_si128 (&out_vec[2*j], finalres0);
         
        __m128i  sum_vec2 = _mm_sub_epi32(R4, R2);
         sum_vec2 = _mm_add_epi32(sum_vec2,add_reg);
         sum_vec2 = _mm_srai_epi32(sum_vec2, shift); // shift right  	 

         __m128i sum_vec3 = _mm_sub_epi32(R3, R1);
         sum_vec3 = _mm_add_epi32(sum_vec3,add_reg);
         sum_vec3 = _mm_srai_epi32(sum_vec3, shift); // shift right

         I5 = _mm_unpackhi_epi32(sum_vec2, sum_vec3);
         I6 = _mm_unpacklo_epi32(sum_vec2, sum_vec3);
         I7 = _mm_unpackhi_epi32(I5, I6);
         I8 = _mm_unpacklo_epi32(I5, I6);
         I9 = _mm_unpacklo_epi32(I7, I8);
         I10 = _mm_unpackhi_epi32(I7, I8);
         
	 sum_vec3 = _mm_packs_epi32(I9, I10); // shrink packed 32bit to packed 16 bit and saturate
         _mm_store_si128 (&out_vec[2*j+1], sum_vec3);
  }
}