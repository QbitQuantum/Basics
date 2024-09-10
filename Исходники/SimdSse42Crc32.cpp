        SIMD_INLINE void Crc32c(size_t & crc, const size_t * p, const size_t * end)
        {
            while(p < end)
            {
#ifdef SIMD_X64_ENABLE
                crc = _mm_crc32_u64(crc, *p++);
#else
                crc = _mm_crc32_u32(crc, *p++);
#endif
            }
        }