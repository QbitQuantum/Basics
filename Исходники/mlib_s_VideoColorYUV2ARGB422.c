mlib_status
mlib_VideoColorYUV2ARGB422_aligned(
	mlib_u8 *argb,
	const mlib_u8 *y,
	const mlib_u8 *u,
	const mlib_u8 *v,
	mlib_s32 width,
	mlib_s32 height,
	mlib_s32 argb_stride,
	mlib_s32 y_stride,
	mlib_s32 uv_stride)
{
/* 1.1644  * 8192 */
	const __m128i c0 = _mm_set1_epi16(0x2543);
	const mlib_s32 ic0 = 0x2543;

/* 2.0184  * 8192 */
	const __m128i c1 = _mm_set1_epi16(0x4097);
	const mlib_s32 ic1 = 0x4097;

/* abs( -0.3920 * 8192 ) */
	const __m128i c4 = _mm_set1_epi16(0xc8b);
	const mlib_s32 ic4 = 0xc8b;

/* abs( -0.8132 * 8192 ) */
	const __m128i c5 = _mm_set1_epi16(0x1a06);
	const mlib_s32 ic5 = 0x1a06;

/* 1.5966  * 8192 */
	const __m128i c8 = _mm_set1_epi16(0x3317);
	const mlib_s32 ic8 = 0x3317;

/* -276.9856 * 32 */
	const __m128i coff0 = _mm_set1_epi16(0xdd60);
	const mlib_s32 icoff0 = (mlib_s32)0xffffdd60;

/* 135.6352  * 32 */
	const __m128i coff1 = _mm_set1_epi16(0x10f4);
	const mlib_s32 icoff1 = 0x10f4;

/* -222.9952 * 32 */
	const __m128i coff2 = _mm_set1_epi16(0xe420);
	const mlib_s32 icoff2 = (mlib_s32)0xffffe420;

/* loop variable */
	mlib_s32 jH, iW;

/* pointers */
	mlib_u8 *pY, *pU, *pV, *pD, *pdd, *ptemp;
	__m128i *py, *pu, *pv;

/* variables */
	__m128i sy1, sy2, sy3, sy4, su1, su2, sv1, sv2;
	__m128i du0, du1, dv1, dv2;
	__m128i db1, db2, db3, db4, dr1, dr2, dr3, dr4, dg1, dg2, dg3, dg4;
	__m128i ddy1, ddy2, ddy3, ddy4, dzrl, dzrh, dgbl, dgbh, drgbh, drgbl;
	__m128i db_h, db_l, dg_h, dg_l, dr_h, dr_l, temp, bak;
	const __m128i x_zero = _mm_setzero_si128();
	const __m128i x_mask = _mm_set1_epi32(0xff);

/* for 4-pixel computing */
	mlib_s32 iu, iv, ig, ir, ib, iTemp;
	mlib_s32 iu0, iu1, iv1, iv2;

	pY  = (mlib_u8 *)y;
	pU  = (mlib_u8 *)u;
	pV  = (mlib_u8 *)v;
	pD = (mlib_u8 *)argb;

	for (jH = 0; jH < height; jH++) {
		py = (__m128i *)pY;
		pu = (__m128i *)pU;
		pv = (__m128i *)pV;
		pdd = pD;
		iW = 0;

#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
		/* 32 pixels */
		for (; iW <= width - 32; iW += 32) {
			/* load y u v, and expand */
			temp = _mm_load_si128(pu);
			su1 = _mm_unpacklo_epi8(x_zero, temp);
			su2 = _mm_unpackhi_epi8(x_zero, temp);
			pu++;
			temp = _mm_load_si128(pv);
			sv1 = _mm_unpacklo_epi8(x_zero, temp);
			sv2 = _mm_unpackhi_epi8(x_zero, temp);
			pv++;
			temp = _mm_load_si128(py);
			sy1 = _mm_unpacklo_epi8(x_zero, temp);
			sy2 = _mm_unpackhi_epi8(x_zero, temp);
			py++;
			temp = _mm_load_si128(py);
			sy3 = _mm_unpacklo_epi8(x_zero, temp);
			sy4 = _mm_unpackhi_epi8(x_zero, temp);
			py++;

			/* pre-calc d[r/g/b][1234] */
			du0 = _mm_mulhi_epu16(su1, c1);
			db_l = _mm_add_epi16(du0, coff0);
			du0 = _mm_mulhi_epu16(su2, c1);
			db_h = _mm_add_epi16(du0, coff0);

			du1 = _mm_mulhi_epu16(su1, c4);
			dv1 = _mm_mulhi_epu16(sv1, c5);
			temp = _mm_add_epi16(du1, dv1);
			dg_l = _mm_sub_epi16(coff1, temp);
			du1 = _mm_mulhi_epu16(su2, c4);
			dv1 = _mm_mulhi_epu16(sv2, c5);
			temp = _mm_add_epi16(du1, dv1);
			dg_h = _mm_sub_epi16(coff1, temp);

			dv2 = _mm_mulhi_epu16(sv1, c8);
			dr_l = _mm_add_epi16(dv2, coff2);
			dv2 = _mm_mulhi_epu16(sv2, c8);
			dr_h = _mm_add_epi16(dv2, coff2);

			ddy1 = _mm_mulhi_epu16(sy1, c0);
			ddy2 = _mm_mulhi_epu16(sy2, c0);
			ddy3 = _mm_mulhi_epu16(sy3, c0);
			ddy4 = _mm_mulhi_epu16(sy4, c0);

			/* db1/2/3/4 */
			bak = _mm_unpacklo_epi16(db_l, db_l);
			db1 = _mm_add_epi16(ddy1, bak);
			bak = _mm_unpackhi_epi16(db_l, db_l);
			db2 = _mm_add_epi16(ddy2, bak);

			bak = _mm_unpacklo_epi16(db_h, db_h);
			db3 = _mm_add_epi16(ddy3, bak);
			bak = _mm_unpackhi_epi16(db_h, db_h);
			db4 = _mm_add_epi16(ddy4, bak);

			/* dg1/2/3/4 */
			bak = _mm_unpacklo_epi16(dg_l, dg_l);
			dg1 = _mm_add_epi16(ddy1, bak);
			bak = _mm_unpackhi_epi16(dg_l, dg_l);
			dg2 = _mm_add_epi16(ddy2, bak);

			bak = _mm_unpacklo_epi16(dg_h, dg_h);
			dg3 = _mm_add_epi16(ddy3, bak);
			bak = _mm_unpackhi_epi16(dg_h, dg_h);
			dg4 = _mm_add_epi16(ddy4, bak);

			/* dr1/2/3/4 */
			bak = _mm_unpacklo_epi16(dr_l, dr_l);
			dr1 = _mm_add_epi16(ddy1, bak);
			bak = _mm_unpackhi_epi16(dr_l, dr_l);
			dr2 = _mm_add_epi16(ddy2, bak);

			bak = _mm_unpacklo_epi16(dr_h, dr_h);
			dr3 = _mm_add_epi16(ddy3, bak);
			bak = _mm_unpackhi_epi16(dr_h, dr_h);
			dr4 = _mm_add_epi16(ddy4, bak);

			db1 = _mm_srai_epi16(db1, 5);
			db2 = _mm_srai_epi16(db2, 5);
			db3 = _mm_srai_epi16(db3, 5);
			db4 = _mm_srai_epi16(db4, 5);
			dg1 = _mm_srai_epi16(dg1, 5);
			dg2 = _mm_srai_epi16(dg2, 5);
			dg3 = _mm_srai_epi16(dg3, 5);
			dg4 = _mm_srai_epi16(dg4, 5);
			dr1 = _mm_srai_epi16(dr1, 5);
			dr2 = _mm_srai_epi16(dr2, 5);
			dr3 = _mm_srai_epi16(dr3, 5);
			dr4 = _mm_srai_epi16(dr4, 5);

			/* pack: 16=>8 */
			db1 = _mm_packus_epi16(db1, db2);
			db2 = _mm_packus_epi16(db3, db4);
			dr1 = _mm_packus_epi16(dr1, dr2);
			dr2 = _mm_packus_epi16(dr3, dr4);
			dg1 = _mm_packus_epi16(dg1, dg2);
			dg2 = _mm_packus_epi16(dg3, dg4);

			/* create rgb sequences : db/dr/dg[1] */
			dzrl = _mm_unpacklo_epi8(x_zero, dr1);
			dzrh = _mm_unpackhi_epi8(x_zero, dr1);
			dgbl = _mm_unpacklo_epi8(dg1, db1);
			dgbh = _mm_unpackhi_epi8(dg1, db1);

			drgbl = _mm_unpacklo_epi16(dzrl, dgbl);
			SAVE_ARGB1(drgbl);

			drgbh = _mm_unpackhi_epi16(dzrl, dgbl);
			SAVE_ARGB1(drgbh);

			drgbl = _mm_unpacklo_epi16(dzrh, dgbh);
			SAVE_ARGB1(drgbl);

			drgbh = _mm_unpackhi_epi16(dzrh, dgbh);
			SAVE_ARGB1(drgbh);

			/* create rgb sequences : db/dr/dg[2] */
			dzrl = _mm_unpacklo_epi8(x_zero, dr2);
			dzrh = _mm_unpackhi_epi8(x_zero, dr2);
			dgbl = _mm_unpacklo_epi8(dg2, db2);
			dgbh = _mm_unpackhi_epi8(dg2, db2);

			drgbl = _mm_unpacklo_epi16(dzrl, dgbl);
			SAVE_ARGB1(drgbl);

			drgbh = _mm_unpackhi_epi16(dzrl, dgbl);
			SAVE_ARGB1(drgbh);

			drgbl = _mm_unpacklo_epi16(dzrh, dgbh);
			SAVE_ARGB1(drgbl);

			drgbh = _mm_unpackhi_epi16(dzrh, dgbh);
			SAVE_ARGB1(drgbh);
		}

		/* 16 pixels */
		if (iW <= width - 16) {
			/* load y u v, and expand */
			temp = _mm_loadl_epi64(pu);
			su1 = _mm_unpacklo_epi8(x_zero, temp);
			pu = (__m128i *) (((__m64 *)pu) + 1);
			temp = _mm_loadl_epi64(pv);
			sv1 = _mm_unpacklo_epi8(x_zero, temp);
			pv = (__m128i *) (((__m64 *)pv) + 1);
			temp = _mm_load_si128(py);
			sy1 = _mm_unpacklo_epi8(x_zero, temp);
			sy2 = _mm_unpackhi_epi8(x_zero, temp);
			py++;

			/* pre-calc d[r/g/b][12] */
			du0 = _mm_mulhi_epu16(su1, c1);
			db_l = _mm_add_epi16(du0, coff0);

			du1 = _mm_mulhi_epu16(su1, c4);
			dv1 = _mm_mulhi_epu16(sv1, c5);
			temp = _mm_add_epi16(du1, dv1);
			dg_l = _mm_sub_epi16(coff1, temp);

			dv2 = _mm_mulhi_epu16(sv1, c8);
			dr_l = _mm_add_epi16(dv2, coff2);

			ddy1 = _mm_mulhi_epu16(sy1, c0);
			ddy2 = _mm_mulhi_epu16(sy2, c0);

			/* db1/2 */
			bak = _mm_unpacklo_epi16(db_l, db_l);
			db1 = _mm_add_epi16(ddy1, bak);
			bak = _mm_unpackhi_epi16(db_l, db_l);
			db2 = _mm_add_epi16(ddy2, bak);

			/* dg1/2 */
			bak = _mm_unpacklo_epi16(dg_l, dg_l);
			dg1 = _mm_add_epi16(ddy1, bak);
			bak = _mm_unpackhi_epi16(dg_l, dg_l);
			dg2 = _mm_add_epi16(ddy2, bak);

			/* dr1/2 */
			bak = _mm_unpacklo_epi16(dr_l, dr_l);
			dr1 = _mm_add_epi16(ddy1, bak);
			bak = _mm_unpackhi_epi16(dr_l, dr_l);
			dr2 = _mm_add_epi16(ddy2, bak);

			db1 = _mm_srai_epi16(db1, 5);
			db2 = _mm_srai_epi16(db2, 5);
			dg1 = _mm_srai_epi16(dg1, 5);
			dg2 = _mm_srai_epi16(dg2, 5);
			dr1 = _mm_srai_epi16(dr1, 5);
			dr2 = _mm_srai_epi16(dr2, 5);

			/* pack: 16=>8 */
			db1 = _mm_packus_epi16(db1, db2);
			dr1 = _mm_packus_epi16(dr1, dr2);
			dg1 = _mm_packus_epi16(dg1, dg2);

			/* create rgb sequences : db/dr/dg[1] */
			dzrl = _mm_unpacklo_epi8(x_zero, dr1);
			dzrh = _mm_unpackhi_epi8(x_zero, dr1);
			dgbl = _mm_unpacklo_epi8(dg1, db1);
			dgbh = _mm_unpackhi_epi8(dg1, db1);

			drgbl = _mm_unpacklo_epi16(dzrl, dgbl);
			SAVE_ARGB1(drgbl);

			drgbh = _mm_unpackhi_epi16(dzrl, dgbl);
			SAVE_ARGB1(drgbh);

			drgbl = _mm_unpacklo_epi16(dzrh, dgbh);
			SAVE_ARGB1(drgbl);

			drgbh = _mm_unpackhi_epi16(dzrh, dgbh);
			SAVE_ARGB1(drgbh);

			iW += 16;
		}

		/* 8 pixels */
		if (iW <= width - 8) {
			/* load y u v, and expand */
			iTemp = *((mlib_s32 *)pu);
			temp = _mm_cvtsi32_si128(iTemp);
			su1 = _mm_unpacklo_epi8(x_zero, temp);
			pu = (__m128i *) (((mlib_s32 *)pu) + 1);
			iTemp = *((mlib_s32 *)pv);
			temp = _mm_cvtsi32_si128(iTemp);
			sv1 = _mm_unpacklo_epi8(x_zero, temp);
			pv = (__m128i *) (((mlib_s32 *)pv) + 1);
			temp = _mm_loadl_epi64(py);
			sy1 = _mm_unpacklo_epi8(x_zero, temp);
			py = (__m128i *) (((__m64 *)py) + 1);

			/* pre-calc d[r/g/b][1] */
			du0 = _mm_mulhi_epu16(su1, c1);
			db_l = _mm_add_epi16(du0, coff0);

			du1 = _mm_mulhi_epu16(su1, c4);
			dv1 = _mm_mulhi_epu16(sv1, c5);
			temp = _mm_add_epi16(du1, dv1);
			dg_l = _mm_sub_epi16(coff1, temp);

			dv2 = _mm_mulhi_epu16(sv1, c8);
			dr_l = _mm_add_epi16(dv2, coff2);

			ddy1 = _mm_mulhi_epu16(sy1, c0);

			/* db1 */
			bak = _mm_unpacklo_epi16(db_l, db_l);
			db1 = _mm_add_epi16(ddy1, bak);

			/* dg1 */
			bak = _mm_unpacklo_epi16(dg_l, dg_l);
			dg1 = _mm_add_epi16(ddy1, bak);

			/* dr1 */
			bak = _mm_unpacklo_epi16(dr_l, dr_l);
			dr1 = _mm_add_epi16(ddy1, bak);

			db1 = _mm_srai_epi16(db1, 5);
			dg1 = _mm_srai_epi16(dg1, 5);
			dr1 = _mm_srai_epi16(dr1, 5);

			/* pack: 16=>8 */
			db1 = _mm_packus_epi16(db1, x_zero);
			dr1 = _mm_packus_epi16(dr1, x_zero);
			dg1 = _mm_packus_epi16(dg1, x_zero);

			/* create rgb sequences : db/dr/dg[1] */
			dzrl = _mm_unpacklo_epi8(x_zero, dr1);
			dgbl = _mm_unpacklo_epi8(dg1, db1);

			drgbl = _mm_unpacklo_epi16(dzrl, dgbl);
			SAVE_ARGB1(drgbl);

			drgbh = _mm_unpackhi_epi16(dzrl, dgbl);
			SAVE_ARGB1(drgbh);

			iW += 8;
		}

		/* 4 pixels */
		if (iW <= width - 4) {
			/* load y u v, and expand */
			iTemp = *((mlib_s16 *)pu);
			temp = _mm_cvtsi32_si128(iTemp);
			su1 = _mm_unpacklo_epi8(x_zero, temp);
			pu = (__m128i *) (((mlib_s16 *)pu) + 1);
			iTemp = *((mlib_s16 *)pv);
			temp = _mm_cvtsi32_si128(iTemp);
			sv1 = _mm_unpacklo_epi8(x_zero, temp);
			pv = (__m128i *) (((mlib_s16 *)pv) + 1);
			iTemp = *((mlib_s32 *)py);
			temp = _mm_cvtsi32_si128(iTemp);
			sy1 = _mm_unpacklo_epi8(x_zero, temp);
			py = (__m128i *) (((mlib_s32 *)py) + 1);

			/* pre-calc d[r/g/b][1] */
			du0 = _mm_mulhi_epu16(su1, c1);
			db_l = _mm_add_epi16(du0, coff0);

			du1 = _mm_mulhi_epu16(su1, c4);
			dv1 = _mm_mulhi_epu16(sv1, c5);
			temp = _mm_add_epi16(du1, dv1);
			dg_l = _mm_sub_epi16(coff1, temp);

			dv2 = _mm_mulhi_epu16(sv1, c8);
			dr_l = _mm_add_epi16(dv2, coff2);

			ddy1 = _mm_mulhi_epu16(sy1, c0);

			/* db1 */
			bak = _mm_unpacklo_epi16(db_l, db_l);
			db1 = _mm_add_epi16(ddy1, bak);

			/* dg1 */
			bak = _mm_unpacklo_epi16(dg_l, dg_l);
			dg1 = _mm_add_epi16(ddy1, bak);

			/* dr1 */
			bak = _mm_unpacklo_epi16(dr_l, dr_l);
			dr1 = _mm_add_epi16(ddy1, bak);

			db1 = _mm_srai_epi16(db1, 5);
			dg1 = _mm_srai_epi16(dg1, 5);
			dr1 = _mm_srai_epi16(dr1, 5);

			/* pack: 16=>8 */
			db1 = _mm_packus_epi16(db1, x_zero);
			dr1 = _mm_packus_epi16(dr1, x_zero);
			dg1 = _mm_packus_epi16(dg1, x_zero);

			/* create rgb sequences : db/dr/dg[1] */
			dzrl = _mm_unpacklo_epi8(x_zero, dr1);
			dgbl = _mm_unpacklo_epi8(dg1, db1);

			drgbl = _mm_unpacklo_epi16(dzrl, dgbl);
			SAVE_ARGB1(drgbl);

			iW += 4;
		}

		/* 2 pixels */
		if (iW <= width - 2) {
			/* load y u v, and expand */
			iu = *((mlib_u8 *)pu);
			pu = (__m128i *) (((mlib_u8 *)pu) + 1);
			iv = *((mlib_u8 *)pv);
			pv = (__m128i *) (((mlib_u8 *)pv) + 1);
			iTemp = *((mlib_s16 *)py);
			temp = _mm_cvtsi32_si128(iTemp);
			sy1 = _mm_unpacklo_epi8(x_zero, temp);
			py = (__m128i *) (((mlib_s16 *)py) + 1);

			/* pre-calc d[r/g/b][1] */
			iu0 = (iu * ic1) >> 8;
			ib = icoff0 + iu0;

			iu1 = (iu * ic4) >> 8;
			iv1 = (iv * ic5) >> 8;
			iTemp = iu1 + iv1;
			ig = icoff1 - iTemp;

			iv2 = (iv * ic8) >> 8;
			ir = iv2 + icoff2;

			ddy1 = _mm_mulhi_epu16(sy1, c0);

			/* db1 */
			temp = _mm_set1_epi16(ib);
			db1 = _mm_add_epi16(ddy1, temp);

			/* dg1 */
			temp = _mm_set1_epi16(ig);
			dg1 = _mm_add_epi16(ddy1, temp);

			/* dr1 */
			temp = _mm_set1_epi16(ir);
			dr1 = _mm_add_epi16(ddy1, temp);

			db1 = _mm_srai_epi16(db1, 5);
			dg1 = _mm_srai_epi16(dg1, 5);
			dr1 = _mm_srai_epi16(dr1, 5);

			/* pack: 16=>8 */
			db1 = _mm_packus_epi16(db1, x_zero);
			dr1 = _mm_packus_epi16(dr1, x_zero);
			dg1 = _mm_packus_epi16(dg1, x_zero);

			/* create rgb sequences : db/dr/dg */
			dzrl = _mm_unpacklo_epi8(x_zero, dr1);
			dgbl = _mm_unpacklo_epi8(dg1, db1);

			/* lower half of drgl & dbzl */
			drgbl = _mm_unpacklo_epi16(dzrl, dgbl);
			ptemp = (mlib_u8*)(&drgbl);
			pdd += 1;
			ptemp += 1;
			*((mlib_s16*)pdd) = *((mlib_s16*)ptemp);
			pdd += 2;
			ptemp += 2;
			*((mlib_u8*)pdd) = *((mlib_u8*)ptemp);
			pdd += 2;
			ptemp += 2;
			*((mlib_s16*)pdd) = *((mlib_s16*)ptemp);
			pdd += 2;
			ptemp += 2;
			*((mlib_u8*)pdd) = *((mlib_u8*)ptemp);
			pdd += 1;

			iW += 2;
		}

		pY += y_stride;
		pU += uv_stride;
		pV += uv_stride;
		pD += argb_stride;
	}