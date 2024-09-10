		inline float64x4_t mat4_mul_vec4(const float64x4_t ymm[4], const float64x4_t ymm_v)
		{
			float64x4_t perm0 = _mm256_permute_pd(ymm_v, 0x0); // x x y y
			float64x4_t perm1 = _mm256_permute_pd(ymm_v, 0xF); // z z w w

			float64x4_t bcast0 = _mm256_broadcast_pd(&_mm256_extractf128_pd(perm0, 0)); // x x x x 
			float64x4_t bcast1 = _mm256_broadcast_pd(&_mm256_extractf128_pd(perm0, 1)); // y y y y
			float64x4_t bcast2 = _mm256_broadcast_pd(&_mm256_extractf128_pd(perm1, 0)); // z z z z
			float64x4_t bcast3 = _mm256_broadcast_pd(&_mm256_extractf128_pd(perm1, 1)); // w w w w

			float64x4_t mul0 = _mm256_mul_pd(ymm[0], bcast0);
			float64x4_t mul1 = _mm256_mul_pd(ymm[1], bcast1);
			float64x4_t mul2 = _mm256_mul_pd(ymm[2], bcast2);
			float64x4_t mul3 = _mm256_mul_pd(ymm[3], bcast3);

			float64x4_t add0 = _mm256_add_pd(mul0, mul1);
			float64x4_t add1 = _mm256_add_pd(mul2, mul3);
			float64x4_t add2 = _mm256_add_pd(add0, add1);

			return add2;
		}