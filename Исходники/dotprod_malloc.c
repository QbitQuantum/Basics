int oneThread(int threadId)
{
	int *aa;
	int *bb;
	int k;
	int itr;

	aa = (int *)_mm_malloc(sizeof(int)*ARRAY_SIZE, 16);
	bb = (int *)_mm_malloc(sizeof(int)*ARRAY_SIZE, 16);

	memset(&aa[0], 1, ARRAY_SIZE*4);
	memset(&bb[0], 2, ARRAY_SIZE*4);

  __m128i a0,a1,a2,a3,b0,b1,b2,b3;
  __m128i a4,a5,a6,a7,b4,b5,b6,b7;
	__m128i c0,c1,c2,c3;
	__m128i c4,c5,c6,c7;
	__m128i cc;
	cc = _mm_set_epi32 (0, 0, 0, 0);

	for (k = 0; k < REPS; k++) 
	{
		for (itr = 0; itr<ARRAY_SIZE; itr+=32)
		{
			a0 = _mm_load_si128((__m128i*)&aa[itr]);
			a1 = _mm_load_si128((__m128i*)&aa[itr+4]);	
			a2 = _mm_load_si128((__m128i*)&aa[itr+8]);	
			a3 = _mm_load_si128((__m128i*)&aa[itr+12]);	
			a4 = _mm_load_si128((__m128i*)&aa[itr+16]);
			a5 = _mm_load_si128((__m128i*)&aa[itr+20]);	
			a6 = _mm_load_si128((__m128i*)&aa[itr+24]);	
			a7 = _mm_load_si128((__m128i*)&aa[itr+28]);	
			b0 = _mm_load_si128((__m128i*)&bb[itr]);
			b1 = _mm_load_si128((__m128i*)&bb[itr+4]);	
			b2 = _mm_load_si128((__m128i*)&bb[itr+8]);	
			b3 = _mm_load_si128((__m128i*)&bb[itr+12]);	
			b4 = _mm_load_si128((__m128i*)&bb[itr+16]);
			b5 = _mm_load_si128((__m128i*)&bb[itr+20]);	
			b6 = _mm_load_si128((__m128i*)&bb[itr+24]);	
			b7 = _mm_load_si128((__m128i*)&bb[itr+28]);	

			c0 = _mm_mul_epi32(a0, b0);
			c1 = _mm_mul_epi32(a1, b1);
			c2 = _mm_mul_epi32(a2, b2);
			c3 = _mm_mul_epi32(a3, b3);
			c4 = _mm_mul_epi32(a4, b4);
			c5 = _mm_mul_epi32(a5, b5);
			c6 = _mm_mul_epi32(a6, b6);
			c7 = _mm_mul_epi32(a7, b7);

			c0 = _mm_add_epi32(c0,c1);
			c1 = _mm_add_epi32(c2,c3);
			c2 = _mm_add_epi32(c4,c5);
			c3 = _mm_add_epi32(c6,c7);
			c0 = _mm_add_epi32(c0,c1);
			c1 = _mm_add_epi32(c2,c3);
			c0 = _mm_add_epi32(c0,c1);
			cc = _mm_add_epi32(cc,c0);

		}	
	}
	cc = _mm_hadd_epi32(cc,cc);
	cc = _mm_hadd_epi32(cc,cc);

	int count =0;
	count = _mm_cvtsi128_si32(cc) ;	

	free(aa);
	free(bb);

	return count;
}