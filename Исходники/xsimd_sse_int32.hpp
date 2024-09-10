        inline void store_aligned_int32(__m128i src, uint16_t* dst)
        {
#if XSIMD_X86_INSTR_SET >= XSIMD_X86_SSE4_1_VERSION
            __m128i tmp = _mm_packus_epi32(src, src);
            _mm_storel_epi64((__m128i*)dst, tmp);
#else
            alignas(16) int32_t tmp[4];
            _mm_store_si128((__m128i*)tmp, src);
            unroller<4>([&](std::size_t i){
                dst[i] = static_cast<uint16_t>(tmp[i]);
            });
#endif
        }