static void GF_FUNC_ALIGN VS_CC
proc_8bit_sse2(uint8_t *buff, int bstride, int width, int height, int stride,
               uint8_t *dstp, const uint8_t *srcp, int th)
{
    uint8_t *p0 = buff + 16;
    uint8_t *p1 = p0 + bstride;
    uint8_t *p2 = p1 + bstride;
    uint8_t *orig = p0, *end = p2;

    line_copy8(p0, srcp + stride, width, 1);
    line_copy8(p1, srcp, width, 1);

    uint8_t threshold = (uint8_t)th;

    __m128i zero = _mm_setzero_si128();
    __m128i xth = _mm_set1_epi8((int8_t)threshold);

    for (int y = 0; y < height; y++) {
        srcp += stride * (y < height - 1 ? 1 : -1);
        line_copy8(p2, srcp, width, 1);
        uint8_t *coordinates[] = COORDINATES;
        for (int x = 0; x < width; x += 16) {
            __m128i sumlo = zero;
            __m128i sumhi = zero;

            for (int i = 0; i < 8; i++) {
                __m128i target = _mm_loadu_si128((__m128i *)(coordinates[i] + x));
                sumlo  = _mm_add_epi16(sumlo, _mm_unpacklo_epi8(target, zero));
                sumhi  = _mm_add_epi16(sumhi, _mm_unpackhi_epi8(target, zero));
            }

            sumlo = _mm_srai_epi16(sumlo, 3);
            sumhi = _mm_srai_epi16(sumhi, 3);
            sumlo = _mm_packus_epi16(sumlo, sumhi);

            __m128i src = _mm_load_si128((__m128i *)(p1 + x));
            __m128i limit = _mm_adds_epu8(src, xth);

            sumlo = _mm_max_epu8(sumlo, src);
            sumlo = _mm_min_epu8(sumlo, limit);

            _mm_store_si128((__m128i *)(dstp + x), sumlo);
        }
        dstp += stride;
        p0 = p1;
        p1 = p2;
        p2 = (p2 == end) ? orig : p2 + bstride;
    }
}