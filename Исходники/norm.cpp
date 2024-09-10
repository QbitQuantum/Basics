int normL1_(const uchar* a, const uchar* b, int n)
{
    int j = 0, d = 0;
#if CV_SSE
    __m128i d0 = _mm_setzero_si128();

    for( ; j <= n - 16; j += 16 )
    {
        __m128i t0 = _mm_loadu_si128((const __m128i*)(a + j));
        __m128i t1 = _mm_loadu_si128((const __m128i*)(b + j));

        d0 = _mm_add_epi32(d0, _mm_sad_epu8(t0, t1));
    }

    for( ; j <= n - 4; j += 4 )
    {
        __m128i t0 = _mm_cvtsi32_si128(*(const int*)(a + j));
        __m128i t1 = _mm_cvtsi32_si128(*(const int*)(b + j));

        d0 = _mm_add_epi32(d0, _mm_sad_epu8(t0, t1));
    }
    d = _mm_cvtsi128_si32(_mm_add_epi32(d0, _mm_unpackhi_epi64(d0, d0)));
#elif CV_NEON
    uint32x4_t v_sum = vdupq_n_u32(0.0f);
    for ( ; j <= n - 16; j += 16)
    {
        uint8x16_t v_dst = vabdq_u8(vld1q_u8(a + j), vld1q_u8(b + j));
        uint16x8_t v_low = vmovl_u8(vget_low_u8(v_dst)), v_high = vmovl_u8(vget_high_u8(v_dst));
        v_sum = vaddq_u32(v_sum, vaddl_u16(vget_low_u16(v_low), vget_low_u16(v_high)));
        v_sum = vaddq_u32(v_sum, vaddl_u16(vget_high_u16(v_low), vget_high_u16(v_high)));
    }

    uint CV_DECL_ALIGNED(16) buf[4];
    vst1q_u32(buf, v_sum);
    d = buf[0] + buf[1] + buf[2] + buf[3];
#endif
    {
        for( ; j <= n - 4; j += 4 )
        {
            d += std::abs(a[j] - b[j]) + std::abs(a[j+1] - b[j+1]) +
            std::abs(a[j+2] - b[j+2]) + std::abs(a[j+3] - b[j+3]);
        }
    }
    for( ; j < n; j++ )
        d += std::abs(a[j] - b[j]);
    return d;
}