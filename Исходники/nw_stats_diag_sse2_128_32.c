    int32_t similar = NEG_LIMIT;
    int32_t length = NEG_LIMIT;
    __m128i vNegLimit = _mm_set1_epi32(NEG_LIMIT);
    __m128i vPosLimit = _mm_set1_epi32(POS_LIMIT);
    __m128i vSaturationCheckMin = vPosLimit;
    __m128i vSaturationCheckMax = vNegLimit;
    __m128i vNegInf = _mm_set1_epi32(NEG_LIMIT);
    __m128i vOpen = _mm_set1_epi32(open);
    __m128i vGap  = _mm_set1_epi32(gap);
    __m128i vZero = _mm_set1_epi32(0);
    __m128i vNegInf0 = _mm_insert_epi32_rpl(vZero, NEG_LIMIT, 3);
    __m128i vOne = _mm_set1_epi32(1);
    __m128i vN = _mm_set1_epi32(N);
    __m128i vGapN = _mm_set1_epi32(gap*N);
    __m128i vNegOne = _mm_set1_epi32(-1);
    __m128i vI = _mm_set_epi32(0,1,2,3);
    __m128i vJreset = _mm_set_epi32(0,-1,-2,-3);
    __m128i vMaxH = vNegInf;
    __m128i vMaxM = vNegInf;
    __m128i vMaxS = vNegInf;
    __m128i vMaxL = vNegInf;
    __m128i vILimit = _mm_set1_epi32(s1Len);
    __m128i vILimit1 = _mm_sub_epi32(vILimit, vOne);
    __m128i vJLimit = _mm_set1_epi32(s2Len);
    __m128i vJLimit1 = _mm_sub_epi32(vJLimit, vOne);
    __m128i vIBoundary = _mm_set_epi32(
            -open-0*gap,
            -open-1*gap,
            -open-2*gap,
            -open-3*gap);
