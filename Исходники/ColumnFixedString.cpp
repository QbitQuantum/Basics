ColumnPtr ColumnFixedString::filter(const IColumn::Filter & filt, ssize_t result_size_hint) const
{
    size_t col_size = size();
    if (col_size != filt.size())
        throw Exception("Size of filter doesn't match size of column.", ErrorCodes::SIZES_OF_COLUMNS_DOESNT_MATCH);

    auto res = ColumnFixedString::create(n);

    if (result_size_hint)
        res->chars.reserve(result_size_hint > 0 ? result_size_hint * n : chars.size());

    const UInt8 * filt_pos = &filt[0];
    const UInt8 * filt_end = filt_pos + col_size;
    const UInt8 * data_pos = &chars[0];

#if __SSE2__
    /** A slightly more optimized version.
        * Based on the assumption that often pieces of consecutive values
        *  completely pass or do not pass the filter.
        * Therefore, we will optimistically check the parts of `SIMD_BYTES` values.
        */

    static constexpr size_t SIMD_BYTES = 16;
    const __m128i zero16 = _mm_setzero_si128();
    const UInt8 * filt_end_sse = filt_pos + col_size / SIMD_BYTES * SIMD_BYTES;
    const size_t chars_per_simd_elements = SIMD_BYTES * n;

    while (filt_pos < filt_end_sse)
    {
        int mask = _mm_movemask_epi8(_mm_cmpgt_epi8(_mm_loadu_si128(reinterpret_cast<const __m128i *>(filt_pos)), zero16));

        if (0 == mask)
        {
            /// Nothing is inserted.
            data_pos += chars_per_simd_elements;
        }
        else if (0xFFFF == mask)
        {
            res->chars.insert(data_pos, data_pos + chars_per_simd_elements);
            data_pos += chars_per_simd_elements;
        }
        else
        {
            size_t res_chars_size = res->chars.size();
            for (size_t i = 0; i < SIMD_BYTES; ++i)
            {
                if (filt_pos[i])
                {
                    res->chars.resize(res_chars_size + n);
                    memcpySmallAllowReadWriteOverflow15(&res->chars[res_chars_size], data_pos, n);
                    res_chars_size += n;
                }
                data_pos += n;
            }
        }

        filt_pos += SIMD_BYTES;
    }
#endif

    size_t res_chars_size = res->chars.size();
    while (filt_pos < filt_end)
    {
        if (*filt_pos)
        {
            res->chars.resize(res_chars_size + n);
            memcpySmallAllowReadWriteOverflow15(&res->chars[res_chars_size], data_pos, n);
            res_chars_size += n;
        }

        ++filt_pos;
        data_pos += n;
    }

    return std::move(res);
}