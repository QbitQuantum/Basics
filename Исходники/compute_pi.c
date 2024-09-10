double compute_pi_leibniz_fma(size_t n)
{
	double pi = 0.0;
	register __m256d ymm0, ymm1, ymm2, ymm3, ymm4;

	ymm0 = _mm256_setzero_pd();
	ymm1 = _mm256_set1_pd(2.0);
	ymm2 = _mm256_set1_pd(1.0);
	ymm3 = _mm256_set_pd(1.0, -1.0, 1.0, -1.0);
	
	for (int i = 0; i <= n - 4; i += 4) {
		ymm4 = _mm256_set_pd(i, i + 1.0, i + 2.0, i + 3.0);
		ymm4 = _mm256_fmadd_pd(ymm1, ymm4, ymm2);
		ymm4 = _mm256_div_pd(ymm3, ymm4);
		ymm0 = _mm256_add_pd(ymm0, ymm4);
	}
	double tmp[4] __attribute__((aligned(32)));
	_mm256_store_pd(tmp, ymm0);
	pi += tmp[0] + tmp[1] + tmp[2] + tmp[3];

	return pi * 4.0;
}