mlib_status
__mlib_ImageColorOrderedDitherMxN(
    mlib_image *dst,
    const mlib_image *src,
    const mlib_s32 **dmask,
    mlib_s32 m,
    mlib_s32 n,
    mlib_s32 scale,
    const void *colormap)
{
	mlib_type stype, dtype;
	const mlib_s32 *dmask0, *dmask1, *dmask2, *dmask3;
	mlib_u8 *sl, *dl;
	mlib_s32 nchan, dchan, sll, dll, sw, sh, dw, dh, num_blk;
	mlib_s32 off, mstep, line_size, kern_size, dsize, i, j, k, fun_ind;
	__m128i *pbuff, *pb;
	mlib_s32 *p_dim;
	mlib_u8 *kern, *pkern;
	__m128i *dkern;
	__m128i ss, d0, d1;
	__m128i k0, k1;
	mlib_s32 step0, step1, step2, step3;
	mlib_d64 srange, dscale, dscale0, dscale1, dscale2, dscale3;
	mlib_s32 half_step0, half_step1, half_step2, half_step3;
	mlib_s32 v0, v1, v2, v3;
	__m128i _s_zero = _mm_xor_si128(_s_zero, _s_zero);
	line_func_type line_func;

	MLIB_IMAGE_CHECK(src);
	MLIB_IMAGE_CHECK(dst);
	MLIB_IMAGE_SIZE_EQUAL(src, dst);
	MLIB_IMAGE_HAVE_CHAN(dst, 1);
	MLIB_IMAGE_AND_COLORMAP_ARE_COMPAT(src, colormap);

	MLIB_IMAGE_GET_ALL_PARAMS(dst, dtype, dchan, dw, dh, dll, dl);
	MLIB_IMAGE_GET_ALL_PARAMS(src, stype, nchan, sw, sh, sll, sl);

	if (stype == MLIB_BYTE && nchan == 1 && dtype == MLIB_BIT) {
		return mlib_ImageColorOrderedDitherBit_MxN(dst, src, dmask, m,
		    n, scale, colormap);
	}

	if (!(stype == MLIB_BYTE || stype == MLIB_SHORT)) {
		return (MLIB_FAILURE);
	}

	if (!(dtype == MLIB_BYTE || dtype == MLIB_SHORT)) {
		return (MLIB_FAILURE);
	}

	if (!(nchan >= 3 && nchan <= 4)) {
		return (MLIB_FAILURE);
	}

	if (dmask == NULL || colormap == NULL) {
		return (MLIB_NULLPOINTER);
	}

	if (scale <= 0) {
		return (MLIB_OUTOFRANGE);
	}

	fun_ind = nchan - 3;

	if (dtype == MLIB_SHORT)
		fun_ind += 2;
	if (stype == MLIB_SHORT)
		fun_ind += 4;
	line_func = line_func_arr[fun_ind];

	num_blk = (sw + (m - 1)) / m;
	mstep = m * nchan;

	GET_STEPS;

	if (stype == MLIB_BYTE) {
		FILL_KERN(mlib_s16);
		dsize = (nchan * sw + 15) / 16;
	} else {
		FILL_KERN(mlib_s32);
		dsize = (nchan * sw + 7) / 8;
	}

	pbuff = __mlib_malloc(dsize * sizeof (__m128i));

	if (pbuff == NULL) {
		__mlib_free(kern);
		return (MLIB_FAILURE);
	}

	pkern = kern;

#ifdef  __SUNPRO_C
#pragma pipeloop(0)
#endif
	for (j = 0; j < sh; j++) {
		dkern = (__m128i *)pkern;

		__m128i *sp = (__m128i *)sl;
		pb = pbuff;

		if (stype == MLIB_BYTE) {
#ifdef  __SUNPRO_C
#pragma pipeloop(0)
#endif
			for (i = 0; i < dsize; i++) {
				ss = _mm_loadu_si128(sp);
				sp++;
				k0 = _mm_loadu_si128(dkern);
				dkern++;
				k1 = _mm_loadu_si128(dkern);
				dkern++;
				d0 = _mm_unpacklo_epi8(ss, _s_zero);
				d1 = _mm_unpackhi_epi8(ss, _s_zero);
				d0 = _mm_add_epi16(d0, k0);
				d1 = _mm_add_epi16(d1, k1);
				d1 = _mm_packus_epi16(d0, d1);
				_mm_storeu_si128(pb, d1);
				pb++;
			}

		} else {
#ifdef  __SUNPRO_C
#pragma pipeloop(0)
#endif
			for (i = 0; i < dsize; i++) {
				ss = _mm_loadu_si128(sp);
				sp++;
				k0 = _mm_loadu_si128(dkern);
				dkern++;
				k1 = _mm_loadu_si128(dkern);
				dkern++;
				d0 = _mm_srai_epi32(
					_mm_unpacklo_epi16(_s_zero, ss), 16);
				d1 = _mm_srai_epi32(
					_mm_unpackhi_epi16(_s_zero, ss), 16);
				d0 = _mm_add_epi32(d0, k0);
				d1 = _mm_add_epi32(d1, k1);
				d1 = _mm_packs_epi32(d0, d1);
				_mm_storeu_si128(pb, d1);
				pb++;
			}
		}

		pkern += line_size;

		if (pkern >= kern + kern_size)
			pkern = kern;

		line_func(pbuff, dl, sw, colormap);

		sl += sll;
		dl += dll;
	}

	__mlib_free(pbuff);
	__mlib_free(kern);

	return (MLIB_SUCCESS);
}