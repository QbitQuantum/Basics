void FastResampler_FirFilter2_C2_SSE2(unsigned int channels, unsigned int filter_length, float* coef1, float* coef2, float frac, float* input, float* output) {
	Q_UNUSED(channels);
	__m128 sum = _mm_setzero_ps();
	__m128 v_frac = _mm_set1_ps(frac);
	for(unsigned int i = 0; i < filter_length / 4; ++i) {
		__m128 v_coef1 = _mm_load_ps(coef1), v_coef2 = _mm_load_ps(coef2);
		coef1 += 4; coef2 += 4;
		__m128 filter_value = _mm_add_ps(v_coef1, _mm_mul_ps(_mm_sub_ps(v_coef2, v_coef1), v_frac));
		__m128 v_input1 = _mm_loadu_ps(input), v_input2 = _mm_loadu_ps(input + 4);
		input += 8;
		sum = _mm_add_ps(sum, _mm_mul_ps(v_input1, _mm_unpacklo_ps(filter_value, filter_value)));
		sum = _mm_add_ps(sum, _mm_mul_ps(v_input2, _mm_unpackhi_ps(filter_value, filter_value)));
	}
	__m128 sum2 = _mm_add_ps(sum, _mm_shuffle_ps(sum, sum, 0xee));
	_mm_store_sd((double*) output, _mm_castps_pd(sum2));
}