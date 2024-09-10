U_CAPI int32_t U_EXPORT2
ucasemap_utf8ToTitle(UCaseMap *csm,
                     char *dest, int32_t destCapacity,
                     const char *src, int32_t srcLength,
                     UErrorCode *pErrorCode) {
    UText utext=UTEXT_INITIALIZER;
    utext_openUTF8(&utext, (const char *)src, srcLength, pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        return 0;
    }
    if(csm->iter==NULL) {
        csm->iter=ubrk_open(UBRK_WORD, csm->locale,
                            NULL, 0,
                            pErrorCode);
    }
    ubrk_setUText(csm->iter, &utext, pErrorCode);
    int32_t length=ucasemap_mapUTF8(csm,
                   (uint8_t *)dest, destCapacity,
                   (const uint8_t *)src, srcLength,
                   ucasemap_internalUTF8ToTitle, pErrorCode);
    utext_close(&utext);
    return length;
}