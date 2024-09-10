/*
Function:
GetMonthDayPattern

Gets the Month-Day DateTime pattern for the specified locale.
*/
static ResultCode GetMonthDayPattern(const char* locale,
                                     UChar* sMonthDay,
                                     int32_t stringCapacity)
{
    UErrorCode err = U_ZERO_ERROR;
    UDateTimePatternGenerator* pGenerator = udatpg_open(locale, &err);
    udatpg_getBestPattern(pGenerator, UDAT_MONTH_DAY_UCHAR, -1, sMonthDay, stringCapacity, &err);
    udatpg_close(pGenerator);
    return GetResultCode(err);
}