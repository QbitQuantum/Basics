mlib_status
mlib_VectorConjSymExt_S32C_S32C_Sat_N(
	mlib_s32 *zz,
	const mlib_s32 *xx,
	mlib_s32 n,
	mlib_s32 n1)
{
	CHECK;

	const mlib_s32 *px = xx;
	mlib_s32 *pz = zz;
	mlib_s32 *pd = zz + n1 + n1;

	mlib_s32 i, ax, az, n2, n3, nstep, c, c0, c1;
	__m128i xbuf, zbuf, mask1, mask2, mask3;
	mask1 = _mm_setr_epi32(0, 0xffffffff, 0, 0xffffffff);
	mask2 = _mm_setr_epi32(0, 0x80000000, 0, 0x80000000);

	ax = (mlib_addr)px & 15;
	az = (mlib_addr)pz & 15;
	nstep = 16 / sizeof (mlib_s32);

	if (ax & 7) {
		for (i = 0; i < n / 2; i++) {
			CONJ_S32C(loadu, storeu);
		}
		for (i = 0; i < n % 2; i++) {
			CONJ(S32);
		}
	} else {
		n1 = ((16 - ax) & 15) / sizeof (mlib_s32);
		n2 = (n + n - n1) / nstep;
		n3 = n + n - n1 - n2 * nstep;

		if (n2 < 1) {
			for (i = 0; i < n; i++) {
				CONJ(S32);
			}
		} else {
			for (i = 0; i < n1 / 2; i++) {
				CONJ(S32);
			}

			if (ax == az) {
				for (i = 0; i < n2; i++) {
					CONJ_S32C(loadu, storeu);
				}
			} else {
				for (i = 0; i < n2; i++) {
					CONJ_S32C(loadu, storeu);
				}
			}
			for (i = 0; i < n3 / 2; i++) {
				CONJ(S32);
			}
		}
	}

	return (MLIB_SUCCESS);
}