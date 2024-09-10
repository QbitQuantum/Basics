float 
nv_vector_norm(const nv_matrix_t *vec, int vec_m)
{
#if NV_ENABLE_AVX
	{
		NV_ALIGNED(float, mm[8], 32);
		__m256 x, u;
		int n;
		int pk_lp = (vec->n & 0xfffffff8);
		float dp = 0.0f;
		
		u = _mm256_setzero_ps();
		for (n = 0; n < pk_lp; n += 8) {
			x = _mm256_load_ps(&NV_MAT_V(vec, vec_m, n));
			u = _mm256_add_ps(u, _mm256_mul_ps(x, x));
		}
		_mm256_store_ps(mm, u);
		dp = mm[0] + mm[1] + mm[2] + mm[3] + mm[4] + mm[5] + mm[6] + mm[7];
		for (n = pk_lp; n < vec->n; ++n) {
			dp += NV_MAT_V(vec, vec_m, n) * NV_MAT_V(vec, vec_m, n);
		}
		if (dp > 0.0f) {
			return sqrtf(dp);
		}
		return 0.0f;
	}
#elif NV_ENABLE_SSE2
	{
		NV_ALIGNED(float, mm[4], 16);
		__m128 x, u;
		int n;
		int pk_lp = (vec->n & 0xfffffffc);
		float dp = 0.0f;
		
		u = _mm_setzero_ps();
		for (n = 0; n < pk_lp; n += 4) {
			x = _mm_load_ps(&NV_MAT_V(vec, vec_m, n));
			u = _mm_add_ps(u, _mm_mul_ps(x, x));
		}
		_mm_store_ps(mm, u);
		dp = mm[0] + mm[1] + mm[2] + mm[3];
		for (n = pk_lp; n < vec->n; ++n) {
			dp += NV_MAT_V(vec, vec_m, n) * NV_MAT_V(vec, vec_m, n);
		}
		if (dp > 0.0f) {
			return sqrtf(dp);
		}
		return 0.0f;
	}
#else
	{
		int n;
		float dp = 0.0f;
		for (n = 0; n < vec->n; ++n) {
			dp += NV_MAT_V(vec, vec_m, n) * NV_MAT_V(vec, vec_m, n);
		}
		if (dp > 0.0f) {
			return sqrtf(dp);
		}
		return 0.0f;
	}
#endif
}