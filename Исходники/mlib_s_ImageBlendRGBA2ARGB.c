mlib_status
__mlib_ImageBlendRGBA2ARGB(
    mlib_image *dst,
    const mlib_image *src)
{
	mlib_type type;
	mlib_u8 *sl, *dl;
	mlib_s32 slb, dlb, nchan, width, height;
	mlib_s32 i, j, ii, off;
	P_TYPE *sp, *dp;
	P_TYPE ss, aa, ds, dd, d_h, d_l;
	P_TYPE mzero, const255, mask64, d_half;

	MLIB_IMAGE_CHECK(dst);
	MLIB_IMAGE_CHECK(src);
	MLIB_IMAGE_FULL_EQUAL(dst, src);

	MLIB_IMAGE_GET_ALL_PARAMS(dst, type, nchan, width, height, dlb, dl);
	slb = mlib_ImageGetStride(src);
	sl = mlib_ImageGetData(src);

	if (type != MLIB_BYTE || nchan != 4) {
		return (MLIB_FAILURE);
	}

	mzero = _mm_setzero_si128();
	const255 = _mm_set1_epi32(0x00ff00ff);
	mask64 = _mm_set1_epi32(0xffffff00);
	d_half = _mm_set1_epi32(0x00800080);

	for (j = 0; j < height; j++) {
		P_TYPE alp, a0, a1, ralp, s0, s1, d0, d1, drnd;
		mlib_m128 s0u, s1u;

		sp = (void *)sl;
		dp = (void *)dl;

		if (!(((mlib_s32)sp | (mlib_s32)dp) & 15)) {
			for (i = 0; i < (width / 4); i++) {
				ss = _mm_load_si128(sp);
				dd = _mm_load_si128(dp);

				s0 = _mm_unpacklo_epi8(ss, mzero);
				a0 = _mm_shufflelo_epi16(s0, 0xff);
				a0 = _mm_shufflehi_epi16(a0, 0xff);
				s0 = _mm_shufflelo_epi16(s0, 0x93);
				s0 = _mm_shufflehi_epi16(s0, 0x93);
				BLEND(d_h, a0, s0, _mm_unpacklo_epi8(dd,
				    mzero));
				s1 = _mm_unpackhi_epi8(ss, mzero);
				a1 = _mm_shufflelo_epi16(s1, 0xff);
				a1 = _mm_shufflehi_epi16(a1, 0xff);
				s1 = _mm_shufflelo_epi16(s1, 0x93);
				s1 = _mm_shufflehi_epi16(s1, 0x93);
				BLEND(d_l, a1, s1, _mm_unpackhi_epi8(dd,
				    mzero));

				d_h = _mm_packus_epi16(d_h, d_l);
				d_h = _mm_or_si128(_mm_and_si128(mask64, d_h),
				    _mm_andnot_si128(mask64, dd));

				_mm_store_si128(dp, d_h);

				sp++;
				dp++;
			}
		} else {
			for (i = 0; i < (width / 4); i++) {
#if 0
				ss = _mm_loadu_si128(sp);
				s0 = _mm_unpacklo_epi8(ss, mzero);
				s1 = _mm_unpackhi_epi8(ss, mzero);
#else
				s0u.m128d = _mm_load_sd((mlib_d64 *)sp);
				s1u.m128d = _mm_load_sd((mlib_d64 *)sp + 1);
				s0 = _mm_unpacklo_epi8(s0u.m128i, mzero);
				s1 = _mm_unpacklo_epi8(s1u.m128i, mzero);
#endif
				dd = _mm_loadu_si128(dp);

				a0 = _mm_shufflelo_epi16(s0, 0xff);
				a0 = _mm_shufflehi_epi16(a0, 0xff);
				s0 = _mm_shufflelo_epi16(s0, 0x93);
				s0 = _mm_shufflehi_epi16(s0, 0x93);
				BLEND(d_h, a0, s0, _mm_unpacklo_epi8(dd,
				    mzero));
				a1 = _mm_shufflelo_epi16(s1, 0xff);
				a1 = _mm_shufflehi_epi16(a1, 0xff);
				s1 = _mm_shufflelo_epi16(s1, 0x93);
				s1 = _mm_shufflehi_epi16(s1, 0x93);
				BLEND(d_l, a1, s1, _mm_unpackhi_epi8(dd,
				    mzero));

				d_h = _mm_packus_epi16(d_h, d_l);
				d_h = _mm_or_si128(_mm_and_si128(mask64, d_h),
				    _mm_andnot_si128(mask64, dd));
#if 1
				_mm_storeu_si128(dp, d_h);
#else
				s0u.m128i = d_h;
				s1u.m128i = _mm_shuffle_epi32(d_h, 0x3e);
				_mm_store_sd((mlib_d64 *)dp, s0u.m128d);
				_mm_store_sd((mlib_d64 *)dp + 1, s1u.m128d);
#endif

				sp++;
				dp++;
			}
		}

		if (width & 3) {
			s0u.m128d = _mm_load_sd((mlib_d64 *)sp);
			s1u.m128d = _mm_load_sd((mlib_d64 *)sp + 1);
			s0 = _mm_unpacklo_epi8(s0u.m128i, mzero);
			s1 = _mm_unpacklo_epi8(s1u.m128i, mzero);
			dd = _mm_loadu_si128(dp);

			a0 = _mm_shufflelo_epi16(s0, 0xff);
			a0 = _mm_shufflehi_epi16(a0, 0xff);
			s0 = _mm_shufflelo_epi16(s0, 0x93);
			s0 = _mm_shufflehi_epi16(s0, 0x93);
			BLEND(d_h, a0, s0, _mm_unpacklo_epi8(dd, mzero));
			a1 = _mm_shufflelo_epi16(s1, 0xff);
			a1 = _mm_shufflehi_epi16(a1, 0xff);
			s1 = _mm_shufflelo_epi16(s1, 0x93);
			s1 = _mm_shufflehi_epi16(s1, 0x93);
			BLEND(d_l, a1, s1, _mm_unpackhi_epi8(dd, mzero));

			d_h = _mm_packus_epi16(d_h, d_l);
			d_h = _mm_or_si128(_mm_and_si128(mask64, d_h),
			    _mm_andnot_si128(mask64, dd));

			for (ii = 0; ii < (width & 3); ii++) {
				((mlib_s32 *)dp)[ii] = ((mlib_s32 *)&d_h)[ii];
			}
		}

		sl += slb;
		dl += dlb;
	}

	return (MLIB_SUCCESS);
}