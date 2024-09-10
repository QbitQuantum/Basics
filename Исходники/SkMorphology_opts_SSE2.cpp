static void SkMorph_SSE2(const SkPMColor* src, SkPMColor* dst, int radius,
                         int width, int height, int srcStride, int dstStride)
{
    const int srcStrideX = direction == kX ? 1 : srcStride;
    const int dstStrideX = direction == kX ? 1 : dstStride;
    const int srcStrideY = direction == kX ? srcStride : 1;
    const int dstStrideY = direction == kX ? dstStride : 1;
    radius = SkMin32(radius, width - 1);
    const SkPMColor* upperSrc = src + radius * srcStrideX;
    for (int x = 0; x < width; ++x) {
        const SkPMColor* lp = src;
        const SkPMColor* up = upperSrc;
        SkPMColor* dptr = dst;
        for (int y = 0; y < height; ++y) {
            __m128i max = type == kDilate ? _mm_setzero_si128() : _mm_set1_epi32(0xFFFFFFFF);
            for (const SkPMColor* p = lp; p <= up; p += srcStrideX) {
                __m128i src_pixel = _mm_cvtsi32_si128(*p);
                max = type == kDilate ? _mm_max_epu8(src_pixel, max) : _mm_min_epu8(src_pixel, max);
            }
            *dptr = _mm_cvtsi128_si32(max);
            dptr += dstStrideY;
            lp += srcStrideY;
            up += srcStrideY;
        }
        if (x >= radius) {
            src += srcStrideX;
        }
        if (x + radius < width - 1) {
            upperSrc += srcStrideX;
        }
        dst += dstStrideX;
    }
}