void FLAC__lpc_compute_autocorrelation_intrin_sse_lag_16_old(const FLAC__real data[], unsigned data_len, unsigned lag, FLAC__real autoc[])
{
	__m128 xmm0, xmm1, xmm2, xmm3, xmm4, xmm5, xmm6, xmm7, xmm8, xmm9;

	(void) lag;
	FLAC__ASSERT(lag > 0);
	FLAC__ASSERT(lag <= 16);
	FLAC__ASSERT(lag <= data_len);
	FLAC__ASSERT(data_len > 0);

	xmm6 = _mm_setzero_ps();
	xmm7 = _mm_setzero_ps();
	xmm8 = _mm_setzero_ps();
	xmm9 = _mm_setzero_ps();

	xmm0 = _mm_load_ss(data++);
	xmm2 = xmm0;
	xmm0 = _mm_shuffle_ps(xmm0, xmm0, 0);
	xmm3 = _mm_setzero_ps();
	xmm4 = _mm_setzero_ps();
	xmm5 = _mm_setzero_ps();

	xmm0 = _mm_mul_ps(xmm0, xmm2);
	xmm6 = _mm_add_ps(xmm6, xmm0);

	data_len--;

	while(data_len)
	{
		xmm0 = _mm_load1_ps(data++);

		/* shift xmm5:xmm4:xmm3:xmm2 left by one float */
		xmm5 = _mm_shuffle_ps(xmm5, xmm5, _MM_SHUFFLE(2,1,0,3));
		xmm4 = _mm_shuffle_ps(xmm4, xmm4, _MM_SHUFFLE(2,1,0,3));
		xmm3 = _mm_shuffle_ps(xmm3, xmm3, _MM_SHUFFLE(2,1,0,3));
		xmm2 = _mm_shuffle_ps(xmm2, xmm2, _MM_SHUFFLE(2,1,0,3));
		xmm5 = _mm_move_ss(xmm5, xmm4);
		xmm4 = _mm_move_ss(xmm4, xmm3);
		xmm3 = _mm_move_ss(xmm3, xmm2);
		xmm2 = _mm_move_ss(xmm2, xmm0);

		/* xmm9|xmm8|xmm7|xmm6 += xmm0|xmm0|xmm0|xmm0 * xmm5|xmm4|xmm3|xmm2 */
		xmm1 = xmm0;
		xmm1 = _mm_mul_ps(xmm1, xmm5);
		xmm9 = _mm_add_ps(xmm9, xmm1);
		xmm1 = xmm0;
		xmm1 = _mm_mul_ps(xmm1, xmm4);
		xmm8 = _mm_add_ps(xmm8, xmm1);
		xmm1 = xmm0;
		xmm1 = _mm_mul_ps(xmm1, xmm3);
		xmm7 = _mm_add_ps(xmm7, xmm1);
		xmm0 = _mm_mul_ps(xmm0, xmm2);
		xmm6 = _mm_add_ps(xmm6, xmm0);

		data_len--;
	}

	_mm_storeu_ps(autoc,   xmm6);
	_mm_storeu_ps(autoc+4, xmm7);
	_mm_storeu_ps(autoc+8, xmm8);
	_mm_storeu_ps(autoc+12,xmm9);
}