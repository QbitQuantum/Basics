static void GF_FUNC_ALIGN VS_CC
proc_16bit_sse2(convolution_hv_t *ch, uint8_t *buff, int bstride, int width,
                int height, int stride, uint8_t *d, const uint8_t *s)
{
    const uint16_t *srcp = (uint16_t *)s;
    uint16_t *dstp = (uint16_t *)d;
    stride /= 2;
    bstride /= 2;

    uint16_t *p0 = (uint16_t *)buff + 8;
    uint16_t *p1 = p0 + bstride;
    uint16_t *p2 = p1 + bstride;
    uint16_t *p3 = p2 + bstride;
    uint16_t *p4 = p3 + bstride;
    uint16_t *orig = p0, *end = p4;

    line_copy16(p0, srcp + 2 * stride, width, 2);
    line_copy16(p1, srcp + stride, width, 2);
    line_copy16(p2, srcp, width, 2);
    srcp += stride;
    line_copy16(p3, srcp, width, 2);

    __m128i zero = _mm_setzero_si128();
    __m128i all1 = _mm_cmpeq_epi32(zero, zero);
    __m128i one = _mm_srli_epi32(all1, 31);
    __m128 rdiv_h = _mm_set1_ps((float)ch->rdiv_h);
    __m128 rdiv_v = _mm_set1_ps((float)ch->rdiv_v);
    __m128 bias = _mm_set1_ps((float)ch->bias);

    __m128i matrix_h[5];
    __m128i matrix_v[5];
    int sign_h[5];
    int sign_v[5];
    for (int i = 0; i < 5; i++) {
        sign_h[i] = ch->m_h[i] < 0 ? 1 : 0;
        sign_v[i] = ch->m_v[i] < 0 ? 1 : 0;
        uint16_t val = sign_h[i] ? (uint16_t)(ch->m_h[i] * -1) : (uint16_t)ch->m_h[i];
        matrix_h[i] = _mm_set1_epi16((int16_t)val);
        val = sign_v[i] ? (uint16_t)(ch->m_v[i] * -1) : (uint16_t)ch->m_v[i];
        matrix_v[i] = _mm_set1_epi16((int16_t)val);
    }

    for (int y = 0; y < height; y++) {
        srcp += stride * (y < height - 2 ? 1 : -1);
        line_copy16(p4, srcp, width, 2);

        for (int x = 0; x < width; x += 8) {
            uint16_t *array[] = {
                p0 + x, p1 + x, p2 + x, p3 + x, p4 + x,
                p2 + x - 2, p2 + x - 1, dstp + x, p2 + x + 1, p2 + x + 2
            };

            for (int j = 0; j < 2; j++) {
                __m128i *matrix = j == 0 ? matrix_v : matrix_h;
                int *sign = j == 0 ? sign_v : sign_h;
                __m128 rdiv = j == 0 ? rdiv_v : rdiv_h;
                __m128i sum[2];
                sum[0] = _mm_setzero_si128();
                sum[1] = _mm_setzero_si128();

                for (int i = 0; i < 5; i++) {
                    __m128i xmm0, xmm1, xmm2;

                    xmm0 = _mm_loadu_si128((__m128i *)array[i + j * 5]);

                    xmm1 = _mm_mullo_epi16(xmm0, matrix[i]);
                    xmm0 = _mm_mulhi_epu16(xmm0, matrix[i]);
                    xmm2 = _mm_unpacklo_epi16(xmm1, xmm0);
                    xmm0 = _mm_unpackhi_epi16(xmm1, xmm0);

                    if (sign[i]) {
                        xmm2 = _mm_add_epi32(one, _mm_xor_si128(xmm2, all1));
                        xmm0 = _mm_add_epi32(one, _mm_xor_si128(xmm0, all1));
                    }
                    sum[0] = _mm_add_epi32(sum[0], xmm2);
                    sum[1] = _mm_add_epi32(sum[1], xmm0);
                }

                for (int i = 0; i < 2; i++) {
                    __m128 sumfp;
                    __m128i mask, temp;
                    sumfp = _mm_cvtepi32_ps(sum[i]);
                    sumfp = _mm_mul_ps(sumfp, rdiv);
                    if (j == 1) {
                        sumfp = _mm_add_ps(sumfp, bias);
                    }
                    sum[i] = _mm_cvttps_epi32(sumfp);

                    temp = _mm_srli_epi32(all1, 16);
                    mask = _mm_cmplt_epi32(sum[i], temp);
                    sum[i] = _mm_or_si128(_mm_and_si128(sum[i], mask),
                                          _mm_andnot_si128(mask, temp));
                    mask = _mm_cmpgt_epi32(sum[i], zero);
                    if (ch->saturate) {
                        sum[i] = _mm_and_si128(mask, sum[i]);
                    } else {
                        temp = _mm_add_epi32(one, _mm_xor_si128(sum[i], all1));
                        sum[i] = _mm_or_si128(_mm_and_si128(mask, sum[i]),
                                              _mm_andnot_si128(mask, temp));
                    }
                }

                sum[0] = mm_cast_epi32(sum[0], sum[1]);

                _mm_store_si128((__m128i *)(dstp + x), sum[0]);
            }
        }
        dstp += stride;
        p0 = p1;
        p1 = p2;
        p2 = p3;
        p3 = p4;
        p4 = (p4 == end) ? orig : p4 + bstride;
    }
}