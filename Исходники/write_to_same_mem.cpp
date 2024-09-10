void elem_mul (float *result, float *a, float *b, int dim) {
	#ifdef __linux
	int residual = dim % SIMD_WIDTH;
	int stopSIMD = dim - residual;

	__m256 vec_a, vec_b, vec_res;
	for (int i=0; i<stopSIMD; i+=SIMD_WIDTH) {
		vec_a = _mm256_loadu_ps(a + i);
		vec_b = _mm256_loadu_ps(b + i);
		vec_res = _mm256_loadu_ps(result + i);

		vec_a = _mm256_mul_ps(vec_a, vec_b);
		vec_res = _mm256_add_ps(vec_res, vec_a);
		_mm256_storeu_ps(result + i, vec_res);
	}

	for (int i=stopSIMD; i<dim; ++i) {
		result[i] += a[i] * b[i];
	}
	#endif
}