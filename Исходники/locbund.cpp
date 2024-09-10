static inline UNumberFormat * copyInvariantFormatter(ULocaleBundle *result, UNumberFormatStyle style) {
    U_NAMESPACE_USE
    Mutex lock(&gLock);
    if (result->fNumberFormat[style-1] == NULL) {
        if (gPosixNumberFormat[style-1] == NULL) {
            UErrorCode status = U_ZERO_ERROR;
            UNumberFormat *formatAlias = unum_open(style, NULL, 0, "en_US_POSIX", NULL, &status);
            if (U_SUCCESS(status)) {
                gPosixNumberFormat[style-1] = formatAlias;
                ucln_io_registerCleanup(UCLN_IO_LOCBUND, locbund_cleanup);
            }
        }
        /* Copy the needed formatter. */
        if (gPosixNumberFormat[style-1] != NULL) {
            UErrorCode status = U_ZERO_ERROR;
            result->fNumberFormat[style-1] = unum_clone(gPosixNumberFormat[style-1], &status);
        }
    }
    return result->fNumberFormat[style-1];
}