		inline float64x4_t length(const float64x4_t ymm)
		{
			float64x4_t dot0 = simd_geometric::dot(ymm, ymm);
			float64x4_t sqrt0 = _mm256_sqrt_pd(dot0);
			return sqrt0;
		}