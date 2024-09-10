mlib_status
__mlib_VideoP64Decimate_U8_U8(
	mlib_u8 *dst,
	const mlib_u8 *src,
	mlib_s32 width,
	mlib_s32 height,
	mlib_s32 dst_stride,
	mlib_s32 src_stride)
{
	mlib_s32 x, y;
	const mlib_u8 *sd1, *sd2;
	mlib_u8 *dd;
	mlib_u32 src_stride2;

	sd1 = src;
	sd2 = src + src_stride;
	src_stride2 = 2 * src_stride;
	dd = dst;

	mlib_s32 dw = width & 0xF;
	__m128i txmm0, txmm1, txmm2, txmm3, txmm4, txmm5, txmm6, txmm7;

	txmm7 = _mm_set1_epi16(0xff);
	for (y = 0; y < height; y++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
		for (x = 0; x < width - dw; x += 16) {
			txmm0 = _mm_loadu_si128((__m128i *)&sd1[2*x]);
			txmm1 = _mm_loadu_si128((__m128i *)&sd2[2*x]);
			txmm2 =  _mm_srli_si128(txmm0, 1);
			txmm3 =  _mm_srli_si128(txmm1, 1);
			txmm4 = _mm_avg_epu8(txmm0, txmm2);
			txmm5 = _mm_avg_epu8(txmm1, txmm3);
			txmm6 = _mm_avg_epu8(txmm5, txmm4);
			txmm6 = _mm_and_si128(txmm6, txmm7);
			txmm0 = _mm_loadu_si128((__m128i *)&sd1[2 * x + 16]);
			txmm1 = _mm_loadu_si128((__m128i *)&sd2[2 * x + 16]);
			txmm2 =  _mm_srli_si128(txmm0, 1);
			txmm3 =  _mm_srli_si128(txmm1, 1);
			txmm4 = _mm_avg_epu8(txmm0, txmm2);
			txmm5 = _mm_avg_epu8(txmm1, txmm3);
			txmm5 = _mm_avg_epu8(txmm5, txmm4);
			txmm5 = _mm_and_si128(txmm5, txmm7);
			txmm1 = _mm_packus_epi16(txmm6, txmm5);
			_mm_storeu_si128((__m128i *)&dd[x], txmm1);

		}
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
		for (; x < width; x++) {
			dd[x] = (sd1[x * 2] + sd1[x * 2 + 1] + sd2[x * 2] +
				sd2[x * 2 + 1] + 2) >> 2;
		}

		sd1 += src_stride2;
		sd2 += src_stride2;
		dd += dst_stride;
	}

	return (MLIB_SUCCESS);
}