//! \brief
//! Performs a bitwise right shift logical by the specified count
//!
inline __m256i srli(__m256i arg, int count)
{
    __m128i arg_low = _mm256_castsi256_si128(arg);
    __m128i arg_hi = _mm256_extractf128_si256(arg, 1);

    __m128i newlow = _mm_srli_epi32(arg_low, count);
    __m128i newhi = _mm_srli_epi32(arg_hi, count);

    __m256i result = _mm256_castsi128_si256(newlow);
    result = _mm256_insertf128_si256(result, newhi, 1);
    return result;
}