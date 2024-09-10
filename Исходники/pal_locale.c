int32_t GlobalizationNative_GetDefaultLocaleName(UChar* value, int32_t valueLength)
{
    char localeNameBuffer[ULOC_FULLNAME_CAPACITY];
    UErrorCode status = U_ZERO_ERROR;

    const char* defaultLocale = DetectDefaultLocaleName();

    uloc_getBaseName(defaultLocale, localeNameBuffer, ULOC_FULLNAME_CAPACITY, &status);
    u_charsToUChars_safe(localeNameBuffer, value, valueLength, &status);

    if (U_SUCCESS(status))
    {
        int localeNameLen = FixupLocaleName(value, valueLength);

        char collationValueTemp[ULOC_KEYWORDS_CAPACITY];
        int32_t collationLen =
            uloc_getKeywordValue(defaultLocale, "collation", collationValueTemp, ULOC_KEYWORDS_CAPACITY, &status);

        if (U_SUCCESS(status) && collationLen > 0)
        {
            // copy the collation; managed uses a "_" to represent collation (not
            // "@collation=")
            u_charsToUChars_safe("_", &value[localeNameLen], valueLength - localeNameLen, &status);
            u_charsToUChars_safe(collationValueTemp, &value[localeNameLen + 1], valueLength - localeNameLen - 1, &status);
        }
    }

    return UErrorCodeToBool(status);
}