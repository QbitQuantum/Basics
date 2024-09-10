void read_luma_inter_pred_avg_8x16_intrinsic( BYTE *address1, BYTE *address2, INT stride_src, BYTE *dst, INT stride_dst )
{
	int i;
	int src_stride = stride_src;
	int dst_stride = stride_dst;
	const unsigned char* src1 = address1;
	const unsigned char* src2 = address2;

	for( i = 0; i < 16; i+=8)
	{
		__declspec(align(16)) __m128i r0, r1, r2, r3, r4, r5, r6, r7,
			r0_x, r1_x, r2_x, r3_x, r4_x, r5_x, r6_x, r7_x;
		int stride2 = (src_stride<<1);
		int stride4 = (src_stride<<2);
		int dst_stride2 = (dst_stride<<1);
		int dst_stride4 = (dst_stride<<2);
		r0 = _mm_loadl_epi64((__m128i*)(src1));
		r1 = _mm_loadl_epi64((__m128i*)(src1+src_stride));
		r2 = _mm_loadl_epi64((__m128i*)(src1+stride2));
		r3 = _mm_loadl_epi64((__m128i*)(src1+stride2+src_stride));
		r4 = _mm_loadl_epi64((__m128i*)(src1+stride4));
		r5 = _mm_loadl_epi64((__m128i*)(src1+stride4+src_stride));
		r6 = _mm_loadl_epi64((__m128i*)(src1+stride4+stride2));
		r7 = _mm_loadl_epi64((__m128i*)(src1+stride4+stride2+src_stride));
		r0_x = _mm_loadl_epi64((__m128i*)(src2));
		r1_x = _mm_loadl_epi64((__m128i*)(src2+src_stride));
		r2_x = _mm_loadl_epi64((__m128i*)(src2+stride2));
		r3_x = _mm_loadl_epi64((__m128i*)(src2+stride2+src_stride));
		r4_x = _mm_loadl_epi64((__m128i*)(src2+stride4));
		r5_x = _mm_loadl_epi64((__m128i*)(src2+stride4+src_stride));
		r6_x = _mm_loadl_epi64((__m128i*)(src2+stride4+stride2));
		r7_x = _mm_loadl_epi64((__m128i*)(src2+stride4+stride2+src_stride));
		r0 = _mm_avg_epu8(r0, r0_x);
		r1 = _mm_avg_epu8(r1, r1_x);
		r2 = _mm_avg_epu8(r2, r2_x);
		r3 = _mm_avg_epu8(r3, r3_x);
		r4 = _mm_avg_epu8(r4, r4_x);
		r5 = _mm_avg_epu8(r5, r5_x);
		r6 = _mm_avg_epu8(r6, r6_x);
		r7 = _mm_avg_epu8(r7, r7_x);
		_mm_storel_epi64((__m128i*)(dst), r0);
		_mm_storel_epi64((__m128i*)(dst+dst_stride), r1);
		_mm_storel_epi64((__m128i*)(dst+dst_stride2), r2);
		_mm_storel_epi64((__m128i*)(dst+dst_stride2+dst_stride), r3);
		_mm_storel_epi64((__m128i*)(dst+dst_stride4), r4);
		_mm_storel_epi64((__m128i*)(dst+dst_stride4+dst_stride), r5);
		_mm_storel_epi64((__m128i*)(dst+dst_stride4+dst_stride2), r6);
		_mm_storel_epi64((__m128i*)(dst+dst_stride4+dst_stride2+dst_stride), r7);
		src1 += (stride4<<1);
		src2 += (stride4<<1);
		dst += (dst_stride4<<1);
	}
}