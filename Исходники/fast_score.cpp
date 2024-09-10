int cornerScore<16>(const uchar* ptr, const int pixel[], int threshold)
{
    const int K = 8, N = K*3 + 1;
    int k, v = ptr[0];
    short d[N];
    for( k = 0; k < N; k++ )
        d[k] = (short)(v - ptr[pixel[k]]);

#if CV_SSE2
    __m128i q0 = _mm_set1_epi16(-1000), q1 = _mm_set1_epi16(1000);
    for( k = 0; k < 16; k += 8 )
    {
        __m128i v0 = _mm_loadu_si128((__m128i*)(d+k+1));
        __m128i v1 = _mm_loadu_si128((__m128i*)(d+k+2));
        __m128i a = _mm_min_epi16(v0, v1);
        __m128i b = _mm_max_epi16(v0, v1);
        v0 = _mm_loadu_si128((__m128i*)(d+k+3));
        a = _mm_min_epi16(a, v0);
        b = _mm_max_epi16(b, v0);
        v0 = _mm_loadu_si128((__m128i*)(d+k+4));
        a = _mm_min_epi16(a, v0);
        b = _mm_max_epi16(b, v0);
        v0 = _mm_loadu_si128((__m128i*)(d+k+5));
        a = _mm_min_epi16(a, v0);
        b = _mm_max_epi16(b, v0);
        v0 = _mm_loadu_si128((__m128i*)(d+k+6));
        a = _mm_min_epi16(a, v0);
        b = _mm_max_epi16(b, v0);
        v0 = _mm_loadu_si128((__m128i*)(d+k+7));
        a = _mm_min_epi16(a, v0);
        b = _mm_max_epi16(b, v0);
        v0 = _mm_loadu_si128((__m128i*)(d+k+8));
        a = _mm_min_epi16(a, v0);
        b = _mm_max_epi16(b, v0);
        v0 = _mm_loadu_si128((__m128i*)(d+k));
        q0 = _mm_max_epi16(q0, _mm_min_epi16(a, v0));
        q1 = _mm_min_epi16(q1, _mm_max_epi16(b, v0));
        v0 = _mm_loadu_si128((__m128i*)(d+k+9));
        q0 = _mm_max_epi16(q0, _mm_min_epi16(a, v0));
        q1 = _mm_min_epi16(q1, _mm_max_epi16(b, v0));
    }
    q0 = _mm_max_epi16(q0, _mm_sub_epi16(_mm_setzero_si128(), q1));
    q0 = _mm_max_epi16(q0, _mm_unpackhi_epi64(q0, q0));
    q0 = _mm_max_epi16(q0, _mm_srli_si128(q0, 4));
    q0 = _mm_max_epi16(q0, _mm_srli_si128(q0, 2));
    threshold = (short)_mm_cvtsi128_si32(q0) - 1;
#else
    int a0 = threshold;
    for( k = 0; k < 16; k += 2 )
    {
        int a = std::min((int)d[k+1], (int)d[k+2]);
        a = std::min(a, (int)d[k+3]);
        if( a <= a0 )
            continue;
        a = std::min(a, (int)d[k+4]);
        a = std::min(a, (int)d[k+5]);
        a = std::min(a, (int)d[k+6]);
        a = std::min(a, (int)d[k+7]);
        a = std::min(a, (int)d[k+8]);
        a0 = std::max(a0, std::min(a, (int)d[k]));
        a0 = std::max(a0, std::min(a, (int)d[k+9]));
    }

    int b0 = -a0;
    for( k = 0; k < 16; k += 2 )
    {
        int b = std::max((int)d[k+1], (int)d[k+2]);
        b = std::max(b, (int)d[k+3]);
        b = std::max(b, (int)d[k+4]);
        b = std::max(b, (int)d[k+5]);
        if( b >= b0 )
            continue;
        b = std::max(b, (int)d[k+6]);
        b = std::max(b, (int)d[k+7]);
        b = std::max(b, (int)d[k+8]);

        b0 = std::min(b0, std::max(b, (int)d[k]));
        b0 = std::min(b0, std::max(b, (int)d[k+9]));
    }

    threshold = -b0-1;
#endif

    return threshold;
}