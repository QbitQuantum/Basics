unsigned int vp9_get8x8var_sse2(const uint8_t *src, int src_stride,
                                const uint8_t *ref, int ref_stride,
                                unsigned int *sse, int *sum) {
    const __m128i zero = _mm_setzero_si128();
    __m128i vsum = _mm_setzero_si128();
    __m128i vsse = _mm_setzero_si128();
    int i;

    for (i = 0; i < 8; i += 2) {
        const __m128i src0 = _mm_unpacklo_epi8(_mm_loadl_epi64(
                (const __m128i *)(src + i * src_stride)), zero);
        const __m128i ref0 = _mm_unpacklo_epi8(_mm_loadl_epi64(
                (const __m128i *)(ref + i * ref_stride)), zero);
        const __m128i diff0 = _mm_sub_epi16(src0, ref0);

        const __m128i src1 = _mm_unpacklo_epi8(_mm_loadl_epi64(
                (const __m128i *)(src + (i + 1) * src_stride)), zero);
        const __m128i ref1 = _mm_unpacklo_epi8(_mm_loadl_epi64(
                (const __m128i *)(ref + (i + 1) * ref_stride)), zero);
        const __m128i diff1 = _mm_sub_epi16(src1, ref1);

        vsum = _mm_add_epi16(vsum, diff0);
        vsum = _mm_add_epi16(vsum, diff1);
        vsse = _mm_add_epi32(vsse, _mm_madd_epi16(diff0, diff0));
        vsse = _mm_add_epi32(vsse, _mm_madd_epi16(diff1, diff1));
    }

    // sum
    vsum = _mm_add_epi16(vsum, _mm_srli_si128(vsum, 8));
    vsum = _mm_add_epi16(vsum, _mm_srli_si128(vsum, 4));
    vsum = _mm_add_epi16(vsum, _mm_srli_si128(vsum, 2));
    *sum = (int16_t)_mm_extract_epi16(vsum, 0);

    // sse
    vsse = _mm_add_epi32(vsse, _mm_srli_si128(vsse, 8));
    vsse = _mm_add_epi32(vsse, _mm_srli_si128(vsse, 4));
    *sse = _mm_cvtsi128_si32(vsse);

    return 0;
}