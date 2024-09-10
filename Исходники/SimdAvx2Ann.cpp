		template <bool inversion, bool align> void Convert(const uint8_t * src, const __m256 &_1_255, float * dst)
		{
			__m128i _src = Invert<inversion>(_mm_loadl_epi64((__m128i*)src));
			Avx::Store<align>(dst, _mm256_mul_ps(_mm256_cvtepi32_ps(_mm256_cvtepu8_epi32(_src)), _1_255));
		}