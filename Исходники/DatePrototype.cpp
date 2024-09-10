static JSCell* formatLocaleDate(ExecState* exec, DateInstance*, double timeInMilliseconds, LocaleDateTimeFormat format)
{
    UDateFormatStyle timeStyle = (format != LocaleDate ? UDAT_LONG : UDAT_NONE);
    UDateFormatStyle dateStyle = (format != LocaleTime ? UDAT_LONG : UDAT_NONE);

    UErrorCode status = U_ZERO_ERROR;
    UDateFormat* df = udat_open(timeStyle, dateStyle, 0, 0, -1, 0, 0, &status);
    if (!df)
        return jsEmptyString(exec);

    UChar buffer[128];
    int32_t length;
    length = udat_format(df, timeInMilliseconds, buffer, 128, 0, &status);
    udat_close(df);
    if (status != U_ZERO_ERROR)
        return jsEmptyString(exec);

    return jsNontrivialString(exec, String(buffer, length));
}