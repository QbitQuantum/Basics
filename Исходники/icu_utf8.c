UErrorCode icu_utf16_from_utf8_cstr(struct icu_buf_utf16 *dest16,
                                    const char *src8cstr,
                                    UErrorCode *status)
{
    size_t src8cstr_len = 0;
    int32_t utf16_len = 0;

    *status = U_ZERO_ERROR;
    src8cstr_len = strlen(src8cstr);

    u_strFromUTF8(dest16->utf16, dest16->utf16_cap,
                  &utf16_len,
                  src8cstr, src8cstr_len, status);

    /* check for buffer overflow, resize and retry */
    if (*status == U_BUFFER_OVERFLOW_ERROR)
    {
        icu_buf_utf16_resize(dest16, utf16_len * 2);
        *status = U_ZERO_ERROR;
        u_strFromUTF8(dest16->utf16, dest16->utf16_cap,
                      &utf16_len,
                      src8cstr, src8cstr_len, status);
    }

    if (U_SUCCESS(*status) && utf16_len <= dest16->utf16_cap)
        dest16->utf16_len = utf16_len;
    else
        icu_buf_utf16_clear(dest16);

    return *status;
}