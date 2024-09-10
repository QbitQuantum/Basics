static __inline __m128 ZMUL2(__m128 a, __m128 b, __m128 sign)
{
#ifdef SSE3_
    // a = a1.r  a1.i  a2.r  a2.i
    // b = b1.r  b1.i  b2.r  b2.i
    __m128 ar;

    ar = _mm_moveldup_ps(a);        // ar = a1.r  a1.r  a2.r  a2.r
    a = _mm_movehdup_ps(a);         // a  = a1.i  a1.i  a2.i  a2.i
    ar = _mm_mul_ps(ar, b);         // ar = a1.r*b1.r  a1.r*b1.i  a2.r*b2.r  a2.r*b2.i
    
    b  = _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 3, 0, 1)); // b  = b1.i  b1.r  b2.i  b2.r
    a = _mm_mul_ps(a, b);           // ai = a1.i*b1.i  a1.i*b1.r  a2.i*b2.i  a2.i*b2.r

    return _mm_addsub_ps(ar, a);    // a1.r*b1.r-a1.i*b1.i  a1.r*b1.i+a1.i*b1.r  a2.r*b2.r-a2.i*b2.i  a2.r*b2.i+a2.i*b2.r
#else
    // a = a1.r  a1.i  a2.r  a2.i
    // b = b1.r  b1.i  b2.r  b2.i
    __m128 ar;

    ar = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 2, 0, 0));     // ar = a1.r  a1.r  a2.r  a2.r
    a  = _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 3, 1, 1));     // ai = a1.i  a1.i  a2.i  a2.i
    ar = _mm_mul_ps(ar, b);                                 // ar = +a1.r*b1.r  +a1.r*b1.i  +a2.r*b2.r  +a2.r*b2.i
    
    a  = _mm_xor_ps(a, sign);                             // ai = a1.i  -a1.i  a2.i  -a2.i
    a  = _mm_mul_ps(a, b);                                // ai = a1.i*b1.r  -a1.i*b1.i  a2.i*b2.r  -a2.i*b2.i
    a  = _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 3, 0, 1));  // ai = -a1.i*b1.i  +a1.i*b1.r  -a2.i*b2.i  +a2.i*b2.r

    return _mm_add_ps(ar, a);   // a1.r*b1.r-a1.i*b1.i  a1.r*b1.i+a1.i*b1.r  a2.r*b2.r-a2.i*b2.i  a2.r*b2.i+a2.i*b2.r
#endif
}