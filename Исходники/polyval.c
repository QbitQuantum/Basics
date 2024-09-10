void Polyval_Horner(unsigned char* TAG,
					unsigned char* pH,
					unsigned char* inp,
					int length)
{
	__m128i TMP0, TMP1, TMP2, TMP3, TMP4, T, POLY, H;
	int i=0;
	if (length==0)
		return;
	int has_semi = length%16;
	uint8_t B[16]={0};
	length /=16;
	
	H = _mm_loadu_si128(((__m128i*)pH));
	T = _mm_loadu_si128(((__m128i*)TAG));
	POLY = _mm_setr_epi32(0x1,0,0,0xc2000000);
	for (i=0; i< length; i++)
	{
		T = _mm_xor_si128(T, _mm_loadu_si128(&((__m128i*)inp)[i]));
		TMP1 = _mm_clmulepi64_si128(T, H, 0x00);
		TMP4 = _mm_clmulepi64_si128(T, H, 0x11);
		TMP2 = _mm_clmulepi64_si128(T, H, 0x10);
		TMP3 = _mm_clmulepi64_si128(T, H, 0x01);
		TMP2 = _mm_xor_si128(TMP2, TMP3);
		TMP3 = _mm_slli_si128(TMP2, 8);
		TMP2 = _mm_srli_si128(TMP2, 8);
		TMP1 = _mm_xor_si128(TMP3, TMP1);
		TMP4 = _mm_xor_si128(TMP4, TMP2);
		TMP2 = _mm_clmulepi64_si128(TMP1, POLY, 0x10);
		TMP3 = _mm_shuffle_epi32(TMP1, 78);
		TMP1 = _mm_xor_si128(TMP3, TMP2);
		TMP2 = _mm_clmulepi64_si128(TMP1, POLY, 0x10);
		TMP3 = _mm_shuffle_epi32(TMP1, 78);
		TMP1 = _mm_xor_si128(TMP3, TMP2);
		T = _mm_xor_si128(TMP4, TMP1);
	}
	if (has_semi!=0)
	{
		memcpy(B, inp+length*16, has_semi);
		T = _mm_xor_si128(T, _mm_loadu_si128((__m128i*)B));
		TMP1 = _mm_clmulepi64_si128(T, H, 0x00);
		TMP4 = _mm_clmulepi64_si128(T, H, 0x11);
		TMP2 = _mm_clmulepi64_si128(T, H, 0x10);
		TMP3 = _mm_clmulepi64_si128(T, H, 0x01);
		TMP2 = _mm_xor_si128(TMP2, TMP3);
		TMP3 = _mm_slli_si128(TMP2, 8);
		TMP2 = _mm_srli_si128(TMP2, 8);
		TMP1 = _mm_xor_si128(TMP3, TMP1);
		TMP4 = _mm_xor_si128(TMP4, TMP2);
		TMP2 = _mm_clmulepi64_si128(TMP1, POLY, 0x10);
		TMP3 = _mm_shuffle_epi32(TMP1, 78);
		TMP1 = _mm_xor_si128(TMP3, TMP2);
		TMP2 = _mm_clmulepi64_si128(TMP1, POLY, 0x10);
		TMP3 = _mm_shuffle_epi32(TMP1, 78);
		TMP1 = _mm_xor_si128(TMP3, TMP2);
		T = _mm_xor_si128(TMP4, TMP1);
	}
	_mm_storeu_si128(((__m128i*)TAG), T);
}