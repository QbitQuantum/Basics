void minmax_vec2(const uint32_t n, float const* buf, uint32_t* idx_min_, uint32_t* idx_max_, float* min_, float* max_)
{
	// We suppose that pointers are aligned on an 16-byte boundary
	
	// Initialise SSE registers
	__m128i sse_idx_min = _mm_setzero_si128();
	__m128i sse_idx_max = _mm_setzero_si128();
	__m128 sse_min = _mm_set1_ps(FLT_MAX);
	__m128 sse_max = _mm_set1_ps(FLT_MIN);

	// We will unroll the for-loop by for, thus doing
	// (n/4) iterations.
	const uint32_t n_sse = n & ~3ULL;

	__m128i sse_idx = _mm_set_epi32(3, 2, 1, 0);
	const __m128i sse_4 = _mm_set1_epi32(4);

	for (uint32_t i = 0; i < n_sse; i += 4) {
		const __m128 sse_v = _mm_load_ps(&buf[i]);
		const __m128 sse_cmp_min = _mm_cmplt_ps(sse_v, sse_min);
		const __m128 sse_cmp_max = _mm_cmpgt_ps(sse_v, sse_max);

		sse_min = _mm_blendv_ps(sse_min, sse_v, sse_cmp_min);
		sse_max = _mm_blendv_ps(sse_max, sse_v, sse_cmp_max);

		sse_idx_min = (__m128i) _mm_blendv_ps((__m128) sse_idx_min, (__m128) sse_idx, (__m128) sse_cmp_min); 
		sse_idx_max = (__m128i) _mm_blendv_ps((__m128) sse_idx_max, (__m128) sse_idx, (__m128) sse_cmp_max); 

		sse_idx = _mm_add_epi32(sse_idx, sse_4);
	}

	// SSE reduction
	__m128 sse_min_permute = _mm_shuffle_epi32(sse_min, 2 | (3<<2));
	__m128 sse_max_permute = _mm_shuffle_epi32(sse_max, 2 | (3<<2));
	__m128i sse_idx_min_permute = _mm_shuffle_epi32(sse_idx_min, 2 | (3<<2));
	__m128i sse_idx_max_permute = _mm_shuffle_epi32(sse_idx_max, 2 | (3<<2));

	__m128 sse_cmp_min = _mm_cmplt_ps(sse_min_permute, sse_min);
	__m128 sse_cmp_max = _mm_cmpgt_ps(sse_max_permute, sse_max);
	sse_min = _mm_blendv_ps(sse_min, sse_min_permute, sse_cmp_min);
	sse_max = _mm_blendv_ps(sse_max, sse_max_permute, sse_cmp_max);
	sse_idx_min = (__m128i) _mm_blendv_ps((__m128) sse_idx_min, (__m128) sse_idx_min_permute, (__m128) sse_cmp_min); 
	sse_idx_max = (__m128i) _mm_blendv_ps((__m128) sse_idx_max, (__m128) sse_idx_max_permute, (__m128) sse_cmp_max); 

	sse_min_permute = _mm_shuffle_epi32(sse_min, 1);
	sse_max_permute = _mm_shuffle_epi32(sse_max, 1);
	sse_idx_min_permute = _mm_shuffle_epi32(sse_idx_min, 1);
	sse_idx_max_permute = _mm_shuffle_epi32(sse_idx_max, 1);

	sse_cmp_min = _mm_cmplt_ps(sse_min_permute, sse_min);
	sse_cmp_max = _mm_cmpgt_ps(sse_max_permute, sse_max);
	sse_min = _mm_blendv_ps(sse_min, sse_min_permute, sse_cmp_min);
	sse_max = _mm_blendv_ps(sse_max, sse_max_permute, sse_cmp_max);
	sse_idx_min = (__m128i) _mm_blendv_ps((__m128) sse_idx_min, (__m128) sse_idx_min_permute, (__m128) sse_cmp_min); 
	sse_idx_max = (__m128i) _mm_blendv_ps((__m128) sse_idx_max, (__m128) sse_idx_max_permute, (__m128) sse_cmp_max); 

	// Epilogue
	float min, max;
	uint32_t idx_min, idx_max;
	_mm_store_ss(&min, sse_min);
	_mm_store_ss(&max, sse_max);
	idx_min = _mm_extract_epi32(sse_idx_min, 0);
	idx_max = _mm_extract_epi32(sse_idx_max, 0);

	for (uint32_t i = n_sse; i < n; i++) {
		const float v = buf[i];
		if (v < min) {
			min = v;
			idx_min = i;
		}
		if (v > max) {
			max = v;
			idx_max = i;
		}
	}

	*idx_min_ = idx_min;
	*min_ = min;
	*idx_max_ = idx_max;
	*max_ = max;
}