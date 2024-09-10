void
mlib_s_ImageCopyMask_u8(
    mlib_u8 *src,
    mlib_s32 slb,
    const mlib_u8 *mask,
    mlib_s32 mlb,
    mlib_u8 *dst,
    mlib_s32 dlb,
    mlib_s32 xsize,
    mlib_s32 ysize,
    mlib_s32 nchan,
    const mlib_s32 *thresh)
{
	mlib_s32 i, j, nsize;
	mlib_s32 thresh0, thresh1, thresh2, thresh3;
	__m128i threshs, threshu, threshv, xormask;

	xormask = _mm_set1_epi8(0x80);
	nsize = xsize * nchan;
	switch (nchan) {
	case 1:
		thresh0 = thresh[0];
		threshs = _mm_set1_epi8(SAT_U8(thresh0));
		threshs = _mm_xor_si128(threshs, xormask);
		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src | slb |
			(mlib_addr)mask | mlb) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 16); i += 16) {
					MLIB_S_COPYIMAGEMASK(
						_mm_cmplt_epi8,
						_mm_store_si128,
						_mm_load_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i ++) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
				}
				src  = (mlib_u8 *)((mlib_u8 *)src + slb);
				mask = (mlib_u8 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_u8 *)((mlib_u8 *)dst + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 16); i += 16) {
					MLIB_S_COPYIMAGEMASK(
						_mm_cmplt_epi8,
						_mm_storeu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128);
				}
				for (; i < nsize; i ++) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
				}
				src  = (mlib_u8 *)((mlib_u8 *)src + slb);
				mask = (mlib_u8 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_u8 *)((mlib_u8 *)dst + dlb);
			}
		}
		break;
	case 2:
		thresh0 = thresh[0];
		thresh1 = thresh[1];
		threshs = _mm_set1_epi16((SAT_U8(thresh1) << 8) |
					(SAT_U8(thresh0) & 0xff));
		threshs = _mm_xor_si128(threshs, xormask);
		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src | slb |
			(mlib_addr)mask | mlb) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 16); i += 16) {
					MLIB_S_COPYIMAGEMASK(
						_mm_cmplt_epi8,
						_mm_store_si128,
						_mm_load_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i += 2) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
				}
				src  = (mlib_u8 *)((mlib_u8 *)src + slb);
				mask = (mlib_u8 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_u8 *)((mlib_u8 *)dst + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 16); i += 16) {
					MLIB_S_COPYIMAGEMASK(
						_mm_cmplt_epi8,
						_mm_storeu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128);
				}
				for (; i < nsize; i += 2) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
				}
				src  = (mlib_u8 *)((mlib_u8 *)src + slb);
				mask = (mlib_u8 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_u8 *)((mlib_u8 *)dst + dlb);
			}
		}
		break;
	case 3:
		thresh0 = thresh[0];
		thresh1 = thresh[1];
		thresh2 = thresh[2];
		threshs = _mm_set_epi8(SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0));
		threshu = _mm_set_epi8(SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1));
		threshv = _mm_set_epi8(SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2),
					SAT_U8(thresh1),
					SAT_U8(thresh0),
					SAT_U8(thresh2));
		threshs = _mm_xor_si128(threshs, xormask);
		threshu = _mm_xor_si128(threshu, xormask);
		threshv = _mm_xor_si128(threshv, xormask);
		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src | slb |
			(mlib_addr)mask | mlb) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 48); i += 48) {
					MLIB_S_COPYIMAGEMASK3(
						16, 32,
						_mm_cmplt_epi8,
						_mm_store_si128,
						_mm_load_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i += 3) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
					if (mask[i + 2] <= thresh2) {
						dst[i + 2] = src[i + 2];
					}
				}
				src  = (mlib_u8 *)((mlib_u8 *)src + slb);
				mask = (mlib_u8 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_u8 *)((mlib_u8 *)dst + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 48); i += 48) {
					MLIB_S_COPYIMAGEMASK3(
						16, 32,
						_mm_cmplt_epi8,
						_mm_storeu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128);
				}
				for (; i < nsize; i += 3) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
					if (mask[i + 2] <= thresh2) {
						dst[i + 2] = src[i + 2];
					}
				}
				src  = (mlib_u8 *)((mlib_u8 *)src + slb);
				mask = (mlib_u8 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_u8 *)((mlib_u8 *)dst + dlb);
			}
		}
		break;
	case 4:
		thresh0 = thresh[0];
		thresh1 = thresh[1];
		thresh2 = thresh[2];
		thresh3 = thresh[3];
		threshs = _mm_set1_epi32(((SAT_U8(thresh3) & 0xff) << 24) |
					((SAT_U8(thresh2) & 0xff) << 16) |
					((SAT_U8(thresh1) & 0xff) << 8) |
					(SAT_U8(thresh0) & 0xff));
		threshs = _mm_xor_si128(threshs, xormask);
		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src | slb |
			(mlib_addr)mask | mlb) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 16); i += 16) {
					MLIB_S_COPYIMAGEMASK(
						_mm_cmplt_epi8,
						_mm_store_si128,
						_mm_load_si128,
						_mm_load_si128,
						_mm_load_si128);
				}
				for (; i < nsize; i += 4) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
					if (mask[i + 2] <= thresh2) {
						dst[i + 2] = src[i + 2];
					}
					if (mask[i + 3] <= thresh3) {
						dst[i + 3] = src[i + 3];
					}
				}
				src  = (mlib_u8 *)((mlib_u8 *)src + slb);
				mask = (mlib_u8 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_u8 *)((mlib_u8 *)dst + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 16); i += 16) {
					MLIB_S_COPYIMAGEMASK(
						_mm_cmplt_epi8,
						_mm_storeu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128,
						_mm_loadu_si128);
				}
				for (; i < nsize; i += 4) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
					if (mask[i + 2] <= thresh2) {
						dst[i + 2] = src[i + 2];
					}
					if (mask[i + 3] <= thresh3) {
						dst[i + 3] = src[i + 3];
					}
				}
				src  = (mlib_u8 *)((mlib_u8 *)src + slb);
				mask = (mlib_u8 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_u8 *)((mlib_u8 *)dst + dlb);
			}
		}
		break;
	}
}