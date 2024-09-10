void sigm_deriv (float *deriv_res, float *sigm_res, int dim) {
	#ifdef __APPLE__
		for (int i=0; i<dim; i++) {
			deriv_res[i] = sigm_res[i] * (1 - sigm_res[i]);
		} 
	#elif __linux
		int residual = dim % SIMD_WIDTH;
		int stopSIMD = dim - residual;

		__m256 vec_deriv, vec_sigm;
		__m256 vec_one  = _mm256_set1_ps(1.f);
		for (int i=0; i<stopSIMD; i+=SIMD_WIDTH) {
			vec_sigm  = _mm256_loadu_ps(sigm_res + i);
			
			vec_deriv = _mm256_mul_ps(vec_sigm, _mm256_sub_ps(vec_one, vec_sigm));
			_mm256_storeu_ps(deriv_res + i, vec_deriv);
		}

		for (int i=stopSIMD; i<dim; ++i) {
			deriv_res[i] = sigm_res[i] * (1 - sigm_res[i]);
		}
	#endif
}