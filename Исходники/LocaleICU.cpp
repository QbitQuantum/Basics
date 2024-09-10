// We cannot use udat_*Symbols API to get standalone month names to use in
// calendar headers for Russian and potentially other languages. Instead,
// we have to format dates with patterns "LLLL" or "LLL" and set the
// display context to 'standalone'. See
// http://bugs.icu-project.org/trac/ticket/11552
UDateFormat* LocaleICU::openDateFormatForStandAloneMonthLabels(bool isShort)  const
{
    const UChar monthPattern[4] = {'L', 'L', 'L', 'L'};
    UErrorCode status = U_ZERO_ERROR;
    UDateFormat* formatter = udat_open(UDAT_PATTERN, UDAT_PATTERN, m_locale.data(), 0, -1, monthPattern, isShort ? 3 : 4, &status);
    udat_setContext(formatter, UDISPCTX_CAPITALIZATION_FOR_STANDALONE, &status);
    ASSERT(U_SUCCESS(status));
    return formatter;
}