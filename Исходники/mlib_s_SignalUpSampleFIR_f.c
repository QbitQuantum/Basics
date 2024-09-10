void
mlib_SignalFIR_s16_to_d64(
    mlib_d64 *pdst,
    mlib_s16 *psrc,
    mlib_s32 n)
{
	mlib_s32 i;

	for (i = 0; (i < n) && ((mlib_addr)psrc & 15); i++) {
		(*pdst++) = (mlib_d64)(*psrc++);
	}

	if (((mlib_addr)pdst & 15) == 0) {

	for (; i < n - 7; i += 8) {
		__m128i x_sd0, x_sd1, x_sd2, x_sd3, x_sd4;
		__m128d xd_sd0, xd_sd1, xd_sd2, xd_sd3;
		x_sd0 = _mm_load_si128((__m128i *)psrc);
		psrc += 8;
		x_sd1 = _mm_srai_epi16(x_sd0, 15);
		x_sd2 = _mm_unpacklo_epi16(x_sd0, x_sd1);
		x_sd3 = _mm_unpackhi_epi16(x_sd0, x_sd1);
		xd_sd0 = _mm_cvtepi32_pd(x_sd2);
		xd_sd1 = _mm_cvtepi32_pd(_mm_srli_si128(x_sd2, 8));
		xd_sd2 = _mm_cvtepi32_pd(x_sd3);
		xd_sd3 = _mm_cvtepi32_pd(_mm_srli_si128(x_sd3, 8));
		_mm_store_pd(pdst, xd_sd0);
		_mm_store_pd((pdst + 2), xd_sd1);
		_mm_store_pd((pdst + 4), xd_sd2);
		_mm_store_pd((pdst + 6), xd_sd3);
		pdst += 8;
	}

	if (i < n - 3) {
		__m128i x_sd0, x_sd1, x_sd2, x_sd3, x_sd4;
		__m128d xd_sd0, xd_sd1;
		x_sd0 = _mm_loadl_epi64((void *)psrc);
		psrc += 4;
		x_sd1 = _mm_srai_epi16(x_sd0, 15);
		x_sd2 = _mm_unpacklo_epi16(x_sd0, x_sd1);
		xd_sd0 = _mm_cvtepi32_pd(x_sd2);
		xd_sd1 = _mm_cvtepi32_pd(_mm_srli_si128(x_sd2, 8));
		_mm_store_pd(pdst, xd_sd0);
		_mm_store_pd((pdst + 2), xd_sd1);
		pdst += 4;
		i += 4;
	}

	} else {

	for (; i < n - 7; i += 8) {
		__m128i x_sd0, x_sd1, x_sd2, x_sd3, x_sd4;
		__m128d xd_sd0, xd_sd1, xd_sd2, xd_sd3;
		x_sd0 = _mm_load_si128((__m128i *)psrc);
		x_sd1 = _mm_srai_epi16(x_sd0, 15);
		x_sd2 = _mm_unpacklo_epi16(x_sd0, x_sd1);
		x_sd3 = _mm_unpackhi_epi16(x_sd0, x_sd1);
		xd_sd0 = _mm_cvtepi32_pd(x_sd2);
		xd_sd1 = _mm_cvtepi32_pd(_mm_srli_si128(x_sd2, 8));
		xd_sd2 = _mm_cvtepi32_pd(x_sd3);
		xd_sd3 = _mm_cvtepi32_pd(_mm_srli_si128(x_sd3, 8));
		_mm_storeu_pd(pdst, xd_sd0);
		_mm_storeu_pd((pdst + 2), xd_sd1);
		_mm_storeu_pd((pdst + 4), xd_sd2);
		_mm_storeu_pd((pdst + 6), xd_sd3);
		psrc += 8;
		pdst += 8;
	}

	if (i < n - 3) {
		__m128i x_sd0, x_sd1, x_sd2, x_sd3, x_sd4;
		__m128d xd_sd0, xd_sd1;
		x_sd0 = _mm_loadl_epi64((void *)psrc);
		psrc += 4;
		x_sd1 = _mm_srai_epi16(x_sd0, 15);
		x_sd2 = _mm_unpacklo_epi16(x_sd0, x_sd1);
		xd_sd0 = _mm_cvtepi32_pd(x_sd2);
		xd_sd1 = _mm_cvtepi32_pd(_mm_srli_si128(x_sd2, 8));
		_mm_storeu_pd(pdst, xd_sd0);
		_mm_storeu_pd((pdst + 2), xd_sd1);
		pdst += 4;
		i += 4;
	}
	}

	for (; i < n; i++) {
		(*pdst++) = (mlib_d64)(*psrc++);
	}
}