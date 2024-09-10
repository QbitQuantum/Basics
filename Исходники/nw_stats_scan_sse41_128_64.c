static inline void arr_store_si128(
        int *array,
        __m128i vH,
        int32_t t,
        int32_t seglen,
        int32_t d,
        int32_t dlen)
{
    array[(0*seglen+t)*dlen + d] = (int64_t)_mm_extract_epi64(vH, 0);
    array[(1*seglen+t)*dlen + d] = (int64_t)_mm_extract_epi64(vH, 1);
}