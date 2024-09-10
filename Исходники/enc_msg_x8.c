void ENC_MSG_x8(const unsigned char *PT,
                      unsigned char *CT,
                      const unsigned char *TAG,
                      const unsigned char *KS,
                      int length)
{
    __m128i or_mask, TWO,ctr_block, tmp, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7, ONE;
    int i,j,remainder_loc;
    if (length%16)
        length = length/16 + 1;
    else length/=16;
    ONE = _mm_setr_epi32(1,0,0,0);
	TWO = _mm_setr_epi32(2,0,0,0);
	ctr_block = _mm_setzero_si128();
	ctr_block = _mm_loadu_si128(((__m128i*)TAG));
	or_mask = _mm_setr_epi32(0,0,0,0x80000000);
	ctr_block = _mm_or_si128(ctr_block, or_mask);
	for (i=0; i< (length-length%8); i=i+8)
	{
		tmp = ctr_block;
		tmp1 = _mm_add_epi32(ctr_block, ONE);
		tmp2 = _mm_add_epi32(ctr_block, TWO);
		tmp3 = _mm_add_epi32(tmp2, ONE);
		tmp4 = _mm_add_epi32(tmp2, TWO);
		tmp5 = _mm_add_epi32(tmp4, ONE);
		tmp6 = _mm_add_epi32(tmp4, TWO);
		tmp7 = _mm_add_epi32(tmp6, ONE);
		ctr_block = _mm_add_epi32(tmp6, TWO);
		tmp = _mm_xor_si128(tmp, ((__m128i*)KS)[0]);
		tmp1 = _mm_xor_si128(tmp1, ((__m128i*)KS)[0]);
		tmp2 = _mm_xor_si128(tmp2, ((__m128i*)KS)[0]);
		tmp3 = _mm_xor_si128(tmp3, ((__m128i*)KS)[0]);
		tmp4 = _mm_xor_si128(tmp4, ((__m128i*)KS)[0]);
		tmp5 = _mm_xor_si128(tmp5, ((__m128i*)KS)[0]);
		tmp6 = _mm_xor_si128(tmp6, ((__m128i*)KS)[0]);
		tmp7 = _mm_xor_si128(tmp7, ((__m128i*)KS)[0]);
			for(j=1; j <10; j++) {
				tmp = _mm_aesenc_si128 (tmp, ((__m128i*)KS)[j]);
				tmp1 = _mm_aesenc_si128 (tmp1, ((__m128i*)KS)[j]);
				tmp2 = _mm_aesenc_si128 (tmp2, ((__m128i*)KS)[j]);
				tmp3 = _mm_aesenc_si128 (tmp3, ((__m128i*)KS)[j]);
				tmp4 = _mm_aesenc_si128 (tmp4, ((__m128i*)KS)[j]);
				tmp5 = _mm_aesenc_si128 (tmp5, ((__m128i*)KS)[j]);
				tmp6 = _mm_aesenc_si128 (tmp6, ((__m128i*)KS)[j]);
				tmp7 = _mm_aesenc_si128 (tmp7, ((__m128i*)KS)[j]);
				};
			tmp = _mm_aesenclast_si128 (tmp, ((__m128i*)KS)[j]);
			tmp1 = _mm_aesenclast_si128 (tmp1, ((__m128i*)KS)[j]);
			tmp2 = _mm_aesenclast_si128 (tmp2, ((__m128i*)KS)[j]);
			tmp3 = _mm_aesenclast_si128 (tmp3, ((__m128i*)KS)[j]);
			tmp4 = _mm_aesenclast_si128 (tmp4, ((__m128i*)KS)[j]);
			tmp5 = _mm_aesenclast_si128 (tmp5, ((__m128i*)KS)[j]);
			tmp6 = _mm_aesenclast_si128 (tmp6, ((__m128i*)KS)[j]);
			tmp7 = _mm_aesenclast_si128 (tmp7, ((__m128i*)KS)[j]);
			tmp = _mm_xor_si128(tmp,_mm_loadu_si128(&((__m128i*)PT)[i]));
			tmp1 = _mm_xor_si128(tmp1,_mm_loadu_si128(&((__m128i*)PT)[i+1]));
			tmp2 = _mm_xor_si128(tmp2,_mm_loadu_si128(&((__m128i*)PT)[i+2]));
			tmp3 = _mm_xor_si128(tmp3,_mm_loadu_si128(&((__m128i*)PT)[i+3]));
			tmp4 = _mm_xor_si128(tmp4,_mm_loadu_si128(&((__m128i*)PT)[i+4]));
			tmp5 = _mm_xor_si128(tmp5,_mm_loadu_si128(&((__m128i*)PT)[i+5]));
			tmp6 = _mm_xor_si128(tmp6,_mm_loadu_si128(&((__m128i*)PT)[i+6]));
			tmp7 = _mm_xor_si128(tmp7,_mm_loadu_si128(&((__m128i*)PT)[i+7]));
			_mm_storeu_si128(&((__m128i*)CT)[i],tmp);
			_mm_storeu_si128(&((__m128i*)CT)[i+1],tmp1);
			_mm_storeu_si128(&((__m128i*)CT)[i+2],tmp2);
			_mm_storeu_si128(&((__m128i*)CT)[i+3],tmp3);
			_mm_storeu_si128(&((__m128i*)CT)[i+4],tmp4);
			_mm_storeu_si128(&((__m128i*)CT)[i+5],tmp5);
			_mm_storeu_si128(&((__m128i*)CT)[i+6],tmp6);
			_mm_storeu_si128(&((__m128i*)CT)[i+7],tmp7);
		}
	// handling remainder and less than 8 blocks
	if (length%8==0)
		return;
	// The remainder_loc is used to remember the location of our block handled 
	remainder_loc = length-length%8;
    for(i=0; i < (length%8); i++)
	{
		tmp = ctr_block;
        ctr_block = _mm_add_epi32(ctr_block, ONE);
        tmp = _mm_xor_si128(tmp, ((__m128i*)KS)[0]);

            for(j=1; j <10; j++) {
                tmp = _mm_aesenc_si128 (tmp, ((__m128i*)KS)[j]);
                };
            tmp = _mm_aesenclast_si128 (tmp, ((__m128i*)KS)[j]);
            tmp = _mm_xor_si128(tmp,_mm_loadu_si128(&((__m128i*)PT)[remainder_loc+i]));
            _mm_storeu_si128 (&((__m128i*)CT)[remainder_loc+i],tmp);
    }
}