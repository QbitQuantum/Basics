        template <bool align> SIMD_INLINE void GrayToBgra(uint8_t * bgra, __m128i gray, __m128i alpha)
        {
            __m128i bgLo = _mm_unpacklo_epi8(gray, gray);
            __m128i bgHi = _mm_unpackhi_epi8(gray, gray);
            __m128i raLo = _mm_unpacklo_epi8(gray, alpha);
            __m128i raHi = _mm_unpackhi_epi8(gray, alpha);

            Store<align>((__m128i*)bgra + 0, _mm_unpacklo_epi16(bgLo, raLo));
            Store<align>((__m128i*)bgra + 1, _mm_unpackhi_epi16(bgLo, raLo));
            Store<align>((__m128i*)bgra + 2, _mm_unpacklo_epi16(bgHi, raHi));
            Store<align>((__m128i*)bgra + 3, _mm_unpackhi_epi16(bgHi, raHi));
        }