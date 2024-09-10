        template <bool align> SIMD_INLINE void Bgr48pToBgra32(uint8_t * bgra, 
            const uint8_t * blue, const uint8_t * green, const uint8_t * red, size_t offset, __m256i alpha)
        {
            __m256i _blue = _mm256_and_si256(LoadPermuted<align>((__m256i*)(blue + offset)), K16_00FF);
            __m256i _green = _mm256_and_si256(LoadPermuted<align>((__m256i*)(green + offset)), K16_00FF);
            __m256i _red = _mm256_and_si256(LoadPermuted<align>((__m256i*)(red + offset)), K16_00FF);

            __m256i bg = _mm256_or_si256(_blue, _mm256_slli_si256(_green, 1));
            __m256i ra = _mm256_or_si256(_red, alpha);

            Store<align>((__m256i*)bgra + 0, _mm256_unpacklo_epi16(bg, ra));
            Store<align>((__m256i*)bgra + 1, _mm256_unpackhi_epi16(bg, ra));
        }