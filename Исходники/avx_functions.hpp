	// PRE: all vectors aligned, 
	//		imag_c = [i1,i1,...,i4,i4]
	//		vec = [v1r,v1i,...,v4r,v4i]
	//		component-wise multiplication
	// POST: returns [-i1*v1i,i1*v1r,...,-i4*v4i,i4*v4r]
	inline __m256 avx_multiply_float_imag_(const __m256& imag_c, const __m256& vec) {
		static const __m256 zero = _mm256_setzero_ps();
		__m256 vec1 = _mm256_mul_ps(imag_c,vec);
		vec1 = _mm256_permute_ps(vec1,0xB1);
		return _mm256_addsub_ps(zero,vec1);
	}