/*
Function:
ToUnicode

Used by System.Globalization.IdnMapping.GetUnicodeCore to convert an ASCII name
to Unicode

Return values:
0: internal error during conversion.
>0: the length of the converted string (not including the null terminator).
*/
extern "C" int32_t GlobalizationNative_ToUnicode(
    int32_t flags, const UChar* lpSrc, int32_t cwSrcLength, UChar* lpDst, int32_t cwDstLength)
{
    UErrorCode err = U_ZERO_ERROR;
    UIDNAInfo info = UIDNA_INFO_INITIALIZER;

    UIDNA* pIdna = uidna_openUTS46(GetOptions(flags), &err);

    int32_t unicodeStrLen = uidna_nameToUnicode(pIdna, lpSrc, cwSrcLength, lpDst, cwDstLength, &info, &err);

    uidna_close(pIdna);

    return ((U_SUCCESS(err) || (err == U_BUFFER_OVERFLOW_ERROR)) && (info.errors == 0)) ? unicodeStrLen : 0;
}