void ff_hevc_transform_skip_8_sse(uint8_t *_dst, int16_t *coeffs, ptrdiff_t _stride)
{
    uint8_t *dst = (uint8_t*)_dst;
    ptrdiff_t stride = _stride;
    int shift = 5;
    int offset = 16;
    __m128i r0, r1, r2, r3, r4, r5, r6, r9;

    r9 = _mm_setzero_si128();
    r2 = _mm_set1_epi16(offset);

    r0 = _mm_load_si128((__m128i*)(coeffs));
    r1 = _mm_load_si128((__m128i*)(coeffs + 8));


    r0 = _mm_adds_epi16(r0, r2);
    r1 = _mm_adds_epi16(r1, r2);

    r0 = _mm_srai_epi16(r0, shift);
    r1 = _mm_srai_epi16(r1, shift);

    r3 = _mm_loadl_epi64((__m128i*)(dst));
    r4 = _mm_loadl_epi64((__m128i*)(dst + stride));
    r5 = _mm_loadl_epi64((__m128i*)(dst + 2 * stride));
    r6 = _mm_loadl_epi64((__m128i*)(dst + 3 * stride));

    r3 = _mm_unpacklo_epi8(r3, r9);
    r4 = _mm_unpacklo_epi8(r4, r9);
    r5 = _mm_unpacklo_epi8(r5, r9);
    r6 = _mm_unpacklo_epi8(r6, r9);
    r3 = _mm_unpacklo_epi64(r3, r4);
    r4 = _mm_unpacklo_epi64(r5, r6);


    r3 = _mm_adds_epi16(r3, r0);
    r4 = _mm_adds_epi16(r4, r1);

    r3 = _mm_packus_epi16(r3, r4);

    *((uint32_t *)(dst)) = _mm_cvtsi128_si32(r3);
    dst+=stride;
    *((uint32_t *)(dst)) = _mm_cvtsi128_si32(_mm_srli_si128(r3, 4));
    dst+=stride;
    *((uint32_t *)(dst)) = _mm_cvtsi128_si32(_mm_srli_si128(r3, 8));
    dst+=stride;
    *((uint32_t *)(dst)) = _mm_cvtsi128_si32(_mm_srli_si128(r3, 12));
}