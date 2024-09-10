mlib_status
__mlib_VectorConvert_S8_U8_Sat(
	mlib_s8 *z,
	const mlib_u8 *x,
	mlib_s32 n)
{
	if (n < 1)
		return (MLIB_FAILURE);

	mlib_s32 i, ax, az, nstep, n1, n2, n3, xval;
	mlib_u8 *px = (mlib_u8 *)x;
	mlib_s8 *pz = (mlib_s8 *)z;
	__m128i zbuf, xbuf, mask;
	mask = _mm_set1_epi8(127);

	ax = (mlib_addr)x & 15;
	az = (mlib_addr)z & 15;

	nstep = 16 / sizeof (mlib_u8);
	n1 = ((16 - ax) & 15) / sizeof (mlib_u8);
	n2 = (n - n1) / nstep;
	n3 = n - n1 - n2 * nstep;

	if (n2 < 1) {
		for (i = 0; i < n; i++) {
			xval = *px++;
			if (xval > 127)
				xval = 127;
			*pz++ = xval;
		}
	} else {
		for (i = 0; i < n1; i++) {
			xval = *px++;
			if (xval > 127)
				xval = 127;
			*pz++ = xval;
		}

		for (i = 0; i < n2; i++) {
			xbuf = _mm_load_si128((__m128i *)px);
			zbuf = _mm_min_epu8(xbuf, mask);
			_mm_storeu_si128((__m128i *)pz, zbuf);
			px += nstep;
			pz += nstep;
		}

		for (i = 0; i < n3; i++) {
			xval = *px++;
			if (xval > 127)
				xval = 127;
			*pz++ = xval;
		}
	}

	return (MLIB_SUCCESS);
}