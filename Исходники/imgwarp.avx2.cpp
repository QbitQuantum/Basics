int warpAffineBlockline(int *adelta, int *bdelta, short* xy, short* alpha, int X0, int Y0, int bw)
{
    const int AB_BITS = MAX(10, (int)INTER_BITS);
    int x1 = 0;
    __m256i fxy_mask = _mm256_set1_epi32(INTER_TAB_SIZE - 1);
    __m256i XX = _mm256_set1_epi32(X0), YY = _mm256_set1_epi32(Y0);
    for (; x1 <= bw - 16; x1 += 16)
    {
        __m256i tx0, tx1, ty0, ty1;
        tx0 = _mm256_add_epi32(_mm256_loadu_si256((const __m256i*)(adelta + x1)), XX);
        ty0 = _mm256_add_epi32(_mm256_loadu_si256((const __m256i*)(bdelta + x1)), YY);
        tx1 = _mm256_add_epi32(_mm256_loadu_si256((const __m256i*)(adelta + x1 + 8)), XX);
        ty1 = _mm256_add_epi32(_mm256_loadu_si256((const __m256i*)(bdelta + x1 + 8)), YY);

        tx0 = _mm256_srai_epi32(tx0, AB_BITS - INTER_BITS);
        ty0 = _mm256_srai_epi32(ty0, AB_BITS - INTER_BITS);
        tx1 = _mm256_srai_epi32(tx1, AB_BITS - INTER_BITS);
        ty1 = _mm256_srai_epi32(ty1, AB_BITS - INTER_BITS);

        __m256i fx_ = _mm256_packs_epi32(_mm256_and_si256(tx0, fxy_mask),
            _mm256_and_si256(tx1, fxy_mask));
        __m256i fy_ = _mm256_packs_epi32(_mm256_and_si256(ty0, fxy_mask),
            _mm256_and_si256(ty1, fxy_mask));
        tx0 = _mm256_packs_epi32(_mm256_srai_epi32(tx0, INTER_BITS),
            _mm256_srai_epi32(tx1, INTER_BITS));
        ty0 = _mm256_packs_epi32(_mm256_srai_epi32(ty0, INTER_BITS),
            _mm256_srai_epi32(ty1, INTER_BITS));
        fx_ = _mm256_adds_epi16(fx_, _mm256_slli_epi16(fy_, INTER_BITS));
        fx_ = _mm256_permute4x64_epi64(fx_, (3 << 6) + (1 << 4) + (2 << 2) + 0);

        _mm256_storeu_si256((__m256i*)(xy + x1 * 2), _mm256_unpacklo_epi16(tx0, ty0));
        _mm256_storeu_si256((__m256i*)(xy + x1 * 2 + 16), _mm256_unpackhi_epi16(tx0, ty0));
        _mm256_storeu_si256((__m256i*)(alpha + x1), fx_);
    }
    _mm256_zeroupper();
    return x1;
}