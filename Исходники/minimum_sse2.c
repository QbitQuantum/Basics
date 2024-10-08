static void GF_FUNC_ALIGN VS_CC
proc_16bit_sse2(uint8_t *buff, int bstride, int width, int height, int stride,
                uint8_t *d, const uint8_t *s, int th, int *enable)
{
    stride /= 2;
    bstride /= 2;
    uint16_t *dstp = (uint16_t *)d;
    const uint16_t *srcp = (uint16_t *)s;

    uint16_t *p0 = (uint16_t *)buff + 8;
    uint16_t *p1 = p0 + bstride;
    uint16_t *p2 = p1 + bstride;
    uint16_t *orig = p0, *end = p2;
    uint16_t threshold = (uint16_t)th;

    line_copy16(p0, srcp, width, 1);
    line_copy16(p1, srcp, width, 1);

    __m128i xth = _mm_set1_epi16((int16_t)threshold);

    for (int y = 0; y < height; y++) {
        srcp += stride * (y < height - 1 ? 1 : -1);
        line_copy16(p2, srcp, width, 1);
        uint16_t *coordinates[] = {p0 - 1, p0, p0 + 1,
                                   p1 - 1,     p1 + 1,
                                   p2 - 1, p2, p2 + 1};
        for (int x = 0; x < width; x += 8) {
            __m128i src = _mm_load_si128((__m128i *)(p1 + x));
            __m128i min = src;

            for (int i = 0; i < 8; i++) {
                if (enable[i]) {
                    __m128i target = _mm_loadu_si128((__m128i *)(coordinates[i] + x));
                    min = MM_MIN_EPU16(min, target);
                }
            }

            __m128i limit = _mm_subs_epu16(src, xth);
            min = MM_MAX_EPU16(min, limit);
            _mm_store_si128((__m128i *)(dstp + x), min);
        }
        dstp += stride;
        p0 = p1;
        p1 = p2;
        p2 = (p2 == end) ? orig : p2 + bstride;
    }
}