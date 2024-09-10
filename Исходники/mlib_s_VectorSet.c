mlib_status
__mlib_VectorSet_S32C(
	mlib_s32 *z,
	const mlib_s32 *c,
	mlib_s32 n)
{
	if (n < 1)
		return (MLIB_FAILURE);

	mlib_s32 i, nstep, n1, n2, n3;
	mlib_s32 c0, c1, *pdst = z;
	__m128i val;
	c0 = c[0];
	c1 = c[1];

	nstep = 16 / sizeof (mlib_s32);
	n1 = ((16 - ((mlib_addr)z & 15)) & 15) / sizeof (mlib_s32);
	n2 = (n + n - n1) / nstep;
	n3 = n + n - n1 - n2 * nstep;

	if (n2 < 1) {
		for (i = 0; i < n; i++) {
			*pdst++ = c0;
			*pdst++ = c1;
		}
	} else {
		for (i = 0; i < n1 / 2; i++) {
			*pdst++ = c0;
			*pdst++ = c1;
		}
		if (n1 & 1) {
			*pdst++ = c0;
			val = _mm_setr_epi32(c1, c0, c1, c0);
		} else {
			val = _mm_setr_epi32(c0, c1, c0, c1);
		}

		for (i = 0; i < n2; i++) {
			_mm_store_si128((__m128i *)pdst, val);
			pdst += nstep;
		}

		if (n1 & 1) {
			*pdst++ = c1;
			n3--;
		}
		for (i = 0; i < n3 / 2; i++) {
			*pdst++ = c0;
			*pdst++ = c1;
		}
		if (n3 & 1) {
			*pdst++ = c0;
		}
	}

	return (MLIB_SUCCESS);
}