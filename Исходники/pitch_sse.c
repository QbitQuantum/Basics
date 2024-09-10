void xcorr_kernel_sse4_1(const opus_val16 * x, const opus_val16 * y, opus_val32 sum[ 4 ], int len)
{
    int j;

    __m128i vecX, vecX0, vecX1, vecX2, vecX3;
    __m128i vecY0, vecY1, vecY2, vecY3;
    __m128i sum0, sum1, sum2, sum3, vecSum;
    __m128i initSum;

    celt_assert(len >= 3);

    sum0 = _mm_setzero_si128();
    sum1 = _mm_setzero_si128();
    sum2 = _mm_setzero_si128();
    sum3 = _mm_setzero_si128();

    for (j=0;j<(len-7);j+=8)
    {
        vecX = _mm_loadu_si128((__m128i *)(&x[j + 0]));
        vecY0 = _mm_loadu_si128((__m128i *)(&y[j + 0]));
        vecY1 = _mm_loadu_si128((__m128i *)(&y[j + 1]));
        vecY2 = _mm_loadu_si128((__m128i *)(&y[j + 2]));
        vecY3 = _mm_loadu_si128((__m128i *)(&y[j + 3]));

        sum0 = _mm_add_epi32(sum0, _mm_madd_epi16(vecX, vecY0));
        sum1 = _mm_add_epi32(sum1, _mm_madd_epi16(vecX, vecY1));
        sum2 = _mm_add_epi32(sum2, _mm_madd_epi16(vecX, vecY2));
        sum3 = _mm_add_epi32(sum3, _mm_madd_epi16(vecX, vecY3));
    }

    sum0 = _mm_add_epi32(sum0, _mm_unpackhi_epi64( sum0, sum0));
    sum0 = _mm_add_epi32(sum0, _mm_shufflelo_epi16( sum0, 0x0E));

    sum1 = _mm_add_epi32(sum1, _mm_unpackhi_epi64( sum1, sum1));
    sum1 = _mm_add_epi32(sum1, _mm_shufflelo_epi16( sum1, 0x0E));

    sum2 = _mm_add_epi32(sum2, _mm_unpackhi_epi64( sum2, sum2));
    sum2 = _mm_add_epi32(sum2, _mm_shufflelo_epi16( sum2, 0x0E));

    sum3 = _mm_add_epi32(sum3, _mm_unpackhi_epi64( sum3, sum3));
    sum3 = _mm_add_epi32(sum3, _mm_shufflelo_epi16( sum3, 0x0E));

    vecSum = _mm_unpacklo_epi64(_mm_unpacklo_epi32(sum0, sum1),
          _mm_unpacklo_epi32(sum2, sum3));

    for (;j<(len-3);j+=4)
    {
        vecX = OP_CVTEPI16_EPI32_M64(&x[j + 0]);
        vecX0 = _mm_shuffle_epi32(vecX, 0x00);
        vecX1 = _mm_shuffle_epi32(vecX, 0x55);
        vecX2 = _mm_shuffle_epi32(vecX, 0xaa);
        vecX3 = _mm_shuffle_epi32(vecX, 0xff);

        vecY0 = OP_CVTEPI16_EPI32_M64(&y[j + 0]);
        vecY1 = OP_CVTEPI16_EPI32_M64(&y[j + 1]);
        vecY2 = OP_CVTEPI16_EPI32_M64(&y[j + 2]);
        vecY3 = OP_CVTEPI16_EPI32_M64(&y[j + 3]);

        sum0 = _mm_mullo_epi32(vecX0, vecY0);
        sum1 = _mm_mullo_epi32(vecX1, vecY1);
        sum2 = _mm_mullo_epi32(vecX2, vecY2);
        sum3 = _mm_mullo_epi32(vecX3, vecY3);

        sum0 = _mm_add_epi32(sum0, sum1);
        sum2 = _mm_add_epi32(sum2, sum3);
        vecSum = _mm_add_epi32(vecSum, sum0);
        vecSum = _mm_add_epi32(vecSum, sum2);
    }

    for (;j<len;j++)
    {
        vecX = OP_CVTEPI16_EPI32_M64(&x[j + 0]);
        vecX0 = _mm_shuffle_epi32(vecX, 0x00);

        vecY0 = OP_CVTEPI16_EPI32_M64(&y[j + 0]);

        sum0 = _mm_mullo_epi32(vecX0, vecY0);
        vecSum = _mm_add_epi32(vecSum, sum0);
    }

    initSum = _mm_loadu_si128((__m128i *)(&sum[0]));
    initSum = _mm_add_epi32(initSum, vecSum);
    _mm_storeu_si128((__m128i *)sum, initSum);
}