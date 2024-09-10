inline
void kernel(adouble* v1, adouble * v2, int m)
{
	__m256d alpha = _mm256_set1_pd(0.25);
	//
	__m256d phi_e = _mm256_loadu_pd (v1 + 1 );
	__m256d phi_w = _mm256_loadu_pd (v1 - 1 );
	__m256d phi_n = _mm256_loadu_pd (v1 + m);
	__m256d phi_s = _mm256_loadu_pd (v1 - m);
	//
	phi_e = _mm256_add_pd(phi_e, phi_s);
	phi_e = _mm256_add_pd(phi_e, phi_n);
	//phi_e = _mm_fmadd_pd(alpha, phi_e, phi_w);
	phi_e = _mm256_add_pd(phi_e, phi_w);
	phi_e = _mm256_mul_pd(alpha, phi_e);
	//
	//printf("-> p = %p\n", &v2[0]);
	_mm256_stream_pd(v2, phi_e);

}