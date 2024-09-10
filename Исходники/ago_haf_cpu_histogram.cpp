static int HafCpu_Histogram3Thresholds_DATA_U8
	(
		vx_uint32     dstHist[],
		vx_uint8      distThreshold0,
		vx_uint8      distThreshold1,
		vx_uint8      distThreshold2,
		vx_uint32     srcWidth,
		vx_uint32     srcHeight,
		vx_uint8    * pSrcImage,
		vx_uint32     srcImageStrideInBytes
	)
{
	// offset: to convert the range from 0..255 to -128..127, because SSE does not have compare instructions for unsigned bytes
	// thresh: source threshold in -128..127 range
	__m128i offset = _mm_set1_epi8((char)0x80);
	__m128i T0 = _mm_set1_epi8((char)((distThreshold0 - 1) ^ 0x80));
	__m128i T1 = _mm_set1_epi8((char)((distThreshold1 - 1) ^ 0x80));
	__m128i T2 = _mm_set1_epi8((char)((distThreshold2 - 1) ^ 0x80));
	__m128i onemask = _mm_set1_epi8((char)1);
	// process one pixel row at a time that counts "pixel < srcThreshold"
	__m128i count0 = _mm_set1_epi8((char)0);
	__m128i count1 = _mm_set1_epi8((char)0);
	__m128i count2 = _mm_set1_epi8((char)0);
	vx_uint8 * srcRow = pSrcImage;
	vx_uint32 width = (srcWidth + 15) >> 4;
	for (unsigned int y = 0; y < srcHeight; y++) {
		__m128i * src = (__m128i *)srcRow;
		for (unsigned int x = 0; x < width; x++) {
			__m128i pixels = _mm_load_si128(src++);
			pixels = _mm_xor_si128(pixels, offset);
			__m128i cmpout;
			cmpout = _mm_cmpgt_epi8(pixels, T0);
			cmpout = _mm_and_si128(cmpout, onemask);
			cmpout = _mm_sad_epu8(cmpout, onemask);
			count0 = _mm_add_epi32(count0, cmpout);
			cmpout = _mm_cmpgt_epi8(pixels, T1);
			cmpout = _mm_and_si128(cmpout, onemask);
			cmpout = _mm_sad_epu8(cmpout, onemask);
			count1 = _mm_add_epi32(count1, cmpout);
			cmpout = _mm_cmpgt_epi8(pixels, T2);
			cmpout = _mm_and_si128(cmpout, onemask);
			cmpout = _mm_sad_epu8(cmpout, onemask);
			count2 = _mm_add_epi32(count2, cmpout);
		}
		srcRow += srcImageStrideInBytes;
	}
	// extract histogram from count: special case needed when T1 == T2
	dstHist[0] = M128I(count0).m128i_u32[0] + M128I(count0).m128i_u32[2];
	dstHist[1] = M128I(count1).m128i_u32[0] + M128I(count1).m128i_u32[2] - dstHist[0];
	dstHist[2] = M128I(count2).m128i_u32[0] + M128I(count2).m128i_u32[2] - dstHist[0] - dstHist[1];
	dstHist[3] = srcWidth * srcHeight - dstHist[0] - dstHist[1] - dstHist[2];
	if (M128I(T1).m128i_i8[0] == M128I(T2).m128i_i8[0]) {
		dstHist[2] = dstHist[3];
		dstHist[3] = 0;
	}
	return AGO_SUCCESS;
}