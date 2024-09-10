U_CAPI int32_t U_EXPORT2
u_strToTitle(UChar *dest, int32_t destCapacity,
             const UChar *src, int32_t srcLength,
             UBreakIterator *titleIter,
             const char *locale,
             UErrorCode *pErrorCode) {
    UCaseMap csm=UCASEMAP_INITIALIZER;
    setTempCaseMap(&csm, locale);
    if(titleIter!=NULL) {
        ubrk_setText(csm.iter=titleIter, src, srcLength, pErrorCode);
    } else {
        csm.iter=ubrk_open(UBRK_WORD, csm.locale, src, srcLength, pErrorCode);
    }
    int32_t length=ustrcase_map(
        &csm,
        dest, destCapacity,
        src, srcLength,
        ustrcase_internalToTitle, pErrorCode);
    if(titleIter==NULL && csm.iter!=NULL) {
        ubrk_close(csm.iter);
    }
    return length;
}