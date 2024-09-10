U_CAPI int32_t U_EXPORT2
unum_format(    const    UNumberFormat*    fmt,
        int32_t           number,
        UChar*            result,
        int32_t           resultLength,
        UFieldPosition    *pos,
        UErrorCode*       status)
{
        return unum_formatInt64(fmt, number, result, resultLength, pos, status);
}