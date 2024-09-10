 __m64 interpolvline128_3(__m128i* temp){



	__m128i xmm6;

	__m64 ret;

	__m128i xmm7 = _mm_setzero_si128();

	__m128i xmm0 = _mm_load_si128(temp++);
	__m128i xmm1 = _mm_load_si128(temp++);
	__m128i xmm2 = _mm_load_si128(temp++);
	__m128i xmm3 = _mm_load_si128(temp++);
	__m128i xmm4 = _mm_load_si128(temp++);
	__m128i xmm5 = _mm_load_si128(temp);

	xmm1 = _mm_add_epi16(xmm1,xmm4);
	xmm0 = _mm_add_epi16(xmm0,xmm5);

	xmm6 = _mm_set_epi32(0xFFFBFFFB,0xFFFBFFFB,0xFFFBFFFB,0xFFFBFFFB);

	xmm4 = _mm_mullo_epi16(xmm1, xmm6);
	xmm5 = _mm_mulhi_epi16(xmm1, xmm6);

	xmm1 = _mm_unpacklo_epi16(xmm4, xmm5);
	xmm6 = _mm_unpackhi_epi16(xmm4, xmm5);

	xmm7 = _mm_set_epi32(0x00140014,0x00140014,0x00140014,0x00140014);
	xmm5 = _mm_add_epi16(xmm2,xmm3);

	xmm4 = _mm_mullo_epi16(xmm5, xmm7);
	xmm5 = _mm_mulhi_epi16(xmm5, xmm7);

	xmm7 = _mm_unpacklo_epi16(xmm4, xmm5);
	xmm4 = _mm_unpackhi_epi16(xmm4, xmm5);

	xmm7 = _mm_add_epi32(xmm7,xmm1);
	xmm4 = _mm_add_epi32(xmm4,xmm6); 

	xmm6 = _mm_set_epi32(0x00010001,0x00010001,0x00010001,0x00010001);
	xmm6 = _mm_mulhi_epi16(xmm0, xmm6);

	xmm1 = _mm_unpacklo_epi16(xmm0, xmm6);
	xmm6 = _mm_unpackhi_epi16(xmm0, xmm6);

	xmm7 = _mm_add_epi32(xmm7,xmm1);
	xmm4 = _mm_add_epi32(xmm4,xmm6); 
	
	xmm1 = _mm_set_epi32(0x00000200,0x00000200,0x00000200,0x00000200);
	
	xmm7 = _mm_add_epi32(xmm7,xmm1);
	xmm4 = _mm_add_epi32(xmm4,xmm1);
	
	xmm5 = _mm_setzero_si128();

	xmm7 = _mm_srli_epi32(xmm7, 10);
	xmm7 = _mm_max_epi16(xmm7, xmm5); // preventing negative values
	xmm7 = _mm_slli_epi32(xmm7,16);
	xmm7 = _mm_srli_epi32(xmm7,16);

	xmm4 = _mm_srli_epi32(xmm4, 10);

	xmm4 = _mm_max_epi16(xmm4, xmm5); // preventing negative values
	xmm4 = _mm_slli_epi32(xmm4,16);
	xmm4 = _mm_srli_epi32(xmm4,16);

	xmm6 = _mm_packs_epi32(xmm7, xmm4);
	
	xmm1 = _mm_set_epi32(0x00100010,0x00100010,0x00100010,0x00100010);
	xmm2 = _mm_add_epi16(xmm2,xmm1);
	xmm2 = _mm_max_epi16(xmm2, xmm5); // preventing negative values
	xmm2 = _mm_srli_epi16(xmm2,5);

	
	xmm3 = _mm_add_epi16(xmm3,xmm1);
	xmm3 = _mm_max_epi16(xmm3, xmm5); // preventing negative values
	xmm3 = _mm_srli_epi16(xmm3,5);

	xmm2 = _mm_packus_epi16(xmm2,xmm5);
	xmm3 = _mm_packus_epi16(xmm3,xmm5);
	xmm6 = _mm_packus_epi16(xmm6,xmm5);

	xmm7 = _mm_unpacklo_epi8(xmm2,xmm6);
	xmm4 = _mm_unpacklo_epi8(xmm6,xmm3);
	xmm6 = _mm_avg_epu8(xmm4,xmm7);

	xmm6 = _mm_srli_epi16(xmm6,8);
	xmm6 = _mm_packus_epi16(xmm6,xmm5);
	ret = _mm_movepi64_pi64(xmm6);

	_mm_empty(); 

	return(ret);
}