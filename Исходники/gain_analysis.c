static void
filterButter(const Float_t* input, Float_t* output, size_t nSamples, const Float_t* kernel)
{   
#ifdef HAVE_SSE2
    __m128d __kernel, __result, __temp;
    __declspec(align(16)) Float_t __temp2[2];

    while (nSamples--) {
        __kernel = _mm_loadr_pd(&kernel[0]);
        __temp = _mm_loadu_pd(&input[-1]);
        __result = _mm_mul_pd(__temp, __kernel);
        __kernel = _mm_loadr_pd(&kernel[4]);
        __temp = _mm_loadu_pd(&output[-2]);
        __temp = _mm_mul_pd(__kernel, __temp);
        __result = _mm_sub_pd(__result, __temp);
        _mm_store_pd(__temp2, __result);
        *output = __temp2[0]
                + __temp2[1]
                + input [-2] * kernel[2];
                ;
        ++output;
        ++input;
    }
#else
    while (nSamples--) {
        *output =  
               input [0]  * kernel[0] - output[-1] * kernel[1]
             + input [-1] * kernel[2] - output[-2] * kernel[3]
             + input [-2] * kernel[4];
        ++output;
        ++input;
    }
#endif
}