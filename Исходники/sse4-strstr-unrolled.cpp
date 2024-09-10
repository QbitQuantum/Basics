size_t sse4_strstr_unrolled_max36(const char* s, size_t n, const char* needle, size_t needle_size) {

    const __m128i zeros     = _mm_setzero_si128();
    const __m128i prefix    = sse::load(needle);
    const __m128i suffix1   = sse::load(needle + 4);
    const __m128i suffix2   = sse::load(needle + 16 + 4);
    const __m128i suff_mask = sse::mask_higher_bytes(needle_size - (16 + 4));

    for (size_t i = 0; i < n; i += 8) {

        const __m128i data   = sse::load(s + i);
        const __m128i result = _mm_mpsadbw_epu8(data, prefix, 0);

        const __m128i cmp    = _mm_cmpeq_epi16(result, zeros);

        unsigned mask = _mm_movemask_epi8(cmp) & 0x5555;

        while (mask != 0) {

            const auto bitpos = bits::get_first_bit_set(mask)/2;

            const __m128i c1 = _mm_cmpeq_epi8(sse::load(s + i + bitpos + 4), suffix1);
            const __m128i c2 = _mm_cmpeq_epi8(sse::load(s + i + bitpos + 16 + 4), suffix2);

            const __m128i c3 = _mm_or_si128(c2, suff_mask);
            const __m128i tmp = _mm_and_si128(c1, c3);

            if (_mm_movemask_epi8(tmp) == 0xffff) {

                return i + bitpos;
            }

            mask = bits::clear_leftmost_set(mask);
        }
    }

    return std::string::npos;
}