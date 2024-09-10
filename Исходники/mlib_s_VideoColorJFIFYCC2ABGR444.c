mlib_status
mlib_VideoColorJFIFYCC2ABGR444_naligned(
	mlib_u8 *abgr,
	const mlib_u8 *y,
	const mlib_u8 *cb,
	const mlib_u8 *cr,
	mlib_s32 n)
{
	/* 1.402 * 8192 */
	const __m128i x_c13 = _mm_set1_epi16(0x2cdd);
	const mlib_s32 c13 = 0x2cdd;

	/* abs(-0.34414) * 8192 */
	const __m128i x_c22 = _mm_set1_epi16(0xb03);
	const mlib_s32 c22 = 0xb03;

	/* abs(-0.71414) * 8192 */
	const __m128i x_c23 = _mm_set1_epi16(0x16da);
	const mlib_s32 c23 = 0x16da;

	/* 1.772 * 8192 */
	const __m128i x_c32 = _mm_set1_epi16(0x38b4);
	const mlib_s32 c32 = 0x38b4;

	/* -179.456 * 32 */
	const __m128i x_coff0 = _mm_set1_epi16(0xe991);
	const mlib_s32 coff0 = (mlib_s32)0xffffe991;

	/* 135.45984 * 32 */
	const __m128i x_coff1 = _mm_set1_epi16(0x10ef);
	const mlib_s32 coff1 = 0x10ef;

	/* -226.816 * 32 */
	const __m128i x_coff2 = _mm_set1_epi16(0xe3a6);
	const mlib_s32 coff2 = (mlib_s32)0xffffe3a6;

	const __m128i x_a = _mm_set1_epi8(0xff);
	const __m128i x_zero = _mm_setzero_si128();

	/* __m128i variables */
	__m128i x_y, x_cb, x_cr, x_r, x_g, x_b, x_temp;
	__m128i x_y1, x_cb1, x_cr1, x_y2, x_cb2, x_cr2;
	__m128i x_r1, x_r2, x_g1, x_g2, x_b1, x_b2;
	__m128i x_abgrl, x_abgrh, x_grl, x_grh, x_abl, x_abh;

	/* pointers */
	__m128i *px_y, *px_cb, *px_cr, *px_abgr;
	mlib_u8 *pabgr;

	/* other var */
	mlib_s32 i, iTemp, iy1, icb1, icr1, ir1, ig1, ib1;

	px_y = (__m128i *)y;
	px_cb = (__m128i *)cb;
	px_cr = (__m128i *)cr;
	px_abgr = (__m128i *)abgr;
	i = 0;

#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
	for (; i <= n - 16; i += 16)	{
		x_y = _mm_loadu_si128(px_y);
		px_y++;
		x_y1 = _mm_unpacklo_epi8(x_y, x_zero);
		x_y2 = _mm_unpackhi_epi8(x_y, x_zero);
		x_cb = _mm_loadu_si128(px_cb);
		px_cb++;
		x_cb1 = _mm_unpacklo_epi8(x_zero, x_cb);
		x_cb2 = _mm_unpackhi_epi8(x_zero, x_cb);
		x_cr = _mm_loadu_si128(px_cr);
		px_cr++;
		x_cr1 = _mm_unpacklo_epi8(x_zero, x_cr);
		x_cr2 = _mm_unpackhi_epi8(x_zero, x_cr);

		/* lower half */
		x_temp = _mm_mulhi_epu16(x_cr1, x_c13);
		x_r1 = _mm_add_epi16(x_temp, x_coff0);
		x_temp = _mm_srai_epi16(x_r1, 5);
		x_r1 = _mm_add_epi16(x_temp, x_y1);

		x_temp = _mm_mulhi_epu16(x_cb1, x_c22);
		x_g1 = _mm_mulhi_epu16(x_cr1, x_c23);
		x_temp = _mm_add_epi16(x_temp, x_g1);
		x_g1 = _mm_sub_epi16(x_coff1, x_temp);
		x_temp = _mm_srai_epi16(x_g1, 5);
		x_g1 = _mm_add_epi16(x_temp, x_y1);

		x_temp = _mm_mulhi_epu16(x_cb1, x_c32);
		x_b1 = _mm_add_epi16(x_temp, x_coff2);
		x_temp = _mm_srai_epi16(x_b1, 5);
		x_b1 = _mm_add_epi16(x_temp, x_y1);

		/* upper half */
		x_temp = _mm_mulhi_epu16(x_cr2, x_c13);
		x_r2 = _mm_add_epi16(x_temp, x_coff0);
		x_temp = _mm_srai_epi16(x_r2, 5);
		x_r2 = _mm_add_epi16(x_temp, x_y2);

		x_temp = _mm_mulhi_epu16(x_cb2, x_c22);
		x_g2 = _mm_mulhi_epu16(x_cr2, x_c23);
		x_temp = _mm_add_epi16(x_temp, x_g2);
		x_g2 = _mm_sub_epi16(x_coff1, x_temp);
		x_temp = _mm_srai_epi16(x_g2, 5);
		x_g2 = _mm_add_epi16(x_temp, x_y2);

		x_temp = _mm_mulhi_epu16(x_cb2, x_c32);
		x_b2 = _mm_add_epi16(x_temp, x_coff2);
		x_temp = _mm_srai_epi16(x_b2, 5);
		x_b2 = _mm_add_epi16(x_temp, x_y2);

		/* pack */
		x_b = _mm_packus_epi16(x_b1, x_b2);
		x_r = _mm_packus_epi16(x_r1, x_r2);
		x_g = _mm_packus_epi16(x_g1, x_g2);

		/* create rgb sequences */
		x_abl = _mm_unpacklo_epi8(x_a, x_b);
		x_abh = _mm_unpackhi_epi8(x_a, x_b);
		x_grl = _mm_unpacklo_epi8(x_g, x_r);
		x_grh = _mm_unpackhi_epi8(x_g, x_r);

		/* save */
		x_abgrl = _mm_unpacklo_epi16(x_abl, x_grl);
		_mm_storeu_si128(px_abgr++, x_abgrl);

		x_abgrh = _mm_unpackhi_epi16(x_abl, x_grl);
		_mm_storeu_si128(px_abgr++, x_abgrh);

		x_abgrl = _mm_unpacklo_epi16(x_abh, x_grh);
		_mm_storeu_si128(px_abgr++, x_abgrl);

		x_abgrh = _mm_unpackhi_epi16(x_abh, x_grh);
		_mm_storeu_si128(px_abgr++, x_abgrh);
	}

	if (i <= n - 8) {
		x_y = _mm_loadl_epi64(px_y);
		px_y = (__m128i *) (((__m64 *)px_y) + 1);
		x_y1 = _mm_unpacklo_epi8(x_y, x_zero);
		x_cb = _mm_loadl_epi64(px_cb);
		px_cb = (__m128i *) (((__m64 *)px_cb) + 1);
		x_cb1 = _mm_unpacklo_epi8(x_zero, x_cb);
		x_cr = _mm_loadl_epi64(px_cr);
		px_cr = (__m128i *) (((__m64 *)px_cr) + 1);
		x_cr1 = _mm_unpacklo_epi8(x_zero, x_cr);

		/* lower half only */
		x_temp = _mm_mulhi_epu16(x_cr1, x_c13);
		x_r1 = _mm_add_epi16(x_temp, x_coff0);
		x_temp = _mm_srai_epi16(x_r1, 5);
		x_r1 = _mm_add_epi16(x_temp, x_y1);

		x_temp = _mm_mulhi_epu16(x_cb1, x_c22);
		x_g1 = _mm_mulhi_epu16(x_cr1, x_c23);
		x_temp = _mm_add_epi16(x_temp, x_g1);
		x_g1 = _mm_sub_epi16(x_coff1, x_temp);
		x_temp = _mm_srai_epi16(x_g1, 5);
		x_g1 = _mm_add_epi16(x_temp, x_y1);

		x_temp = _mm_mulhi_epu16(x_cb1, x_c32);
		x_b1 = _mm_add_epi16(x_temp, x_coff2);
		x_temp = _mm_srai_epi16(x_b1, 5);
		x_b1 = _mm_add_epi16(x_temp, x_y1);

		/* pack */
		x_b = _mm_packus_epi16(x_b1, x_zero);
		x_r = _mm_packus_epi16(x_r1, x_zero);
		x_g = _mm_packus_epi16(x_g1, x_zero);

		/* create rgb sequences */
		x_abl = _mm_unpacklo_epi8(x_a, x_b);
		x_grl = _mm_unpacklo_epi8(x_g, x_r);

		/* save */
		x_abgrl = _mm_unpacklo_epi16(x_abl, x_grl);
		_mm_storeu_si128(px_abgr++, x_abgrl);

		x_abgrh = _mm_unpackhi_epi16(x_abl, x_grl);
		_mm_storeu_si128(px_abgr++, x_abgrh);

		i += 8;
	}

	if (i <= n - 4) {
		iTemp = *((mlib_s32 *)px_y);
		x_y = _mm_cvtsi32_si128(iTemp);
		px_y = (__m128i *) (((mlib_s32 *)px_y) + 1);
		x_y1 = _mm_unpacklo_epi8(x_y, x_zero);

		iTemp = *((mlib_s32 *)px_cb);
		x_cb = _mm_cvtsi32_si128(iTemp);
		px_cb = (__m128i *) (((mlib_s32 *)px_cb) + 1);
		x_cb1 = _mm_unpacklo_epi8(x_zero, x_cb);

		iTemp = *((mlib_s32 *)px_cr);
		x_cr = _mm_cvtsi32_si128(iTemp);
		px_cr = (__m128i *) (((mlib_s32 *)px_cr) + 1);
		x_cr1 = _mm_unpacklo_epi8(x_zero, x_cr);

		/* 64 0f lower half only */
		x_temp = _mm_mulhi_epu16(x_cr1, x_c13);
		x_r1 = _mm_add_epi16(x_temp, x_coff0);
		x_temp = _mm_srai_epi16(x_r1, 5);
		x_r1 = _mm_add_epi16(x_temp, x_y1);

		x_temp = _mm_mulhi_epu16(x_cb1, x_c22);
		x_g1 = _mm_mulhi_epu16(x_cr1, x_c23);
		x_temp = _mm_add_epi16(x_temp, x_g1);
		x_g1 = _mm_sub_epi16(x_coff1, x_temp);
		x_temp = _mm_srai_epi16(x_g1, 5);
		x_g1 = _mm_add_epi16(x_temp, x_y1);
		x_temp = _mm_mulhi_epu16(x_cb1, x_c32);
		x_b1 = _mm_add_epi16(x_temp, x_coff2);
		x_temp = _mm_srai_epi16(x_b1, 5);
		x_b1 = _mm_add_epi16(x_temp, x_y1);

		/* pack */
		x_b = _mm_packus_epi16(x_b1, x_zero);
		x_r = _mm_packus_epi16(x_r1, x_zero);
		x_g = _mm_packus_epi16(x_g1, x_zero);

		/* create rgb sequences */
		x_abl = _mm_unpacklo_epi8(x_a, x_b);
		x_grl = _mm_unpacklo_epi8(x_g, x_r);

		/* save */
		x_abgrl = _mm_unpacklo_epi16(x_abl, x_grl);
		_mm_storeu_si128(px_abgr++, x_abgrl);

		i += 4;
	}

	/* pure C implementation */
	pabgr = (mlib_u8 *)px_abgr;
	for (; i < n; i++) {
		iy1 = y[i];
		icb1 = cb[i];
		icr1 = cr[i];

		iTemp = (icr1 * c13) >> 8;
		ir1 = (iTemp + coff0) >> 5;
		ir1 += iy1;

		iTemp = (icb1 * c22) >> 8;
		ig1 = (icr1 * c23) >> 8;
		iTemp += ig1;
		ig1 = coff1 - iTemp;
		iTemp = ig1 >> 5;
		ig1 = iTemp + iy1;

		iTemp = (icb1 * c32) >> 8;
		ib1 = iTemp + coff2;
		iTemp = ib1 >> 5;
		ib1 = iTemp + iy1;

		pabgr[0] = 0xff;
		CLAMP_U8(ib1, pabgr[1]);
		CLAMP_U8(ig1, pabgr[2]);
		CLAMP_U8(ir1, pabgr[3]);

		pabgr += 4;
	}

	return (MLIB_SUCCESS);
}