void imageFilterMean_SSE2(unsigned char *src1, unsigned char *src2, unsigned char *dst, int length)
{
    int n = length;

    // Compute first few values so we're on a 16-byte boundary in dst
    while( (((long)dst & 0xF) > 0) && (n > 0) ) {
        MEAN_PIXEL();
        --n; ++dst; ++src1; ++src2;
    }

    // Do bulk of processing using SSE2 (find the mean of 16 8-bit unsigned integers, with saturation)
    __m128i mask = _mm_set1_epi8(0x7F);
    while(n >= 16) {
        __m128i s1 = _mm_loadu_si128((__m128i*)src1);
        s1 = _mm_srli_epi16(s1, 1); // shift right 1
        s1 = _mm_and_si128(s1, mask); // apply byte-mask
        __m128i s2 = _mm_loadu_si128((__m128i*)src2);
        s2 = _mm_srli_epi16(s2, 1); // shift right 1
        s2 = _mm_and_si128(s2, mask); // apply byte-mask
        __m128i r = _mm_adds_epu8(s1, s2);
        _mm_store_si128((__m128i*)dst, r);

        n -= 16; src1 += 16; src2 += 16; dst += 16;
    }

    // If any bytes are left over, deal with them individually
    ++n;
    BASIC_MEAN();
}