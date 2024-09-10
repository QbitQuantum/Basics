static uint32_t icu_utf16_sub(struct icu_buf_utf16 *dest16,
                          struct icu_buf_utf16 *src16,
                          const char *locale, char action,
                          UErrorCode *status)
{
    switch (action)
    {
    case 'l':
    case 'L':
        return u_strToLower(dest16->utf16, dest16->utf16_cap,
                            src16->utf16, src16->utf16_len,
                            locale, status);
    case 'u':
    case 'U':
        return u_strToUpper(dest16->utf16, dest16->utf16_cap,
                            src16->utf16, src16->utf16_len,
                            locale, status);
        break;
    case 't':
    case 'T':
        return u_strToTitle(dest16->utf16, dest16->utf16_cap,
                            src16->utf16, src16->utf16_len,
                            0, locale, status);
        break;
    case 'f':
    case 'F':
        return u_strFoldCase(dest16->utf16, dest16->utf16_cap,
                             src16->utf16, src16->utf16_len,
                             U_FOLD_CASE_DEFAULT, status);
        break;
    default:
        *status = U_UNSUPPORTED_ERROR;
        break;
    }
    return 0;
}