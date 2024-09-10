mlib_status
__mlib_SignalLimit_F32S_F32S(
    mlib_f32 *dst,
    const mlib_f32 *src,
    const mlib_f32 *low,
    const mlib_f32 *high,
    mlib_s32 n)
{
	mlib_s32 i, count;
	mlib_f32 tl0, tl1;
	mlib_f32 th0, th1;
	mlib_f32 x, x1;
	__m128 t_low, t_high;
	__m128 dx;
	mlib_f32 *psrc = (mlib_f32 *)src;
	mlib_f32 *pdst = (mlib_f32 *)dst;
	mlib_s32 samples = 2 * n;

	tl0 = low[0];
	th0 = high[0];
	tl1 = low[1];
	th1 = high[1];

	if ((tl0 > th0) || (tl1 > th1) || (n <= 0))
		return (MLIB_FAILURE);

	count = (16 - ((mlib_addr)psrc & 15)) >> 2;
	if (count > samples) count = samples;

	for (i = 0; i < count - 1; i += 2) {
		x = (*psrc++);
		x = (x < tl0) ? tl0 : x;
		x = (x >= th0) ? th0 : x;
		(*pdst++) = x;
		x1 = (*psrc++);
		x1 = (x1 < tl1) ? tl1 : x1;
		x1 = (x1 >= th1) ? th1 : x1;
		(*pdst++) = x1;
	}

	if (count & 1) {
		x = (*psrc++);
		x = (x < tl0) ? tl0 : x;
		x = (x >= th0) ? th0 : x;
		(*pdst++) = x;
	}

	if (count & 1) {
		t_low = _mm_setr_ps(tl1, tl0, tl1, tl0);
		t_high = _mm_setr_ps(th1, th0, th1, th0);
	} else {
		t_low = _mm_setr_ps(tl0, tl1, tl0, tl1);
		t_high = _mm_setr_ps(th0, th1, th0, th1);
	}

	samples -= count;

	if ((mlib_addr)pdst & 15) {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
		for (i = 0; i < samples >> 2; i++) {
			dx = _mm_load_ps(psrc + 4 * i);
			dx = _mm_max_ps(dx, t_low);
			dx = _mm_min_ps(dx, t_high);
			_mm_storeu_ps(pdst + 4 * i, dx);
		}
	} else {
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
		for (i = 0; i < samples >> 2; i++) {
			dx = _mm_load_ps(psrc + 4 * i);
			dx = _mm_max_ps(dx, t_low);
			dx = _mm_min_ps(dx, t_high);
			_mm_store_ps(pdst + 4 * i, dx);
		}
	}

	i <<= 2;
	psrc += i;
	pdst += i;

	if (count & 1 && i < samples) {
		x = (*psrc++);
		x = (x < tl1) ? tl1 : x;
		x = (x >= th1) ? th1 : x;
		(*pdst++) = x;

		i ++;
	}

	for (; i < samples - 1; i += 2) {
		x = (*psrc++);
		x = (x < tl0) ? tl0 : x;
		x = (x >= th0) ? th0 : x;
		(*pdst++) = x;
		x1 = (*psrc++);
		x1 = (x1 < tl1) ? tl1 : x1;
		x1 = (x1 >= th1) ? th1 : x1;
		(*pdst++) = x1;
	}

	return (MLIB_SUCCESS);
}