unsigned FLAC__fixed_compute_best_predictor_intrin_ssse3(const FLAC__int32 data[], unsigned data_len, FLAC__float residual_bits_per_sample[FLAC__MAX_FIXED_ORDER + 1])
{
	FLAC__uint32 total_error_0, total_error_1, total_error_2, total_error_3, total_error_4;
	unsigned i, order;

	__m128i total_err0, total_err1, total_err2;

	{
		FLAC__int32 itmp;
		__m128i last_error;

		last_error = _mm_cvtsi32_si128(data[-1]);							// 0   0   0   le0
		itmp = data[-2];
		last_error = _mm_shuffle_epi32(last_error, _MM_SHUFFLE(2,1,0,0));
		last_error = _mm_sub_epi32(last_error, _mm_cvtsi32_si128(itmp));	// 0   0   le0 le1
		itmp -= data[-3];
		last_error = _mm_shuffle_epi32(last_error, _MM_SHUFFLE(2,1,0,0));
		last_error = _mm_sub_epi32(last_error, _mm_cvtsi32_si128(itmp));	// 0   le0 le1 le2
		itmp -= data[-3] - data[-4];
		last_error = _mm_shuffle_epi32(last_error, _MM_SHUFFLE(2,1,0,0));
		last_error = _mm_sub_epi32(last_error, _mm_cvtsi32_si128(itmp));	// le0 le1 le2 le3

		total_err0 = total_err1 = _mm_setzero_si128();
		for(i = 0; i < data_len; i++) {
			__m128i err0, err1;
			err0 = _mm_cvtsi32_si128(data[i]);								// 0   0   0   e0
			err1 = _mm_shuffle_epi32(err0, _MM_SHUFFLE(0,0,0,0));			// e0  e0  e0  e0
#if 1 /* OPT_SSE */
			err1 = _mm_sub_epi32(err1, last_error);
			last_error = _mm_srli_si128(last_error, 4);						// 0   le0 le1 le2
			err1 = _mm_sub_epi32(err1, last_error);
			last_error = _mm_srli_si128(last_error, 4);						// 0   0   le0 le1
			err1 = _mm_sub_epi32(err1, last_error);
			last_error = _mm_srli_si128(last_error, 4);						// 0   0   0   le0
			err1 = _mm_sub_epi32(err1, last_error);							// e1  e2  e3  e4
#else
			last_error = _mm_add_epi32(last_error, _mm_srli_si128(last_error, 8));	// le0  le1  le2+le0  le3+le1
			last_error = _mm_add_epi32(last_error, _mm_srli_si128(last_error, 4));	// le0  le1+le0  le2+le0+le1  le3+le1+le2+le0
			err1 = _mm_sub_epi32(err1, last_error);							// e1  e2  e3  e4
#endif
			last_error = _mm_alignr_epi8(err0, err1, 4);					// e0  e1  e2  e3

			err0 = _mm_abs_epi32(err0);
			err1 = _mm_abs_epi32(err1);

			total_err0 = _mm_add_epi32(total_err0, err0);					// 0   0   0   te0
			total_err1 = _mm_add_epi32(total_err1, err1);					// te1 te2 te3 te4
		}
	}
	
	total_error_0 = _mm_cvtsi128_si32(total_err0);
	total_err2 = total_err1;											// te1  te2  te3  te4
	total_err1 = _mm_srli_si128(total_err1, 8);							//  0    0   te1  te2
	total_error_4 = _mm_cvtsi128_si32(total_err2);
	total_error_2 = _mm_cvtsi128_si32(total_err1);
	total_err2 = _mm_srli_si128(total_err2,	4);							//  0   te1  te2  te3
	total_err1 = _mm_srli_si128(total_err1, 4);							//  0    0    0   te1
	total_error_3 = _mm_cvtsi128_si32(total_err2);
	total_error_1 = _mm_cvtsi128_si32(total_err1);

	/* prefer higher order */
	if(total_error_0 < flac_min(flac_min(flac_min(total_error_1, total_error_2), total_error_3), total_error_4))
		order = 0;
	else if(total_error_1 < flac_min(flac_min(total_error_2, total_error_3), total_error_4))
		order = 1;
	else if(total_error_2 < flac_min(total_error_3, total_error_4))
		order = 2;
	else if(total_error_3 < total_error_4)
		order = 3;
	else
		order = 4;

	/* Estimate the expected number of bits per residual signal sample. */
	/* 'total_error*' is linearly related to the variance of the residual */
	/* signal, so we use it directly to compute E(|x|) */
	FLAC__ASSERT(data_len > 0 || total_error_0 == 0);
	FLAC__ASSERT(data_len > 0 || total_error_1 == 0);
	FLAC__ASSERT(data_len > 0 || total_error_2 == 0);
	FLAC__ASSERT(data_len > 0 || total_error_3 == 0);
	FLAC__ASSERT(data_len > 0 || total_error_4 == 0);

	residual_bits_per_sample[0] = (FLAC__float)((total_error_0 > 0) ? log(M_LN2 * (FLAC__double)total_error_0 / (FLAC__double)data_len) / M_LN2 : 0.0);
	residual_bits_per_sample[1] = (FLAC__float)((total_error_1 > 0) ? log(M_LN2 * (FLAC__double)total_error_1 / (FLAC__double)data_len) / M_LN2 : 0.0);
	residual_bits_per_sample[2] = (FLAC__float)((total_error_2 > 0) ? log(M_LN2 * (FLAC__double)total_error_2 / (FLAC__double)data_len) / M_LN2 : 0.0);
	residual_bits_per_sample[3] = (FLAC__float)((total_error_3 > 0) ? log(M_LN2 * (FLAC__double)total_error_3 / (FLAC__double)data_len) / M_LN2 : 0.0);
	residual_bits_per_sample[4] = (FLAC__float)((total_error_4 > 0) ? log(M_LN2 * (FLAC__double)total_error_4 / (FLAC__double)data_len) / M_LN2 : 0.0);

	return order;
}