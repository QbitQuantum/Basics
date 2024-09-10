size_t avx512bw_strstr_v3_memcmp(const char* string, size_t n, const char* needle, MEMCMP memeq_fun) {

    assert(n > 0);
    assert(k > 0);

    const __m512i first = _mm512_set1_epi8(needle[0]);
    const __m512i last  = _mm512_set1_epi8(needle[k - 1]);

    char* haystack = const_cast<char*>(string);
    char* end      = haystack + n;

    for (/**/; haystack < end; haystack += 64) {

        const __m512i block_first = _mm512_loadu_si512(haystack + 0);
        const __mmask64 first_eq  = _mm512_cmpeq_epi8_mask(block_first, first);

        if (first_eq == 0)
            continue;

        const __m512i block_last  = _mm512_loadu_si512(haystack + k - 1);
        uint64_t mask = _mm512_mask_cmpeq_epi8_mask(first_eq, block_last, last);

        while (mask != 0) {

            const uint64_t bitpos = bits::get_first_bit_set(mask);
            const char* s = reinterpret_cast<const char*>(haystack);

            if (memeq_fun(s + bitpos + 1, needle + 1)) {
                return (s - string) + bitpos;
            }

            mask = bits::clear_leftmost_set(mask);
        }
    }

    return size_t(-1);
}