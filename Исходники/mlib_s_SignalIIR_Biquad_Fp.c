mlib_status
__mlib_SignalIIR_Biquad_F32_F32(
    mlib_f32 *dst,
    const mlib_f32 *src,
    void *filter,
    mlib_s32 n)
{
	mlib_d64 a0, a1, a2, b1, b2, x1, x2, y1, y2, r0, x0;

	mlib_s32 i, tmp;

	__m128d sa0, sa1, sa2, sb1, sb2, sx1, sx2, sy1, sy2, sr0, sx0;
	__m128d stmp1, stmp2, stmp3, stmp4, stmp5;
	mlib_d64 tr0[2], tx0[2], tx1[2], tx2[2], ty1[2], ty2[2];

	mlib_IIR_filt_F32 *pflt = (mlib_IIR_filt_F32 *) filter;

	if (filter == NULL || src == NULL || dst == NULL)
		return (MLIB_NULLPOINTER);

	if (n <= 0)
		return (MLIB_OUTOFRANGE);

	a0 = pflt->a0;
	a1 = pflt->a1;
	a2 = pflt->a2;

	b1 = pflt->b1;
	b2 = pflt->b2;

	x1 = pflt->x1;
	x2 = pflt->x2;
	y1 = pflt->y1;
	y2 = pflt->y2;

	for (i = 0; (i < 2) && (i < n); i++) {
		x0 = src[i];

		r0 = a0 * x0 + a1 * x1 + a2 * x2 + b2 * y2 + b1 * y1;

		x2 = x1;
		x1 = x0;

		y2 = y1;
		y1 = r0;

		dst[i] = r0;
	}

	sa0 = _mm_set1_pd(pflt->a0);
	sa1 = _mm_set1_pd(pflt->a1);
	sa2 = _mm_set1_pd(pflt->a2);
	sb1 = _mm_set1_pd(pflt->b1);
	sb2 = _mm_set1_pd(pflt->b2);

	x0 = src[i];
	sx0 = _mm_setr_pd(src[i], src[i + 1]);
	sx1 = _mm_setr_pd(x1, x0);
	sx2 = _mm_setr_pd(x2, x1);
	sy1 = _mm_setr_pd(y1, 0);
	sy2 = _mm_setr_pd(y2, y1);

	for (; i < n - 1; i += 2) {

		stmp1 = _mm_mul_pd(sa0, sx0);
		stmp2 = _mm_mul_pd(sa1, sx1);
		stmp3 = _mm_mul_pd(sa2, sx2);
		stmp4 = _mm_mul_pd(sb2, sy2);
		stmp5 = _mm_mul_pd(sb1, sy1);
		stmp1 = _mm_add_pd(stmp1, stmp2);
		stmp3 = _mm_add_pd(stmp3, stmp4);
		stmp1 = _mm_add_pd(stmp1, stmp3);
		sr0 = _mm_add_pd(stmp1, stmp5);

		_mm_storeu_pd(tr0, sr0);
		tr0[1] += (b1 * tr0[0]);
		_mm_storeu_pd(tx0, sx0);

		sx2 = sx0;
		sx1 = _mm_setr_pd(tx0[1], src[i + 2]);
		sx0 = _mm_setr_pd(src[i + 2], src[i + 3]);
		sy1 = _mm_setr_pd(tr0[1], 0);
		sy2 = _mm_setr_pd(tr0[0], tr0[1]);

		dst[i] = tr0[0];
		dst[i + 1] = tr0[1];
	}

	_mm_storeu_pd(tx1, sx1);
	x1 = tx1[0];
	_mm_storeu_pd(tx2, sx2);
	x2 = tx2[0];
	_mm_storeu_pd(ty1, sy1);
	y1 = ty1[0];
	_mm_storeu_pd(ty2, sy2);
	y2 = ty2[0];

	for (; i < n; i++) {
		x0 = src[i];

		r0 = a0 * x0 + a1 * x1 + a2 * x2 + b2 * y2 + b1 * y1;

		x2 = x1;
		x1 = x0;

		y2 = y1;
		y1 = r0;

		dst[i] = r0;
	}

	pflt->x1 = x1;
	pflt->x2 = x2;

	pflt->y1 = y1;
	pflt->y2 = y2;

	return (MLIB_SUCCESS);
}