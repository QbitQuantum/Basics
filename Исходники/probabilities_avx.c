static inline __m256d gmx_mm256_exp2_pd(__m256d x)
{
    /* Lower bound: We do not allow numbers that would lead to an IEEE fp representation exponent smaller than -126. */
    const __m256d arglimit = _mm256_set1_pd(1022.0);
    const __m128i expbase  = _mm_set1_epi32(1023);

    const __m256d P2       = _mm256_set1_pd(2.30933477057345225087e-2);
    const __m256d P1       = _mm256_set1_pd(2.02020656693165307700e1);
    const __m256d P0       = _mm256_set1_pd(1.51390680115615096133e3);
    /* Q2 == 1.0 */
    const __m256d Q1       = _mm256_set1_pd(2.33184211722314911771e2);
    const __m256d Q0       = _mm256_set1_pd(4.36821166879210612817e3);
    const __m256d one      = _mm256_set1_pd(1.0);
    const __m256d two      = _mm256_set1_pd(2.0);

    __m256d       valuemask;
    __m256i       iexppart;
    __m128i       iexppart128a, iexppart128b;
    __m256d       fexppart;
    __m256d       intpart;
    __m256d       z, z2;
    __m256d       PolyP, PolyQ;

    iexppart128a  = _mm256_cvtpd_epi32(x);
    intpart       = _mm256_round_pd(x, _MM_FROUND_TO_NEAREST_INT);

    /* Add exponent bias */
    iexppart128a   = _mm_add_epi32(iexppart128a, expbase);

    /* We now want to shift the exponent 52 positions left, but to achieve this we need
     * to separate the 128-bit register data into two registers (4x64-bit > 128bit)
     * shift them, and then merge into a single __m256d.
     * Elements 0/1 should end up in iexppart128a, and 2/3 in iexppart128b.
     * It doesnt matter what we put in the 2nd/4th position, since that data will be
     * shifted out and replaced with zeros.
     */
    iexppart128b   = _mm_shuffle_epi32(iexppart128a, _MM_SHUFFLE(3, 3, 2, 2));
    iexppart128a   = _mm_shuffle_epi32(iexppart128a, _MM_SHUFFLE(1, 1, 0, 0));

    iexppart128b   = _mm_slli_epi64(iexppart128b, 52);
    iexppart128a   = _mm_slli_epi64(iexppart128a, 52);

    iexppart  = _mm256_castsi128_si256(iexppart128a);
    iexppart  = _mm256_insertf128_si256(iexppart, iexppart128b, 0x1);

    valuemask = _mm256_cmp_pd(arglimit, gmx_mm256_abs_pd(x), _CMP_GE_OQ);
    fexppart  = _mm256_and_pd(valuemask, _mm256_castsi256_pd(iexppart));

    z         = _mm256_sub_pd(x, intpart);

    z2        = _mm256_mul_pd(z, z);

    PolyP     = _mm256_mul_pd(P2, z2);
    PolyP     = _mm256_add_pd(PolyP, P1);
    PolyQ     = _mm256_add_pd(z2, Q1);
    PolyP     = _mm256_mul_pd(PolyP, z2);
    PolyQ     = _mm256_mul_pd(PolyQ, z2);
    PolyP     = _mm256_add_pd(PolyP, P0);
    PolyQ     = _mm256_add_pd(PolyQ, Q0);
    PolyP     = _mm256_mul_pd(PolyP, z);

    z         = _mm256_mul_pd(PolyP, gmx_mm256_inv_pd(_mm256_sub_pd(PolyQ, PolyP)));
    z         = _mm256_add_pd(one, _mm256_mul_pd(two, z));

    z         = _mm256_mul_pd(z, fexppart);

    return z;
}