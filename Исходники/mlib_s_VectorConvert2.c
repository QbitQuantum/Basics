mlib_status
__mlib_VectorConvert_S16_S32_Mod(
	mlib_s16 *z,
	const mlib_s32 *x,
	mlib_s32 n)
{
	if (n < 1)
		return (MLIB_FAILURE);

	mlib_s32 i, ax, az, nstep, n1, n2, n3;
	mlib_s32 *px = (mlib_s32 *)x;
	mlib_s16 *pz = (mlib_s16 *)z;
	__m128i zbuf, xlo, xhi, mask;

	ax = (mlib_addr)x & 15;
	az = (mlib_addr)z & 15;

	nstep = 16 / sizeof (mlib_s16);
	n1 = ((16 - ax) & 15) / sizeof (mlib_s32);
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

		for (i = 0; i < n2; i++) {
			xlo = _mm_load_si128((__m128i *)px);
			xhi = _mm_load_si128((__m128i *)px + 1);
			xlo = _mm_slli_epi32(xlo, 16);
			xhi = _mm_slli_epi32(xhi, 16);
			xlo = _mm_srai_epi32(xlo, 16);
			xhi = _mm_srai_epi32(xhi, 16);
			zbuf = _mm_packs_epi32(xlo, xhi);
			_mm_storeu_si128((__m128i *)pz, zbuf);
			px += nstep;
			pz += nstep;
		}

		for (i = 0; i < n3; i++) {
			*pz++ = *px++;
		}
	}

	return (MLIB_SUCCESS);
}