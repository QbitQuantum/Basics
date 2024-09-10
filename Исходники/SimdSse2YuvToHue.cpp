		SIMD_INLINE __m128i MulDiv16(__m128i dividend, __m128i divisor, const __m128 & KF_255_DIV_6)
		{
			const __m128i quotientLo = MulDiv32(_mm_unpacklo_epi16(dividend, K_ZERO), _mm_unpacklo_epi16(divisor, K_ZERO), KF_255_DIV_6);
			const __m128i quotientHi = MulDiv32(_mm_unpackhi_epi16(dividend, K_ZERO), _mm_unpackhi_epi16(divisor, K_ZERO), KF_255_DIV_6);
			return _mm_packs_epi32(quotientLo, quotientHi);
		}