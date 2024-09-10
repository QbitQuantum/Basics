    int32_t end_ref = 0;
    int64_t score = NEG_INF;
    __m256i vNegInf = _mm256_set1_epi64x(NEG_INF);
    __m256i vNegInf0 = _mm256_srli_si256_rpl(vNegInf, 8); /* shift in a 0 */
    __m256i vOpen = _mm256_set1_epi64x(open);
    __m256i vGap  = _mm256_set1_epi64x(gap);
    __m256i vOne = _mm256_set1_epi64x(1);
    __m256i vN = _mm256_set1_epi64x(N);
    __m256i vNegOne = _mm256_set1_epi64x(-1);
    __m256i vI = _mm256_set_epi64x(0,1,2,3);
    __m256i vJreset = _mm256_set_epi64x(0,-1,-2,-3);
    __m256i vMaxScore = vNegInf;
    __m256i vEndI = vNegInf;
    __m256i vEndJ = vNegInf;
    __m256i vILimit = _mm256_set1_epi64x(s1Len);
    __m256i vILimit1 = _mm256_sub_epi64(vILimit, vOne);
    __m256i vJLimit = _mm256_set1_epi64x(s2Len);
    __m256i vJLimit1 = _mm256_sub_epi64(vJLimit, vOne);
    

    /* convert _s1 from char to int in range 0-23 */
    for (i=0; i<s1Len; ++i) {
        s1[i] = matrix->mapper[(unsigned char)_s1[i]];
    }
    /* pad back of s1 with dummy values */
    for (i=s1Len; i<s1Len_PAD; ++i) {
        s1[i] = 0; /* point to first matrix row because we don't care */
    }

    /* convert _s2 from char to int in range 0-23 */
    for (j=0; j<s2Len; ++j) {