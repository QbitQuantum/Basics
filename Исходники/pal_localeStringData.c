/*
Function:
GetLocaleInfoAmPm

Obtains the value of the AM or PM string for a locale.
*/
static UErrorCode GetLocaleInfoAmPm(const char* locale,
                                    int am,
                                    UChar* value,
                                    int32_t valueLength)
{
    UErrorCode status = U_ZERO_ERROR;
    UDateFormat* pFormat = udat_open(UDAT_DEFAULT, UDAT_DEFAULT, locale, NULL, 0, NULL, 0, &status);
    udat_getSymbols(pFormat, UDAT_AM_PMS, am ? 0 : 1, value, valueLength, &status);
    udat_close(pFormat);
    return status;
}