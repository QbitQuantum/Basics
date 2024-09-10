void
mlib_s_ImageScalarBlend_s32(
	mlib_s32 *dst,
	mlib_s32 dlb,
	const mlib_s32 *src1,
	mlib_s32 slb1,
	const mlib_s32 *src2,
	mlib_s32 slb2,
	const mlib_s32 *alpha,
	mlib_s32 xsize,
	mlib_s32 ysize,
	mlib_s32 nchan)
{
	mlib_s32 i, j, nsize;
	__m128i *srcPtr1, *srcPtr2, *dstPtr;
	mlib_s32 *dl = dst;
	mlib_s32 *sl1 = (mlib_s32 *)src1, *sl2 = (mlib_s32 *)src2;
	__m128d alphas0, alphas1, alphau0, alphau1, alphav0, alphav1;
	__m128d betas0, betas1, betau0, betau1, betav0, betav1;
	__m128d ones = _mm_set1_pd(1.0f);
	mlib_s32 res, sdata1, sdata2;
	mlib_d64 a0, a1, a2, a3;



	nsize = xsize * nchan;

	switch (nchan) {
	case 1:
		a0 = -(alpha[0] & MASK) / (mlib_d64)MLIB_S32_MIN;
		alphas0 = _mm_set1_pd(a0);
		alphas1 = _mm_set1_pd(a0);
		betas0  = _mm_sub_pd(ones, alphas0);
		betas1  = _mm_sub_pd(ones, alphas1);
		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src1 | slb1 |
			(mlib_addr)src2 | slb2) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_IMAGESCALARBLEND_S32(
						_mm_store_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i++) {
					MLIB_C_IMAGESCALARBLEND_S32_1(
						sl1, sl2, dl);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		} else
		if ((((mlib_addr)src1 | slb1 |
			(mlib_addr)src2 | slb2) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_IMAGESCALARBLEND_S32(
						_mm_storeu_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i++) {
					MLIB_C_IMAGESCALARBLEND_S32_1(
						sl1, sl2, dl);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_IMAGESCALARBLEND_S32(
						_mm_storeu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128);
				}
				for (; i < nsize; i++) {
					MLIB_C_IMAGESCALARBLEND_S32_1(
						sl1, sl2, dl);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		}
		break;
	case 2:
		a0 = -(alpha[0] & MASK) / (mlib_d64)MLIB_S32_MIN;
		a1 = -(alpha[1] & MASK) / (mlib_d64)MLIB_S32_MIN;
		alphas0 = _mm_set_pd(a1, a0);
		alphas1 = _mm_set_pd(a1, a0);
		betas0  = _mm_sub_pd(ones, alphas0);
		betas1  = _mm_sub_pd(ones, alphas1);

		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src1 | slb1 |
			(mlib_addr)src2 | slb2) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_IMAGESCALARBLEND_S32(
						_mm_store_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i += 2) {
					MLIB_C_IMAGESCALARBLEND_S32_2(
						sl1, sl2, dl);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		} else
		if ((((mlib_addr)src1 | slb1 |
			(mlib_addr)src2 | slb2) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_IMAGESCALARBLEND_S32(
						_mm_storeu_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i += 2) {
					MLIB_C_IMAGESCALARBLEND_S32_2(
						sl1, sl2, dl);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_IMAGESCALARBLEND_S32(
						_mm_storeu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128);
				}
				for (; i < nsize; i += 2) {
					MLIB_C_IMAGESCALARBLEND_S32_2(
						sl1, sl2, dl);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		}
		break;
	case 3:
		a0 = -(alpha[0] & MASK) / (mlib_d64)MLIB_S32_MIN;
		a1 = -(alpha[1] & MASK) / (mlib_d64)MLIB_S32_MIN;
		a2 = -(alpha[2] & MASK) / (mlib_d64)MLIB_S32_MIN;
		alphas0 = _mm_set_pd(a1, a0);
		alphas1 = _mm_set_pd(a0, a2);
		alphau0 = _mm_set_pd(a2, a1);
		alphau1 = _mm_set_pd(a1, a0);
		alphav0 = _mm_set_pd(a0, a2);
		alphav1 = _mm_set_pd(a2, a1);
		betas0  = _mm_sub_pd(ones, alphas0);
		betas1  = _mm_sub_pd(ones, alphas1);
		betau0  = _mm_sub_pd(ones, alphau0);
		betau1  = _mm_sub_pd(ones, alphau1);
		betav0  = _mm_sub_pd(ones, alphav0);
		betav1  = _mm_sub_pd(ones, alphav1);

		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src1 | slb1 |
			(mlib_addr)src2 | slb2) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 12); i += 12) {
					MLIB_S_IMAGESCALARBLEND3_S32(
						_mm_store_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i += 3) {
					MLIB_C_IMAGESCALARBLEND_S32_3(
						sl1, sl2, dl);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		} else
		if ((((mlib_addr)src1 | slb1 |
			(mlib_addr)src2 | slb2) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 12); i += 12) {
					MLIB_S_IMAGESCALARBLEND3_S32(
						_mm_storeu_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i += 3) {
					MLIB_C_IMAGESCALARBLEND_S32_3(
						sl1, sl2, dl);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 12); i += 12) {
					MLIB_S_IMAGESCALARBLEND3_S32(
						_mm_storeu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128);
				}
				for (; i < nsize; i += 3) {
					MLIB_C_IMAGESCALARBLEND_S32_3(
						sl1, sl2, dl);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		}
		break;

	case 4:
		a0 = -(alpha[0] & MASK) / (mlib_d64)MLIB_S32_MIN;
		a1 = -(alpha[1] & MASK) / (mlib_d64)MLIB_S32_MIN;
		a2 = -(alpha[2] & MASK) / (mlib_d64)MLIB_S32_MIN;
		a3 = -(alpha[3] & MASK) / (mlib_d64)MLIB_S32_MIN;
		alphas0 = _mm_set_pd(a1, a0);
		alphas1 = _mm_set_pd(a3, a2);
		betas0  = _mm_sub_pd(ones, alphas0);
		betas1  = _mm_sub_pd(ones, alphas1);

		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src1 | slb1 |
			(mlib_addr)src2 | slb2) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_IMAGESCALARBLEND_S32(
						_mm_store_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		} else
		if ((((mlib_addr)src1 | slb1 |
			(mlib_addr)src2 | slb2) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_IMAGESCALARBLEND_S32(
						_mm_storeu_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
				srcPtr1 = (__m128i *)sl1;
				srcPtr2 = (__m128i *)sl2;
				dstPtr = (__m128i *)dl;
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_IMAGESCALARBLEND_S32(
						_mm_storeu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128);
				}
				sl1 = (mlib_s32 *)((mlib_u8 *)sl1 + slb1);
				sl2 = (mlib_s32 *)((mlib_u8 *)sl2 + slb2);
				dl = (mlib_s32 *)((mlib_u8 *)dl + dlb);
			}
		}
		break;
	}
}