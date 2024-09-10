mlib_status
__mlib_VectorConvert_S32_S16_Mod(
	mlib_s32 *z,
	const mlib_s16 *x,
	mlib_s32 n)
{
	if (n < 1)
		return (MLIB_FAILURE);

	mlib_s32 i, ax, az, nstep, n1, n2, n3;
	mlib_s16 *px = (mlib_s16 *)x;
	mlib_s32 *pz = (mlib_s32 *)z;
	__m128i xbuf, zlo, zhi, zero;
	zero = _mm_setzero_si128();

	ax = (mlib_addr)x & 15;
	az = (mlib_addr)z & 15;

	nstep = 16 / sizeof (mlib_s16);
	n1 = ((16 - ax) & 15) / sizeof (mlib_s16);
	n2 = (n - n1) / nstep;
	n3 = n - n1 - n2 * nstep;

	if (n2 < 1) {
		for (i = 0; i < n; i++) {
			*pz++ = *px++;
		}
	} else {
		for (i = 0; i < n1; i++) {
			*pz++ = *px++;
		}

		if ((ax * 2 & 15) == az) {
			for (i = 0; i < n2; i++) {
				xbuf = _mm_load_si128((__m128i *)px);
				zlo = _mm_unpacklo_epi16(zero, xbuf);
				zhi = _mm_unpackhi_epi16(zero, xbuf);
				zlo = _mm_srai_epi32(zlo, 16);
				zhi = _mm_srai_epi32(zhi, 16);
				_mm_store_si128((__m128i *)pz, zlo);
				_mm_store_si128((__m128i *)pz + 1, zhi);
				px += nstep;
				pz += nstep;
			}
		} else {
			for (i = 0; i < n2; i++) {
				xbuf = _mm_load_si128((__m128i *)px);
				zlo = _mm_unpacklo_epi16(zero, xbuf);
				zhi = _mm_unpackhi_epi16(zero, xbuf);
				zlo = _mm_srai_epi32(zlo, 16);
				zhi = _mm_srai_epi32(zhi, 16);
				_mm_storeu_si128((__m128i *)pz, zlo);
				_mm_storeu_si128((__m128i *)pz + 1, zhi);
				px += nstep;
				pz += nstep;
			}
		}

		for (i = 0; i < n3; i++) {
			*pz++ = *px++;
		}
	}

	return (MLIB_SUCCESS);
}