unsigned int luma_sse2(const uint8_t *pSrc, intptr_t nSrcPitch) {
    __m128i sum = zeroes;

    for (unsigned y = 0; y < height; y++) {
        for (unsigned x = 0; x < width; x += 16) {
            __m128i src;
            if (width == 4)
                src = _mm_cvtsi32_si128(*(const int *)pSrc);
            else if (width == 8)
                src = _mm_loadl_epi64((const __m128i *)pSrc);
            else
                src = _mm_loadu_si128((const __m128i *)&pSrc[x]);

            sum = _mm_add_epi64(sum, _mm_sad_epu8(src, zeroes));
        }

        pSrc += nSrcPitch;
    }

    if (width >= 16)
        sum = _mm_add_epi64(sum, _mm_srli_si128(sum, 8));

    return (unsigned)_mm_cvtsi128_si32(sum);
}