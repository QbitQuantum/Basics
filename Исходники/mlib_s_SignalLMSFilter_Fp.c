mlib_status
__mlib_SignalLMSFilter_F32S_F32S(
    mlib_f32 *dst,
    const mlib_f32 *src,
    const mlib_f32 *ref,
    void *filter,
    mlib_s32 n)
{
	LMS_Filter *pLMS_Filter = (LMS_Filter *) filter;
	mlib_d64 *W[2], *srcBuffer[2];
	mlib_d64 U = pLMS_Filter->U;
	mlib_d64 D, Y;
	mlib_s32 i, t, j, off, count;
	mlib_s32 tap, bufferSize;
	mlib_f32 *psrc, *pdst, *pref;

	__m128d srcs1, srcs2, srcs3, srcs4;
	__m128d SBE0, SD, temp;
	__m128d *SW;

	if (src == NULL || dst == NULL || ref == NULL)
		return (MLIB_NULLPOINTER);

	if (n <= 0)
		return (MLIB_FAILURE);

	tap = pLMS_Filter->tap;
	bufferSize = pLMS_Filter->bufferSize;

	SW = __mlib_malloc(tap * sizeof (__m128d));

	W[0] = pLMS_Filter->data;
	srcBuffer[0] = (W[0] + 2 * tap);
	W[1] = srcBuffer[0] + 2 * bufferSize;
	srcBuffer[1] = (W[1] + 2 * tap);

	psrc = (mlib_f32 *)src;
	pdst = (mlib_f32 *)dst;
	pref = (mlib_f32 *)ref;

	for (off = 0; off < n; off += count) {

		count = n - off;
		if (count > bufferSize) {
			count = bufferSize;
		}

		for (i = 0; i < count; i++) {
			srcBuffer[0][i] = (mlib_d64)psrc[2 * i];
			srcBuffer[1][i] = (mlib_d64)psrc[2 * i + 1];
		}

		for (j = 0; j < 2; j++) {
			mlib_d64 *psrcBuffer = srcBuffer[j];
			mlib_d64 *pW = W[j];
			mlib_d64 BE0 = pLMS_Filter->BE[j];

			for (i = 0; i < (tap / 2); i++) {
				SW[i] = _mm_set_pd(pW[i * 2], pW[i * 2 + 1]);
			}

			for (t = 0; t < count; t++) {
				D = 0;
				Y = pref[2 * t + j];
				SBE0 = _mm_set1_pd(BE0);
				SD = _mm_setzero_pd();
#ifdef __SUNPRO_C
#pragma pipeloop(0)
#endif /* __SUNPRO_C */
				for (i = 0; i < (tap / 2); i++) {
					srcs1 = _mm_loadu_pd(
					    psrcBuffer + t - i * 2 - 2);
					srcs2 = _mm_loadu_pd(
					    psrcBuffer + t - i * 2 - 1);

					temp = _mm_mul_pd(SBE0, srcs1);
					SW[i] = _mm_add_pd(SW[i], temp);
					SD = _mm_add_pd(SD,
					    _mm_mul_pd(srcs2, SW[i]));
				}

				mlib_d64 TD[2];
				_mm_storeu_pd(TD, SD);
				D += TD[0] + TD[1];

				for (i = i * 2; i < tap; i++) {
					pW[i] += BE0 * psrcBuffer[t - i - 1];
					D += psrcBuffer[t - i] * pW[i];
				}

				BE0 = (Y - D) * U;

				pdst[2 * t + j] = (mlib_f32)D;
			}

			mlib_d64 TW[2];
			for (i = 0; i < (tap / 2); i++) {
				_mm_storeu_pd(TW, SW[i]);
				pW[i * 2] = TW[1];
				pW[i * 2 + 1] = TW[0];
			}

			for (i = 0; i < tap; i++) {
				psrcBuffer[i - tap] =
				    psrcBuffer[count + (i - tap)];
			}

			pLMS_Filter->BE[j] = BE0;
		}

		psrc += 2 * count;
		pdst += 2 * count;
		pref += 2 * count;
	}

	__mlib_free(SW);
	return (MLIB_SUCCESS);
}