void*  xmemset(void* dest, int c, size_t n)
{
    void* ret = dest;
    if (n < 16) {
        xmemset_lt16(dest, c, n);
        return ret;
    }

    __m256i mm = _mm256_set1_epi8((char)c);

    if (((unsigned long)dest & 31) == 0) {
        for ( ; n >= 256; n -= 256) {
            _mm256_store_si256((__m256i*)dest, mm);
            _mm256_store_si256((__m256i*)dest + 1, mm);
            _mm256_store_si256((__m256i*)dest + 2, mm);
            _mm256_store_si256((__m256i*)dest + 3, mm);
            _mm256_store_si256((__m256i*)dest + 4, mm);
            _mm256_store_si256((__m256i*)dest + 5, mm);
            _mm256_store_si256((__m256i*)dest + 6, mm);
            _mm256_store_si256((__m256i*)dest + 7, mm); // 8
            dest = (void*)((__m256i*)dest + 8);
        }

        if (n >= 128) {
            _mm256_store_si256((__m256i*)dest, mm);
            _mm256_store_si256((__m256i*)dest + 1, mm);
            _mm256_store_si256((__m256i*)dest + 2, mm);
            _mm256_store_si256((__m256i*)dest + 3, mm);
            dest = (void*)((__m256i*)dest + 4);
            n -= 128;
        }

        if (n >= 64) {
            _mm256_store_si256((__m256i*)dest, mm);
            _mm256_store_si256((__m256i*)dest + 1, mm);
            dest = (void*)((__m256i*)dest + 2);
            n -= 64;
        }

        if (n >= 32) {
            _mm256_store_si256((__m256i*)dest, mm);
            dest = (void*)((__m256i*)dest + 1);
            n -= 32;
        }

        if (n >= 16) {
            _mm_store_si128((__m128i*)dest, _mm_set1_epi8((char)c));
            dest = (void*)((__m128i*)dest + 1);
            n -= 16;
        }

    } else {
        for ( ; n >= 256; n -= 256) {
            _mm256_storeu_si256((__m256i*)dest, mm);
            _mm256_storeu_si256((__m256i*)dest + 1, mm);
            _mm256_storeu_si256((__m256i*)dest + 2, mm);
            _mm256_storeu_si256((__m256i*)dest + 3, mm);
            _mm256_storeu_si256((__m256i*)dest + 4, mm);
            _mm256_storeu_si256((__m256i*)dest + 5, mm);
            _mm256_storeu_si256((__m256i*)dest + 6, mm);
            _mm256_storeu_si256((__m256i*)dest + 7, mm); // 8
            dest = (void*)((__m256i*)dest + 8);
        }

        if (n >= 128) {
            _mm256_storeu_si256((__m256i*)dest, mm);
            _mm256_storeu_si256((__m256i*)dest + 1, mm);
            _mm256_storeu_si256((__m256i*)dest + 2, mm);
            _mm256_storeu_si256((__m256i*)dest + 3, mm);
            dest = (void*)((__m256i*)dest + 4);
            n -= 128;
        }

        if (n >= 64) {
            _mm256_storeu_si256((__m256i*)dest, mm);
            _mm256_storeu_si256((__m256i*)dest + 1, mm);
            dest = (void*)((__m256i*)dest + 2);
            n -= 64;
        }

        if (n >= 32) {
            _mm256_storeu_si256((__m256i*)dest, mm);
            dest = (void*)((__m256i*)dest + 1);
            n -= 32;
        }

        if (n >= 16) {
            _mm_storeu_si128((__m128i*)dest, _mm_set1_epi8((char)c));
            dest = (void*)((__m128i*)dest + 1);
            n -= 16;
        }
    }

    xmemset_lt16(dest, c, n);
    return ret;
}