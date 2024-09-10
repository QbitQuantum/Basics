int normHamming(const uchar* a, const uchar* b, int n)
{
    CV_AVX_GUARD;

    int i = 0;
    int result = 0;
#if CV_AVX2
    {
        __m256i _r0 = _mm256_setzero_si256();
        __m256i _0 = _mm256_setzero_si256();
        __m256i _popcnt_table = _mm256_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
                                                 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
        __m256i _popcnt_mask = _mm256_set1_epi8(0x0F);

        for(; i <= n - 32; i+= 32)
        {
            __m256i _a0 = _mm256_loadu_si256((const __m256i*)(a + i));
            __m256i _b0 = _mm256_loadu_si256((const __m256i*)(b + i));

            __m256i _xor = _mm256_xor_si256(_a0, _b0);

            __m256i _popc0 = _mm256_shuffle_epi8(_popcnt_table, _mm256_and_si256(_xor, _popcnt_mask));
            __m256i _popc1 = _mm256_shuffle_epi8(_popcnt_table,
                             _mm256_and_si256(_mm256_srli_epi16(_xor, 4), _popcnt_mask));

            _r0 = _mm256_add_epi32(_r0, _mm256_sad_epu8(_0, _mm256_add_epi8(_popc0, _popc1)));
        }
        _r0 = _mm256_add_epi32(_r0, _mm256_shuffle_epi32(_r0, 2));
        result = _mm256_extract_epi32_(_mm256_add_epi32(_r0, _mm256_permute2x128_si256(_r0, _r0, 1)), 0);
    }
#endif // CV_AVX2

#if CV_POPCNT
    {
#  if defined CV_POPCNT_U64
        for(; i <= n - 8; i += 8)
        {
            result += (int)CV_POPCNT_U64(*(uint64*)(a + i) ^ *(uint64*)(b + i));
        }
#  endif
        for(; i <= n - 4; i += 4)
        {
            result += CV_POPCNT_U32(*(uint*)(a + i) ^ *(uint*)(b + i));
        }
    }
#endif // CV_POPCNT

#if CV_SIMD128
    {
        v_uint32x4 t = v_setzero_u32();
        for(; i <= n - v_uint8x16::nlanes; i += v_uint8x16::nlanes)
        {
            t += v_popcount(v_load(a + i) ^ v_load(b + i));
        }
        result += v_reduce_sum(t);
    }
#endif // CV_SIMD128
#if CV_ENABLE_UNROLLED
    for(; i <= n - 4; i += 4)
    {
        result += popCountTable[a[i] ^ b[i]] + popCountTable[a[i+1] ^ b[i+1]] +
                popCountTable[a[i+2] ^ b[i+2]] + popCountTable[a[i+3] ^ b[i+3]];
    }
#endif
    for(; i < n; i++)
    {
        result += popCountTable[a[i] ^ b[i]];
    }
    return result;
}