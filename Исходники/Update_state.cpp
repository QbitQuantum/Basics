inline void sum_offset( __m128i * X, __m128i * A, __m128i * B, __m128i * C, 
                        unsigned size_sse_ar, unsigned shift )
{
    for(unsigned i=0; i<size_sse_ar; ++i) 
    {
        __m128i tmp = _mm_and_si128(A[i],X[shift + i]);    
        A[i]=_mm_xor_si128(A[i],X[shift + i]);    
        C[i]=_mm_or_si128(C[i],_mm_and_si128(B[i],tmp));
        B[i]=_mm_xor_si128(B[i],tmp);
    }
}