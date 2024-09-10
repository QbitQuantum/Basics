static void GF_FUNC_ALIGN VS_CC
proc_16bit_sse2(uint8_t *buff, int bstride, int width, int height, int stride,
                uint8_t *d, const uint8_t *s, edge_t *eh, uint16_t plane_max)
{
    const uint16_t *srcp = (uint16_t *)s;
    uint16_t *dstp = (uint16_t *)d;
    stride /= 2;
    bstride /= 2;

    uint16_t* p0 = (uint16_t *)buff + 8;
    uint16_t* p1 = p0 + bstride;
    uint16_t* p2 = p1 + bstride;
    uint16_t* p3 = p2 + bstride;
    uint16_t* p4 = p3 + bstride;
    uint16_t *orig = p0, *end = p4;

    line_copy16(p0, srcp + 2 * stride, width, 2);
    line_copy16(p1, srcp + stride, width, 2);
    line_copy16(p2, srcp, width, 2);
    srcp += stride;
    line_copy16(p3, srcp, width, 2);

    __m128i zero = _mm_setzero_si128();
    __m128 alpha = _mm_set1_ps((float)0.96043387);
    __m128 beta = _mm_set1_ps((float)0.39782473);
    __m128i pmax = _mm_set1_epi32(0xFFFF);
    __m128i min = _mm_set1_epi16((int16_t)eh->min);
    __m128i max = _mm_set1_epi16((int16_t)eh->max);

    for (int y = 0; y < height; y++) {
        srcp += stride * (y < height - 2 ? 1 : -1);
        line_copy16(p4, srcp, width, 2);
        uint16_t* posh[] = {p2 - 2, p2 - 1, p2 + 1, p2 + 2};
        uint16_t* posv[] = {p0, p1, p3, p4};

        for (int x = 0; x < width; x += 8) {
            __m128 sumx[2] = {(__m128)zero, (__m128)zero};
            __m128 sumy[2] = {(__m128)zero, (__m128)zero};

            for (int i = 0; i < 4; i++) {
                __m128 xmul = _mm_load_ps(ar_mulxf[i]);
                __m128i xmm0 = _mm_loadu_si128((__m128i *)(posh[i] + x));
                __m128i xmm1 = _mm_unpackhi_epi16(xmm0, zero);
                xmm0 = _mm_unpacklo_epi16(xmm0, zero);
                sumx[0] = _mm_add_ps(sumx[0], _mm_mul_ps(_mm_cvtepi32_ps(xmm0), xmul));
                sumx[1] = _mm_add_ps(sumx[1], _mm_mul_ps(_mm_cvtepi32_ps(xmm1), xmul));

                xmul = _mm_load_ps(ar_mulyf[i]);
                xmm0 = _mm_load_si128((__m128i *)(posv[i] + x));
                xmm1 = _mm_unpackhi_epi16(xmm0, zero);
                xmm0 = _mm_unpacklo_epi16(xmm0, zero);
                sumy[0] = _mm_add_ps(sumy[0], _mm_mul_ps(_mm_cvtepi32_ps(xmm0), xmul));
                sumy[1] = _mm_add_ps(sumy[1], _mm_mul_ps(_mm_cvtepi32_ps(xmm1), xmul));
            }

            __m128i out[2];
            for (int i = 0; i < 2; i++) {
                sumx[i] = mm_abs_ps(sumx[i]);
                sumy[i] = mm_abs_ps(sumy[i]);
                __m128 t0 = _mm_max_ps(sumx[i], sumy[i]);
                __m128 t1 = _mm_min_ps(sumx[i], sumy[i]);
                t0 = _mm_add_ps(_mm_mul_ps(alpha, t0), _mm_mul_ps(beta, t1));
                out[i] = _mm_srli_epi32(_mm_cvtps_epi32(t0), eh->rshift);
                out[i] = mm_min_epi32(out[i], pmax);
            }
            out[0] = mm_cast_epi32(out[0], out[1]);

            out[1] = MM_MIN_EPU16(out[0], max);
            out[1] = _mm_cmpeq_epi16(out[1], max);
            out[0] = _mm_or_si128(out[1], out[0]);

            out[1] = MM_MAX_EPU16(out[0], min);
            out[1] = _mm_cmpeq_epi16(out[1], min);
            out[0] = _mm_andnot_si128(out[1], out[0]);

            _mm_store_si128((__m128i *)(dstp + x), out[0]);
        }
        dstp += stride;
        p0 = p1;
        p1 = p2;
        p2 = p3;
        p3 = p4;
        p4 = (p4 == end) ? orig : p4 + bstride;
    }
}