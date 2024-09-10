static void
mlib_ImageCopyMask_Fp_d64(
    const mlib_d64 *src,
    mlib_s32 slb,
    const mlib_d64 *mask,
    mlib_s32 mlb,
    mlib_d64 *dst,
    mlib_s32 dlb,
    mlib_s32 xsize,
    mlib_s32 ysize,
    mlib_s32 nchan,
    const mlib_d64 *thresh)
{
	mlib_s32 i, j, nsize;
	mlib_d64 thresh0, thresh1, thresh2, thresh3;
	__m128d threshs, threshu, threshv;

	nsize = xsize * nchan;
	switch (nchan) {
	case 1:
		thresh0 = thresh[0];
		threshs = _mm_set1_pd(thresh0);
		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src | slb |
			(mlib_addr)mask | mlb) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 2); i += 2) {
					MLIB_S_COPYIMAGEMASK_D64(
						_mm_store_pd,
						_mm_load_pd,
						_mm_load_pd,
						_mm_load_pd);
				}
				for (; i < nsize; i ++) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
				}
				src  = (mlib_d64 *)((mlib_u8 *)src + slb);
				mask = (mlib_d64 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_d64 *)((mlib_u8 *)dst + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 2); i += 2) {
					MLIB_S_COPYIMAGEMASK_D64(
						_mm_storeu_pd,
						_mm_loadu_pd,
						_mm_loadu_pd,
						_mm_loadu_pd);
				}
				for (; i < nsize; i ++) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
				}
				src  = (mlib_d64 *)((mlib_u8 *)src + slb);
				mask = (mlib_d64 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_d64 *)((mlib_u8 *)dst + dlb);
			}
		}
		break;
	case 2:
		thresh0 = thresh[0];
		thresh1 = thresh[1];
		threshs = _mm_set_pd(thresh1, thresh0);
		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src | slb |
			(mlib_addr)mask | mlb) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 2); i += 2) {
					MLIB_S_COPYIMAGEMASK_D64(
						_mm_store_pd,
						_mm_load_pd,
						_mm_load_pd,
						_mm_load_pd);
				}
				for (; i < nsize; i += 2) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
				}
				src  = (mlib_d64 *)((mlib_u8 *)src + slb);
				mask = (mlib_d64 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_d64 *)((mlib_u8 *)dst + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 2); i += 2) {
					MLIB_S_COPYIMAGEMASK_D64(
						_mm_storeu_pd,
						_mm_loadu_pd,
						_mm_loadu_pd,
						_mm_loadu_pd);
				}
				for (; i < nsize; i += 2) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
				}
				src  = (mlib_d64 *)((mlib_u8 *)src + slb);
				mask = (mlib_d64 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_d64 *)((mlib_u8 *)dst + dlb);
			}
		}
		break;
	case 3:
		thresh0 = thresh[0];
		thresh1 = thresh[1];
		thresh2 = thresh[2];
		threshs = _mm_set_pd(thresh1, thresh0);
		threshu = _mm_set_pd(thresh0, thresh2);
		threshv = _mm_set_pd(thresh2, thresh1);
		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src | slb |
			(mlib_addr)mask | mlb) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 6); i += 6) {
					MLIB_S_COPYIMAGEMASK3_D64(
						_mm_store_pd,
						_mm_load_pd,
						_mm_load_pd,
						_mm_load_pd);
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
				src  = (mlib_d64 *)((mlib_u8 *)src + slb);
				mask = (mlib_d64 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_d64 *)((mlib_u8 *)dst + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 6); i += 6) {
					MLIB_S_COPYIMAGEMASK3_D64(
						_mm_storeu_pd,
						_mm_loadu_pd,
						_mm_loadu_pd,
						_mm_loadu_pd);
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
				src  = (mlib_d64 *)((mlib_u8 *)src + slb);
				mask = (mlib_d64 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_d64 *)((mlib_u8 *)dst + dlb);
			}
		}
		break;
	case 4:
		thresh0 = thresh[0];
		thresh1 = thresh[1];
		thresh2 = thresh[2];
		thresh3 = thresh[3];
		threshs = _mm_set_pd(thresh1, thresh0);
		threshu = _mm_set_pd(thresh3, thresh2);
		if ((((mlib_addr)dst | dlb |
			(mlib_addr)src | slb |
			(mlib_addr)mask | mlb) & 0xf) == 0) {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_COPYIMAGEMASK4_D64(
						_mm_store_pd,
						_mm_load_pd,
						_mm_load_pd,
						_mm_load_pd);
				}
				for (; i < nsize; i += 4) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
					if (mask[i + 2] <= thresh2) {
						dst[i + 1] = src[i + 2];
					}
					if (mask[i + 3] <= thresh3) {
						dst[i + 1] = src[i + 3];
					}
				}
				src  = (mlib_d64 *)((mlib_u8 *)src + slb);
				mask = (mlib_d64 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_d64 *)((mlib_u8 *)dst + dlb);
			}
		} else {
			for (j = 0; j < ysize; j ++) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i <= (nsize - 4); i += 4) {
					MLIB_S_COPYIMAGEMASK4_D64(
						_mm_storeu_pd,
						_mm_loadu_pd,
						_mm_loadu_pd,
						_mm_loadu_pd);
				}
				for (; i < nsize; i += 4) {
					if (mask[i] <= thresh0) {
						dst[i] = src[i];
					}
					if (mask[i + 1] <= thresh1) {
						dst[i + 1] = src[i + 1];
					}
					if (mask[i + 2] <= thresh2) {
						dst[i + 1] = src[i + 2];
					}
					if (mask[i + 3] <= thresh3) {
						dst[i + 1] = src[i + 3];
					}
				}
				src  = (mlib_d64 *)((mlib_u8 *)src + slb);
				mask = (mlib_d64 *)((mlib_u8 *)mask + mlb);
				dst  = (mlib_d64 *)((mlib_u8 *)dst + dlb);
			}
		}
		break;
	}
}