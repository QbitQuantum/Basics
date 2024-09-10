void
mlib_FIR_tap1f_d64(
    mlib_d64 *pdst,
    const mlib_d64 *psrc,
    mlib_d64 *pflt,
    mlib_s32 n)
{
	mlib_s32 j;
	mlib_d64 dflt1 = pflt[0];
	__m128d sdflt1;
	__m128d ssrc1;
	__m128d smul1;

	j = 0;
	if ((mlib_addr)psrc & 15) {
		pdst[0] = dflt1 * psrc[0];
		psrc++;
		pdst++;
		j++;
	}

	sdflt1 = _mm_set1_pd(dflt1);

#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
	for (; j < (n - 1); j += 2) {
		ssrc1 = _mm_load_pd(psrc);
		smul1 = _mm_mul_pd(sdflt1, ssrc1);
		_mm_storeu_pd(pdst, smul1);
		psrc += 2;
		pdst += 2;
	}

	for (; j < n; j++) {
		pdst[0] = dflt1 * psrc[0];
		psrc++;
		pdst++;
	}
}