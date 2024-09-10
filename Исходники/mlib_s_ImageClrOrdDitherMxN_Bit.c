mlib_status FUNC(
    MxN) (
    mlib_image *dst,
    const mlib_image *src,
    const mlib_s32 **dmask,
    mlib_s32 m,
    mlib_s32 n,
    mlib_s32 scale,
    const void *colormap)
{
	mlib_type stype, dtype;
	const mlib_s32 *dmask0 = dmask[0], *dmask1 = dmask[1], *dmask2 =
	    dmask[2];
	mlib_s32 method = mlib_ImageGetMethod(colormap);
	mlib_u8 *sl, *dl;
	mlib_s32 schan, dchan, sll, dll, sw, sh, dw, dh, num_blk;
	mlib_s32 off, off1, kw, mstep, line_size, kern_size, xsize16, i, j, k;
	__m128i *pbuff, *pb;
	mlib_u8 *p_dim;
	mlib_s16 *kern, *pkern;
	__m128i *dkern;
	mlib_d64 dscale, dscale0, dscale1, dscale2;
	__m128i ss, d0, d1, k0, k1;
	__m128i _s_zero = _mm_xor_si128(_s_zero, _s_zero);
	mlib_s32 step0, half_step0, v0;
	mlib_s32 bit_offset = mlib_ImageGetBitOffset(dst);
	mlib_u8 *p_lut;

	MLIB_IMAGE_GET_ALL_PARAMS(dst, dtype, dchan, dw, dh, dll, dl);
	MLIB_IMAGE_GET_ALL_PARAMS(src, stype, schan, sw, sh, sll, sl);

	p_lut = (mlib_u8 *)mlib_ImageGetLutInversTable(colormap);
	step0 = abs(p_lut[1] - p_lut[0]);

	num_blk = (sw + (m - 1)) / m;
	mstep = m * NCHAN;
	line_size = (mstep * num_blk + 15) & ~15;
	xsize16 = (NCHAN * sw + 15) / 16;

	dscale = 1.0;
	while (scale > 30) {
		dscale *= 1.0 / (1 << 30);
		scale -= 30;
	}

	dscale /= (1 << scale);

	dscale0 = dscale * step0;
	half_step0 = (step0 - 1) >> 1;

	kern_size = n * line_size;
	kern = __mlib_malloc(kern_size * sizeof (mlib_s16));

	if (kern == NULL)
		return (MLIB_FAILURE);

	for (j = 0; j < n; j++) {
		for (i = 0; i < m; i++) {
			pkern = kern + j * line_size + i;
			v0 = half_step0 - (mlib_s32)(dmask0[j * m +
			    i] * dscale0);
			for (k = 0; k < num_blk; k++) {
				pkern[k * mstep] = v0;
			}
		}
	}

	pbuff = __mlib_malloc(xsize16 * sizeof (__m128i) + 16);

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

#ifdef  __SUNPRO_C
#pragma pipeloop(0)
#endif
		for (i = 0; i < xsize16; i++) {
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

		pkern += line_size;

		if (pkern >= kern + kern_size)
			pkern = kern;

		mlib_ImageColorTrue2IndexLine_U8_BIT_1((mlib_u8 *)pbuff, dl,
		    bit_offset, sw, colormap);

		sl += sll;
		dl += dll;
	}

	__mlib_free(pbuff);
	__mlib_free(kern);

	return (MLIB_SUCCESS);
}