opus_val32 celt_inner_prod_sse4_1(const opus_val16 *x, const opus_val16 *y,
      int N)
{
    opus_int  i, dataSize16;
    opus_int32 sum;
    __m128i inVec1_76543210, inVec1_FEDCBA98, acc1;
    __m128i inVec2_76543210, inVec2_FEDCBA98, acc2;
    __m128i inVec1_3210, inVec2_3210;

    sum = 0;
    dataSize16 = N & ~15;

    acc1 = _mm_setzero_si128();
    acc2 = _mm_setzero_si128();

    for (i=0;i<dataSize16;i+=16) {
        inVec1_76543210 = _mm_loadu_si128((__m128i *)(&x[i + 0]));
        inVec2_76543210 = _mm_loadu_si128((__m128i *)(&y[i + 0]));

        inVec1_FEDCBA98 = _mm_loadu_si128((__m128i *)(&x[i + 8]));
        inVec2_FEDCBA98 = _mm_loadu_si128((__m128i *)(&y[i + 8]));

        inVec1_76543210 = _mm_madd_epi16(inVec1_76543210, inVec2_76543210);
        inVec1_FEDCBA98 = _mm_madd_epi16(inVec1_FEDCBA98, inVec2_FEDCBA98);

        acc1 = _mm_add_epi32(acc1, inVec1_76543210);
        acc2 = _mm_add_epi32(acc2, inVec1_FEDCBA98);
    }

    acc1 = _mm_add_epi32(acc1, acc2);

    if (N - i >= 8)
    {
        inVec1_76543210 = _mm_loadu_si128((__m128i *)(&x[i + 0]));
        inVec2_76543210 = _mm_loadu_si128((__m128i *)(&y[i + 0]));

        inVec1_76543210 = _mm_madd_epi16(inVec1_76543210, inVec2_76543210);

        acc1 = _mm_add_epi32(acc1, inVec1_76543210);
        i += 8;
    }

    if (N - i >= 4)
    {
        inVec1_3210 = OP_CVTEPI16_EPI32_M64(&x[i + 0]);
        inVec2_3210 = OP_CVTEPI16_EPI32_M64(&y[i + 0]);

        inVec1_3210 = _mm_mullo_epi32(inVec1_3210, inVec2_3210);

        acc1 = _mm_add_epi32(acc1, inVec1_3210);
        i += 4;
    }

    acc1 = _mm_add_epi32(acc1, _mm_unpackhi_epi64(acc1, acc1));
    acc1 = _mm_add_epi32(acc1, _mm_shufflelo_epi16(acc1, 0x0E));

    sum += _mm_cvtsi128_si32(acc1);

    for (;i<N;i++)
    {
        sum = silk_SMLABB(sum, x[i], y[i]);
    }

    return sum;
}