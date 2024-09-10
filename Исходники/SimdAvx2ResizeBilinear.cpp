        template <> SIMD_INLINE void InterpolateX<3>(const __m256i * alpha, __m256i * buffer)
        {
            __m256i src[3], shuffled;
            src[0] = _mm256_load_si256(buffer + 0);
            src[1] = _mm256_load_si256(buffer + 1);
            src[2] = _mm256_load_si256(buffer + 2);

            shuffled = _mm256_shuffle_epi8(_mm256_permute2x128_si256(src[0], src[0], 0x21), K8_SHUFFLE_X3_00);
            shuffled = _mm256_or_si256(shuffled, _mm256_shuffle_epi8(src[0], K8_SHUFFLE_X3_01));
            shuffled = _mm256_or_si256(shuffled, _mm256_shuffle_epi8(_mm256_permute2x128_si256(src[0], src[1], 0x21), K8_SHUFFLE_X3_02));
            _mm256_store_si256(buffer + 0, _mm256_maddubs_epi16(shuffled, _mm256_load_si256(alpha + 0)));

            shuffled = _mm256_shuffle_epi8(_mm256_permute2x128_si256(src[0], src[1], 0x21), K8_SHUFFLE_X3_10);
            shuffled = _mm256_or_si256(shuffled, _mm256_shuffle_epi8(src[1], K8_SHUFFLE_X3_11));
            shuffled = _mm256_or_si256(shuffled, _mm256_shuffle_epi8(_mm256_permute2x128_si256(src[1], src[2], 0x21), K8_SHUFFLE_X3_12));
            _mm256_store_si256(buffer + 1, _mm256_maddubs_epi16(shuffled, _mm256_load_si256(alpha + 1)));

            shuffled = _mm256_shuffle_epi8(_mm256_permute2x128_si256(src[1], src[2], 0x21), K8_SHUFFLE_X3_20);
            shuffled = _mm256_or_si256(shuffled, _mm256_shuffle_epi8(src[2], K8_SHUFFLE_X3_21));
            shuffled = _mm256_or_si256(shuffled, _mm256_shuffle_epi8(_mm256_permute2x128_si256(src[2], src[2], 0x21), K8_SHUFFLE_X3_22));
            _mm256_store_si256(buffer + 2, _mm256_maddubs_epi16(shuffled, _mm256_load_si256(alpha + 2)));
        }        