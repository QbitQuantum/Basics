        SIMD_INLINE __m128i SquaredDifference(__m128i a, __m128i b)
        {
            const __m128i aLo = _mm_unpacklo_epi8(a, _mm_setzero_si128());
            const __m128i bLo = _mm_unpacklo_epi8(b, _mm_setzero_si128());
            const __m128i dLo = _mm_sub_epi16(aLo, bLo);

            const __m128i aHi = _mm_unpackhi_epi8(a, _mm_setzero_si128());
            const __m128i bHi = _mm_unpackhi_epi8(b, _mm_setzero_si128());
            const __m128i dHi = _mm_sub_epi16(aHi, bHi);

            return _mm_add_epi32(_mm_madd_epi16(dLo, dLo), _mm_madd_epi16(dHi, dHi));
        }