mlib_status
__mlib_VectorDotProd_U8_Sat(
	mlib_d64 *z,
	const mlib_u8 *x,
	const mlib_u8 *y,
	mlib_s32 n)
{
	if (n <= 0)
		return (MLIB_FAILURE);

	mlib_s32 i, ax, ay, nstep, n1, n2, n3, sum = 0;
	const mlib_u8 *px = x, *py = y;
	__m128i zero, xbuf, ybuf, zbuf32, zbuf64, buf1, buf2, buf3, buf4;
	zero = _mm_setzero_si128();
	zbuf64 = zero;

	ax = (mlib_addr)x & 15;
	ay = (mlib_addr)y & 15;
	nstep = 16 / sizeof (mlib_u8);
	n1 = ((16 - ax) & 15) / sizeof (mlib_u8);
	n2 = (n - n1) / nstep;
	n3 = n - n1 - n2 * nstep;

	if (n2 > 0) {
		for (i = 0; i < n1; i++) {
			sum += (mlib_s32)(*px++) * (*py++);
		}

		mlib_s32 nblock = n2 >> 12;
		mlib_s32 tail = n2 & 4095;
		mlib_s32 k;

		if (ax == ay) {
			for (k = 0; k < nblock; k++) {
				zbuf32 = zero;
				for (i = 0; i < 4096; i++) {
					VECTOR_DOTPROD_U8(load);
				}
				buf1 = _mm_unpacklo_epi32(zbuf32, zero);
				buf2 = _mm_unpackhi_epi32(zbuf32, zero);
				zbuf64 = _mm_add_epi64(zbuf64, buf1);
				zbuf64 = _mm_add_epi64(zbuf64, buf2);
			}
			zbuf32 = zero;
			for (i = 0; i < tail; i++) {
				VECTOR_DOTPROD_U8(load);
			}
		} else {
			for (k = 0; k < nblock; k++) {
				zbuf32 = zero;
				for (i = 0; i < 4096; i++) {
					VECTOR_DOTPROD_U8(loadu);
				}
				buf1 = _mm_unpacklo_epi32(zbuf32, zero);
				buf2 = _mm_unpackhi_epi32(zbuf32, zero);
				zbuf64 = _mm_add_epi64(zbuf64, buf1);
				zbuf64 = _mm_add_epi64(zbuf64, buf2);
			}
			zbuf32 = zero;
			for (i = 0; i < tail; i++) {
				VECTOR_DOTPROD_U8(loadu);
			}
		}
		buf1 = _mm_unpacklo_epi32(zbuf32, zero);
		buf2 = _mm_unpackhi_epi32(zbuf32, zero);
		zbuf64 = _mm_add_epi64(zbuf64, buf1);
		zbuf64 = _mm_add_epi64(zbuf64, buf2);

		for (i = 0; i < n3; i++) {
			sum += (mlib_s32)(*px++) * (*py++);
		}

		mlib_d64 dsum = sum;
		long long pz[2];
		_mm_storeu_si128((__m128i *)pz, zbuf64);
		dsum += pz[0];
		dsum += pz[1];
		*z = dsum;
	} else {
		for (i = 0; i < n; i++) {