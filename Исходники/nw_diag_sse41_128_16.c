    int16_t * const restrict F_pr = _F_pr+PAD;
#ifdef PARASAIL_TABLE
    parasail_result_t *result = parasail_result_new_table1(s1Len, s2Len);
#else
#ifdef PARASAIL_ROWCOL
    parasail_result_t *result = parasail_result_new_rowcol1(s1Len, s2Len);
#else
    parasail_result_t *result = parasail_result_new();
#endif
#endif
    int32_t i = 0;
    int32_t j = 0;
    int32_t end_query = s1Len-1;
    int32_t end_ref = s2Len-1;
    int16_t score = NEG_INF;
    __m128i vNegInf = _mm_set1_epi16(NEG_INF);
    __m128i vOpen = _mm_set1_epi16(open);
    __m128i vGap  = _mm_set1_epi16(gap);
    __m128i vOne = _mm_set1_epi16(1);
    __m128i vN = _mm_set1_epi16(N);
    __m128i vGapN = _mm_set1_epi16(gap*N);
    __m128i vNegOne = _mm_set1_epi16(-1);
    __m128i vI = _mm_set_epi16(0,1,2,3,4,5,6,7);
    __m128i vJreset = _mm_set_epi16(0,-1,-2,-3,-4,-5,-6,-7);
    __m128i vMax = vNegInf;
    __m128i vILimit = _mm_set1_epi16(s1Len);
    __m128i vILimit1 = _mm_sub_epi16(vILimit, vOne);
    __m128i vJLimit = _mm_set1_epi16(s2Len);
    __m128i vJLimit1 = _mm_sub_epi16(vJLimit, vOne);
    __m128i vIBoundary = _mm_set_epi16(
            -open-0*gap,