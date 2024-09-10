}bool validate_utf8_sse(const char *src, size_t len) {
  const char *end = src + len;
  while (src + 16 < end) {
    __m128i chunk = _mm_loadu_si128((const __m128i *)(src));

    int asciiMask = _mm_movemask_epi8(chunk);
    if (!asciiMask) {
      src += 16;
      continue;
    }

    __m128i chunk_signed = _mm_add_epi8(chunk, _mm_set1_epi8(0x80));
    __m128i cond2 =
        _mm_cmplt_epi8(_mm_set1_epi8(0xc2 - 1 - 0x80), chunk_signed);
    __m128i state = _mm_set1_epi8((char)(0x0 | 0x80));
    state = _mm_blendv_epi8(state, _mm_set1_epi8((char)(0x2 | 0xc0)), cond2);

    __m128i cond3 =
        _mm_cmplt_epi8(_mm_set1_epi8(0xe0 - 1 - 0x80), chunk_signed);

    state = _mm_blendv_epi8(state, _mm_set1_epi8((char)(0x3 | 0xe0)), cond3);
    __m128i mask3 = _mm_slli_si128(cond3, 1);

    __m128i cond4 =
        _mm_cmplt_epi8(_mm_set1_epi8(0xf0 - 1 - 0x80), chunk_signed);

    // Fall back to the scalar processing
    if (_mm_movemask_epi8(cond4)) {
      break;
    }

    __m128i count = _mm_and_si128(state, _mm_set1_epi8(0x7));

    __m128i count_sub1 = _mm_subs_epu8(count, _mm_set1_epi8(0x1));

    __m128i counts = _mm_add_epi8(count, _mm_slli_si128(count_sub1, 1));

    __m128i shifts = count_sub1;
    shifts = _mm_add_epi8(shifts, _mm_slli_si128(shifts, 1));
    counts = _mm_add_epi8(
        counts, _mm_slli_si128(_mm_subs_epu8(counts, _mm_set1_epi8(0x2)), 2));
    shifts = _mm_add_epi8(shifts, _mm_slli_si128(shifts, 2));

    if (asciiMask ^ _mm_movemask_epi8(_mm_cmpgt_epi8(counts, _mm_set1_epi8(0))))
      return false; // error
    shifts = _mm_add_epi8(shifts, _mm_slli_si128(shifts, 4));

    if (_mm_movemask_epi8(_mm_cmpgt_epi8(
            _mm_sub_epi8(_mm_slli_si128(counts, 1), counts), _mm_set1_epi8(1))))
      return false; // error

    shifts = _mm_add_epi8(shifts, _mm_slli_si128(shifts, 8));

    __m128i mask = _mm_and_si128(state, _mm_set1_epi8(0xf8));
    shifts =
        _mm_and_si128(shifts, _mm_cmplt_epi8(counts, _mm_set1_epi8(2))); // <=1

    chunk =
        _mm_andnot_si128(mask, chunk); // from now on, we only have usefull bits

    shifts = _mm_blendv_epi8(shifts, _mm_srli_si128(shifts, 1),
                             _mm_srli_si128(_mm_slli_epi16(shifts, 7), 1));

    __m128i chunk_right = _mm_slli_si128(chunk, 1);

    __m128i chunk_low = _mm_blendv_epi8(
        chunk,
        _mm_or_si128(chunk, _mm_and_si128(_mm_slli_epi16(chunk_right, 6),
                                          _mm_set1_epi8(0xc0))),
        _mm_cmpeq_epi8(counts, _mm_set1_epi8(1)));

    __m128i chunk_high =
        _mm_and_si128(chunk, _mm_cmpeq_epi8(counts, _mm_set1_epi8(2)));

    shifts = _mm_blendv_epi8(shifts, _mm_srli_si128(shifts, 2),
                             _mm_srli_si128(_mm_slli_epi16(shifts, 6), 2));
    chunk_high = _mm_srli_epi32(chunk_high, 2);

    shifts = _mm_blendv_epi8(shifts, _mm_srli_si128(shifts, 4),
                             _mm_srli_si128(_mm_slli_epi16(shifts, 5), 4));
    chunk_high = _mm_or_si128(
        chunk_high, _mm_and_si128(_mm_and_si128(_mm_slli_epi32(chunk_right, 4),
                                                _mm_set1_epi8(0xf0)),
                                  mask3));
    int c = _mm_extract_epi16(counts, 7);
    int source_advance = !(c & 0x0200) ? 16 : !(c & 0x02) ? 15 : 14;

    __m128i high_bits = _mm_and_si128(chunk_high, _mm_set1_epi8(0xf8));
    if (!_mm_testz_si128(
            mask3,
            _mm_or_si128(_mm_cmpeq_epi8(high_bits, _mm_set1_epi8(0x00)),
                         _mm_cmpeq_epi8(high_bits, _mm_set1_epi8(0xd8)))))
      return false;

    shifts = _mm_blendv_epi8(shifts, _mm_srli_si128(shifts, 8),
                             _mm_srli_si128(_mm_slli_epi16(shifts, 4), 8));

    chunk_high = _mm_slli_si128(chunk_high, 1);

    __m128i shuf =
        _mm_add_epi8(shifts, _mm_set_epi8(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5,
                                          4, 3, 2, 1, 0));

    chunk_low = _mm_shuffle_epi8(chunk_low, shuf);
    chunk_high = _mm_shuffle_epi8(chunk_high, shuf);
    __m128i utf16_low = _mm_unpacklo_epi8(chunk_low, chunk_high);
    __m128i utf16_high = _mm_unpackhi_epi8(chunk_low, chunk_high);

    if (_mm_cmpestrc(_mm_cvtsi64_si128(0xfdeffdd0fffffffe), 4, utf16_high, 8,
                     _SIDD_UWORD_OPS | _SIDD_CMP_RANGES) |
        _mm_cmpestrc(_mm_cvtsi64_si128(0xfdeffdd0fffffffe), 4, utf16_low, 8,
                     _SIDD_UWORD_OPS | _SIDD_CMP_RANGES)) {
      return false;
    }

    src += source_advance;
  }
  return validate_utf8(src, end - src);
}