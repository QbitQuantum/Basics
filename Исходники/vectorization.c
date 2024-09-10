int valuesOK(cl_float8* to, cl_float8* from, size_t length) {
#ifdef DEBUG
    printf("Checking data of size: %lu\n", length);
#endif
    for(int i = 0; i < length; ++i) {
#ifdef __SSE__
        __cl_float4 __hostFirstValue = to->v4[0];
        __cl_float4 __hostSecondValue = to->v4[1];
        __cl_float4 __deviceFirstValue = from->v4[0];
        __cl_float4 __deviceSecondValue = from->v4[1];
        __m128i vcmp = (__m128i) _mm_cmpneq_ps(__hostFirstValue, __deviceFirstValue);
        uint16_t test = _mm_movemask_epi8(vcmp);
        __m128i vcmp_2 = (__m128i) _mm_cmpneq_ps(__hostSecondValue, __deviceSecondValue);
        uint16_t test_2 = _mm_movemask_epi8(vcmp_2);
        if( (test|test_2) != 0 ) return 0; // indicative that the result failed
#else
        #error "SSE not supported, which is required for example code to work!"  
#endif
    }
  return 1;
}