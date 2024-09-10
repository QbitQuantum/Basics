mlib_status
mlib_ImageColorConvert2_D64(
    const mlib_d64 *src,
    mlib_s32 slb,
    mlib_d64 *dst,
    mlib_s32 dlb,
    mlib_s32 xsize,
    mlib_s32 ysize,
    const mlib_d64 *fmat,
    const mlib_d64 *offset)
{
	/* pointers for pixel and line of source */
	mlib_d64 *sa, *sl;

	/* pointers for pixel and line of destination */
	mlib_d64 *da, *dl;

	/* indices */
	mlib_s32 i, j;

	/* coeff's */
	mlib_d64 k02, k12, k22;
	mlib_d64 p0, p1, p2, q2;
	mlib_d64 off2;

	/* intermediate */
	__m128d t0, t1, t2, s0, s1, q;
	__m128d p00, p11, p22;

	/* packed kernel */
	__m128d k0, k1, k2;

	/* packed offset */
	__m128d off;

	/* load transposed kernel */
	k0 = _mm_set_pd(fmat[3], fmat[0]);
	k1 = _mm_set_pd(fmat[4], fmat[1]);
	k2 = _mm_set_pd(fmat[5], fmat[2]);

	/* load offset */
	off = _mm_set_pd(offset[1], offset[0]);

	/* keep kernel in regs */
	k02 = fmat[6];
	k12 = fmat[7];
	k22 = fmat[8];

	off2 = offset[2];

	sa = sl = (void *)src;
	da = dl = dst;

	for (j = 0; j < ysize; j++) {

#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
		for (i = 0; i < 3 * xsize; i += 3) {
			p0 = *sa;
			sa ++;
			p00 = _mm_set1_pd(p0);
			p1 = *sa;
			sa ++;
			p11 = _mm_set1_pd(p1);
			p2 = *sa;
			sa ++;
			p22 = _mm_set1_pd(p2);

			t0 = _mm_mul_pd(p00, k0);
			t1 = _mm_mul_pd(p11, k1);
			t2 = _mm_mul_pd(p22, k2);

			s0 = _mm_add_pd(t0, t1);
			s1 = _mm_add_pd(t2, off);
			q = _mm_add_pd(s0, s1);

			q2 = p0 * k02 + p1 * k12 + p2 * k22 + off2;

			_mm_storeu_pd(da, q);
			da += 2;
			*da = q2;
			da ++;
		}

		/* set src ptrs to next row */
		sl = sa = sl + slb;
		/* set dst ptrs to next row */
		dl = da = dl + dlb;
	}

	return (MLIB_SUCCESS);
}