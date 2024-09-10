uint64_t avx2_count_byte_popcount(const uint8_t* data, size_t size, uint8_t byte) {

    const __m256i v = _mm256_set1_epi8(byte);

    const uint8_t* end = data + size;
    const uint8_t* ptr = data;

    uint64_t result = 0;

    // 1. blocks of 8 registers
    while (ptr + 8*32 < end) {
        const __m256i eq0 = _mm256_cmpeq_epi8(v, _mm256_loadu_si256((const __m256i*)(ptr + 0*32)));
        const __m256i eq1 = _mm256_cmpeq_epi8(v, _mm256_loadu_si256((const __m256i*)(ptr + 1*32)));
        const __m256i eq2 = _mm256_cmpeq_epi8(v, _mm256_loadu_si256((const __m256i*)(ptr + 2*32)));
        const __m256i eq3 = _mm256_cmpeq_epi8(v, _mm256_loadu_si256((const __m256i*)(ptr + 3*32)));
        const __m256i eq4 = _mm256_cmpeq_epi8(v, _mm256_loadu_si256((const __m256i*)(ptr + 4*32)));
        const __m256i eq5 = _mm256_cmpeq_epi8(v, _mm256_loadu_si256((const __m256i*)(ptr + 5*32)));
        const __m256i eq6 = _mm256_cmpeq_epi8(v, _mm256_loadu_si256((const __m256i*)(ptr + 6*32)));
        const __m256i eq7 = _mm256_cmpeq_epi8(v, _mm256_loadu_si256((const __m256i*)(ptr + 7*32)));

        const __m256i eq0bit = _mm256_and_si256(eq0, _mm256_set1_epi8(0x01));
        const __m256i eq1bit = _mm256_and_si256(eq1, _mm256_set1_epi8(0x02));
        const __m256i eq2bit = _mm256_and_si256(eq2, _mm256_set1_epi8(0x04));
        const __m256i eq3bit = _mm256_and_si256(eq3, _mm256_set1_epi8(0x08));
        const __m256i eq4bit = _mm256_and_si256(eq4, _mm256_set1_epi8(0x10));
        const __m256i eq5bit = _mm256_and_si256(eq5, _mm256_set1_epi8(0x20));
        const __m256i eq6bit = _mm256_and_si256(eq6, _mm256_set1_epi8(0x40));
        const __m256i eq7bit = _mm256_and_si256(eq7, _mm256_set1_epi8(int8_t(0x80)));

        const __m256i m01    = _mm256_or_si256(eq0bit, eq1bit);
        const __m256i m23    = _mm256_or_si256(eq2bit, eq3bit);
        const __m256i m45    = _mm256_or_si256(eq4bit, eq5bit);
        const __m256i m67    = _mm256_or_si256(eq6bit, eq7bit);

        const __m256i m0123  = _mm256_or_si256(m01, m23);
        const __m256i m4567  = _mm256_or_si256(m45, m67);

        const __m256i merged = _mm256_or_si256(m0123, m4567);

        result += __builtin_popcountll(_mm256_extract_epi64(merged, 0));
        result += __builtin_popcountll(_mm256_extract_epi64(merged, 1));
        result += __builtin_popcountll(_mm256_extract_epi64(merged, 2));
        result += __builtin_popcountll(_mm256_extract_epi64(merged, 3));

        ptr += 8 * 32;
    }

    return result + scalar_count_bytes(ptr, end - ptr, byte);
}