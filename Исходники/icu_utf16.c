struct icu_buf_utf16 *icu_buf_utf16_append(struct icu_buf_utf16 *dest16,
                                           const struct icu_buf_utf16 *src16)
{
    assert(dest16);
    if (!src16)
        return dest16;
    if (dest16 == src16)
        return 0;

    if (dest16->utf16_cap <= src16->utf16_len + dest16->utf16_len)
        icu_buf_utf16_resize(dest16, dest16->utf16_len + src16->utf16_len * 2);

    u_strncpy(dest16->utf16 + dest16->utf16_len,
              src16->utf16, src16->utf16_len);
    dest16->utf16_len += src16->utf16_len;

    return dest16;
}