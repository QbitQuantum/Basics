int fts_icu_translate(buffer_t *dest_utf16, const UChar *src_utf16,
                      unsigned int src_len, UTransliterator *transliterator,
                      const char **error_r)
{
    UErrorCode err = U_ZERO_ERROR;
    int32_t utf16_len = src_len;
    UChar *dest_data;
    int32_t avail_uchars, limit = src_len;
    size_t dest_pos = dest_utf16->used;

    /* translation is done in-place in the buffer. try first with the
       current buffer size. */
    buffer_append(dest_utf16, src_utf16, src_len*sizeof(UChar));

    avail_uchars = (buffer_get_writable_size(dest_utf16)-dest_pos) / sizeof(UChar);
    dest_data = buffer_get_space_unsafe(dest_utf16, dest_pos,
                                        buffer_get_writable_size(dest_utf16)-dest_pos);
    utrans_transUChars(transliterator, dest_data, &utf16_len,
                       avail_uchars, 0, &limit, &err);
    if (err == U_BUFFER_OVERFLOW_ERROR) {
        /* try again with a larger buffer */
        err = U_ZERO_ERROR;
        avail_uchars = utf16_len;
        limit = utf16_len = src_len;
        buffer_write(dest_utf16, dest_pos,
                     src_utf16, src_len*sizeof(UChar));
        dest_data = buffer_get_space_unsafe(dest_utf16, dest_pos,
                                            avail_uchars * sizeof(UChar));
        utrans_transUChars(transliterator, dest_data, &utf16_len,
                           avail_uchars, 0, &limit, &err);
        i_assert(err != U_BUFFER_OVERFLOW_ERROR);
    }
    if (U_FAILURE(err)) {
        *error_r = t_strdup_printf("LibICU utrans_transUChars() failed: %s",
                                   u_errorName(err));
        buffer_set_used_size(dest_utf16, dest_pos);
        return -1;
    }
    buffer_set_used_size(dest_utf16, utf16_len * sizeof(UChar));
    return 0;
}