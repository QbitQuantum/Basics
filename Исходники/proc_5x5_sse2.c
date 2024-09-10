static void GF_FUNC_ALIGN VS_CC
proc_8bit_sse2(convolution_t *ch, uint8_t *buff, int bstride, int width,
               int height, int stride, uint8_t *dstp, const uint8_t *srcp)
{
    uint8_t *p0 = buff + 16;
    uint8_t *p1 = p0 + bstride;
    uint8_t *p2 = p1 + bstride;
    uint8_t *p3 = p2 + bstride;
    uint8_t *p4 = p3 + bstride;
    uint8_t *orig = p0, *end = p4;

    line_copy8(p0, srcp + 2 * stride , width, 2);
    line_copy8(p1, srcp + stride, width, 2);
    line_copy8(p2, srcp, width, 2);
    srcp += stride;
    line_copy8(p3, srcp, width, 2);

    __m128i zero = _mm_setzero_si128();
    __m128 rdiv = _mm_set1_ps((float)ch->rdiv);
    __m128 bias = _mm_set1_ps((float)ch->bias);
    __m128i matrix[25];
    for (int i = 0; i < 25; i++) {
        matrix[i] = _mm_unpacklo_epi16(_mm_set1_epi16((int16_t)ch->m[i]), zero);
    }

    for (int y = 0; y < height; y++) {
        srcp += stride * (y < height - 2 ? 1 : -1);
        line_copy8(p4, srcp, width, 2);
        uint8_t *array[] = {
            p0 - 2, p0 - 1, p0, p0 + 1, p0 + 2,
            p1 - 2, p1 - 1, p1, p1 + 1, p1 + 2,
            p2 - 2, p2 - 1, p2, p2 + 1, p2 + 2,
            p3 - 2, p3 - 1, p3, p3 + 1, p3 + 2,
            p4 - 2, p4 - 1, p4, p4 + 1, p4 + 2
        };

        for (int x = 0; x < width; x += 16) {
            __m128i sum[4] = { zero, zero, zero, zero };

            for (int i = 0; i < 25; i++) {
                __m128i xmm0, xmm1, xmm2;

                xmm0 = _mm_loadu_si128((__m128i *)(array[i] + x));
                xmm2 = _mm_unpackhi_epi8(xmm0, zero);
                xmm0 = _mm_unpacklo_epi8(xmm0, zero);
                
                xmm1 = _mm_unpackhi_epi16(xmm0, zero);
                xmm0 = _mm_unpacklo_epi16(xmm0, zero);
                sum[0] = _mm_add_epi32(sum[0], _mm_madd_epi16(xmm0, matrix[i]));
                sum[1] = _mm_add_epi32(sum[1], _mm_madd_epi16(xmm1, matrix[i]));

                xmm1 = _mm_unpackhi_epi16(xmm2, zero);
                xmm0 = _mm_unpacklo_epi16(xmm2, zero);
                sum[2] = _mm_add_epi32(sum[2], _mm_madd_epi16(xmm0, matrix[i]));
                sum[3] = _mm_add_epi32(sum[3], _mm_madd_epi16(xmm1, matrix[i]));
            }

            for (int i = 0; i < 4; i++) {
                __m128 sumfp = _mm_cvtepi32_ps(sum[i]);
                sumfp = _mm_mul_ps(sumfp, rdiv);
                sumfp = _mm_add_ps(sumfp, bias);
                if (!ch->saturate) {
                    sumfp = mm_abs_ps(sumfp);
                }
                sum[i] = _mm_cvttps_epi32(sumfp);
            }

            sum[0] = _mm_packs_epi32(sum[0], sum[1]);
            sum[1] = _mm_packs_epi32(sum[2], sum[3]);
            sum[0] = _mm_packus_epi16(sum[0], sum[1]);

            _mm_store_si128((__m128i *)(dstp + x), sum[0]);
        }
        dstp += stride;
        p0 = p1;
        p1 = p2;
        p2 = p3;
        p3 = p4;
        p4 = (p4 == end) ? orig : p4 + bstride;
    }
}