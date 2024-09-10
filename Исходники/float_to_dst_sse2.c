static void GF_FUNC_ALIGN VS_CC
float_to_dst_8bit(const float *srcp, uint8_t *dstp, int width, int height,
                  int src_stride, int dst_stride, float th, int bits)
{
    __m128 tmax = _mm_set1_ps(th);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x += 16) {
            __m128 xmf0 = _mm_cmpge_ps(_mm_load_ps(srcp + x), tmax);
            __m128 xmf1 = _mm_cmpge_ps(_mm_load_ps(srcp + x + 4), tmax);
            __m128 xmf2 = _mm_cmpge_ps(_mm_load_ps(srcp + x + 8), tmax);
            __m128 xmf3 = _mm_cmpge_ps(_mm_load_ps(srcp + x + 12), tmax);
            __m128i xmi0 = _mm_packs_epi32(_mm_castps_si128(xmf0),
                                           _mm_castps_si128(xmf1));
            __m128i xmi1 = _mm_packs_epi32(_mm_castps_si128(xmf2),
                                           _mm_castps_si128(xmf3));
            xmi0 = _mm_packs_epi16(xmi0, xmi1);
            _mm_store_si128((__m128i *)(dstp + x), xmi0);
        }
        srcp += src_stride;
        dstp += dst_stride;
    }
}