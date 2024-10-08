U_CAPI URegularExpression * U_EXPORT2
uregex_openC( const char           *pattern,
                    uint32_t        flags,
                    UParseError    *pe,
                    UErrorCode     *status) {
    if (U_FAILURE(*status)) {
        return NULL;
    }
    if (pattern == NULL) {
        *status = U_ILLEGAL_ARGUMENT_ERROR;
        return NULL;
    }

    UnicodeString patString(pattern);
    return uregex_open(patString.getBuffer(), patString.length(), flags, pe, status);
}