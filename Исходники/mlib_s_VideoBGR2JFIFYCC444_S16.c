mlib_status
mlib_VideoColorBGR2JFIFYCC444_S16_aligned(
	mlib_s16 *y,
	mlib_s16 *cb,
	mlib_s16 *cr,
	const mlib_s16 *bgr,
	mlib_s32 n)
{
	/* 0.299*32768 */
	const __m128i x_c11 = _mm_set1_epi16(9798);

	/* 0.587*32768 */
	const __m128i x_c12 = _mm_set1_epi16(19235);

	/* 0.114*32768 */
	const __m128i x_c13 = _mm_set1_epi16(3735);

	/* -0.16874*32768 */
	const __m128i x_c21 = _mm_set1_epi16(-5529);

	/* -0.33126*32768 */
	const __m128i x_c22 = _mm_set1_epi16(-10855);

	/* 0.5*32768 */
	const __m128i x_c23 = _mm_set1_epi16(16384);

	/* 0.5*32768 */
	const __m128i x_c31 = x_c23;

	/* -0.41869*32768 */
	const __m128i x_c32 = _mm_set1_epi16(-13720);

	/* -0.08131*32768 */
	const __m128i x_c33 = _mm_set1_epi16(-2664);

	/* 2048 */
	const __m128i x_coff = _mm_set1_epi16(2048 << 2);

	const __m128i x_zero = _mm_setzero_si128();

	__m128i x_bgr0, x_bgr1, x_bgr2, x_r, x_g, x_b;
	__m128i x_y, x_cb, x_cr;
	__m128i x_t0, x_t1, x_t2, x_t3, x_t4, x_t5;
	__m128i *px_y, *px_cb, *px_cr, *px_bgr;
	mlib_d64 fr, fg, fb, fy, fcb, fcr;
	mlib_s32 i;

	px_y = (__m128i *)y;
	px_cb = (__m128i *)cb;
	px_cr = (__m128i *)cr;
	px_bgr = (__m128i *)bgr;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
	for (i = 0; i <= (n - 8); i += 8) {
		x_bgr0 = _mm_load_si128(px_bgr++);
		x_bgr0 = _mm_slli_epi16(x_bgr0, 3);
		x_bgr1 = _mm_load_si128(px_bgr++);
		x_bgr1 = _mm_slli_epi16(x_bgr1, 3);
		x_bgr2 = _mm_load_si128(px_bgr++);
		x_bgr2 = _mm_slli_epi16(x_bgr2, 3);
		SeparateBGR48_S16;

		x_t0 = _mm_mulhi_epi16(x_r, x_c11);
		x_t1 = _mm_mulhi_epi16(x_g, x_c12);
		x_t2 = _mm_mulhi_epi16(x_b, x_c13);
		x_y = _mm_add_epi16(x_t0, x_t1);
		x_y = _mm_add_epi16(x_y, x_t2);

		x_t0 = _mm_mulhi_epi16(x_r, x_c21);
		x_t1 = _mm_mulhi_epi16(x_g, x_c22);
		x_t2 = _mm_mulhi_epi16(x_b, x_c23);
		x_cb = _mm_add_epi16(x_t0, x_t1);
		x_cb = _mm_add_epi16(x_cb, x_coff);
		x_cb = _mm_add_epi16(x_cb, x_t2);

		x_t0 = _mm_mulhi_epi16(x_r, x_c31);
		x_t1 = _mm_mulhi_epi16(x_g, x_c32);
		x_t2 = _mm_mulhi_epi16(x_b, x_c33);
		x_cr = _mm_add_epi16(x_t0, x_t1);
		x_cr = _mm_add_epi16(x_cr, x_coff);
		x_cr = _mm_add_epi16(x_cr, x_t2);

		/* save */
		x_y = _mm_srli_epi16(x_y, 2);
		x_cb = _mm_srli_epi16(x_cb, 2);
		x_cr = _mm_srli_epi16(x_cr, 2);
		_mm_store_si128(px_y++, x_y);
		_mm_store_si128(px_cb++, x_cb);
		_mm_store_si128(px_cr++, x_cr);
	}

	if (i <= (n - 4)) {
		x_bgr0 = _mm_load_si128(px_bgr++);
		x_bgr0 = _mm_slli_epi16(x_bgr0, 3);
		x_bgr1 = _mm_loadl_epi64(px_bgr);
		x_bgr1 = _mm_slli_epi16(x_bgr1, 3);
		px_bgr = (__m128i *)((__m64 *)px_bgr + 1);
		SeparateBGR24_S16;

		x_t0 = _mm_mulhi_epi16(x_r, x_c11);
		x_t1 = _mm_mulhi_epi16(x_g, x_c12);
		x_t2 = _mm_mulhi_epi16(x_b, x_c13);
		x_y = _mm_add_epi16(x_t0, x_t1);
		x_y = _mm_add_epi16(x_y, x_t2);

		x_t0 = _mm_mulhi_epi16(x_r, x_c21);
		x_t1 = _mm_mulhi_epi16(x_g, x_c22);
		x_t2 = _mm_mulhi_epi16(x_b, x_c23);
		x_cb = _mm_add_epi16(x_t0, x_t1);
		x_cb = _mm_add_epi16(x_cb, x_coff);
		x_cb = _mm_add_epi16(x_cb, x_t2);

		x_t0 = _mm_mulhi_epi16(x_r, x_c31);
		x_t1 = _mm_mulhi_epi16(x_g, x_c32);
		x_t2 = _mm_mulhi_epi16(x_b, x_c33);
		x_cr = _mm_add_epi16(x_t0, x_t1);
		x_cr = _mm_add_epi16(x_cr, x_coff);
		x_cr = _mm_add_epi16(x_cr, x_t2);

		/* save */
		x_y = _mm_srli_epi16(x_y, 2);
		x_cb = _mm_srli_epi16(x_cb, 2);
		x_cr = _mm_srli_epi16(x_cr, 2);
		_mm_storel_epi64(px_y, x_y);
		px_y = (__m128i *)((__m64 *)px_y + 1);
		_mm_storel_epi64(px_cb, x_cb);
		px_cb = (__m128i *)((__m64 *)px_cb + 1);
		_mm_storel_epi64(px_cr, x_cr);
		px_cr = (__m128i *)((__m64 *)px_cr + 1);

		i += 4;
	}

	for (; i <= (n - 1); i++) {
		fb = bgr[3 * i];
		fg = bgr[3 * i + 1];
		fr = bgr[3 * i + 2];

		fy = 0.29900f * fr + 0.58700f * fg + 0.11400f * fb;
		fcb = -0.16874f * fr - 0.33126f * fg + 0.50000f * fb + 2048;
		fcr = 0.50000f * fr - 0.41869f * fg - 0.08131f * fb + 2048;

		y[i] = (mlib_s16)fy;
		cb[i] = (mlib_s16)fcb;
		cr[i] = (mlib_s16)fcr;
	}

	return (MLIB_SUCCESS);
}