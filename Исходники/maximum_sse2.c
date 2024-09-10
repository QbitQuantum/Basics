static void GF_FUNC_ALIGN VS_CC
proc_8bit_sse2(uint8_t *buff, int bstride, int width, int height, int stride,
               uint8_t *dstp, const uint8_t *srcp, int th, int *enable)
{
    uint8_t *p0 = buff + 16;
    uint8_t *p1 = p0 + bstride;
    uint8_t *p2 = p1 + bstride;
    uint8_t *orig = p0, *end = p2;
    uint8_t threshold = th > 255 ? 255 : (uint8_t)th;

    line_copy8(p0, srcp + stride, width, 1);
    line_copy8(p1, srcp, width, 1);

    __m128i xth = _mm_set1_epi8((int8_t)threshold);

    for (int y = 0; y < height; y++) {
        srcp += stride * (y < height - 1 ? 1 : -1);
        line_copy8(p2, srcp, width, 1);

        for (int x = 0; x < width; x += 16) {
            uint8_t *coordinates[] = COORDINATES;

            __m128i src = _mm_load_si128((__m128i *)(p1 + x));
            __m128i max = src;
            
            for (int i = 0; i < 8; i++) {
                if (enable[i]) {
                    __m128i target = _mm_loadu_si128((__m128i *)coordinates[i]);
                    max = _mm_max_epu8(target, max);
                }
            }
            
            __m128i limit = _mm_adds_epu8(src, xth);
            max = _mm_min_epu8(max, limit);
            _mm_store_si128((__m128i *)(dstp + x), max);
        }
        dstp += stride;
        p0 = p1;
        p1 = p2;
        p2 = (p2 == end) ? orig : p2 + bstride;
    }
}