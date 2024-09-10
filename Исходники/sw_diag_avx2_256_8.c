    int8_t * const restrict del_pr = _del_pr+PAD;
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
    int32_t end_query = 0;
    int32_t end_ref = 0;
    int8_t score = NEG_INF;
    __m256i vNegInf = _mm256_set1_epi8(NEG_INF);
    __m256i vNegInf0 = _mm256_srli_si256_rpl(vNegInf, 1); /* shift in a 0 */
    __m256i vOpen = _mm256_set1_epi8(open);
    __m256i vGap  = _mm256_set1_epi8(gap);
    __m256i vZero = _mm256_set1_epi8(0);
    __m256i vOne16 = _mm256_set1_epi16(1);
    __m256i vNegOne16 = _mm256_set1_epi16(-1);
    __m256i vN16 = _mm256_set1_epi16(N);
    __m256i vILo16 = _mm256_set_epi16(16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31);
    __m256i vIHi16 = _mm256_set_epi16(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    __m256i vJresetLo16 = _mm256_set_epi16(-16,-17,-18,-19,-20,-21,-22,-23,-24,-25,-26,-27,-28,-29,-30,-31);
    __m256i vJresetHi16 = _mm256_set_epi16(0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10,-11,-12,-13,-14,-15);
    __m256i vMax = vNegInf;
    __m256i vEndILo = vNegInf;
    __m256i vEndIHi = vNegInf;
    __m256i vEndJLo = vNegInf;