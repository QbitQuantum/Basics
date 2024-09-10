/*
Function:
GetLocaleInfoAmPm

Obtains the value of the AM or PM string for a locale.
*/
UErrorCode GetLocaleInfoAmPm(const char* locale, bool am, UChar* value, int32_t valueLength)
{
    UErrorCode status = U_ZERO_ERROR;
    UDateFormat* pFormat = udat_open(UDAT_DEFAULT, UDAT_DEFAULT, locale, nullptr, 0, nullptr, 0, &status);
    UDateFormatHolder formatHolder(pFormat, status);

    if (U_FAILURE(status))
    {
        return status;
    }

    udat_getSymbols(pFormat, UDAT_AM_PMS, am ? 0 : 1, value, valueLength, &status);

    return status;
}