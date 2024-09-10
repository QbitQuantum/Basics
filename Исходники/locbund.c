U_CDECL_END


static U_INLINE UNumberFormat * copyInvariantFormatter(ULocaleBundle *result, UNumberFormatStyle style) {
    if (result->fNumberFormat[style-1] == NULL) {
        UErrorCode status = U_ZERO_ERROR;
        UBool needsInit;

        UMTX_CHECK(NULL, gPosixNumberFormat[style-1] == NULL, needsInit);
        if (needsInit) {
            UNumberFormat *formatAlias = unum_open(style, NULL, 0, "en_US_POSIX", NULL, &status);

            /* Cache upon first request. */
            if (U_SUCCESS(status)) {
                umtx_lock(NULL);
                gPosixNumberFormat[style-1] = formatAlias;
                ucln_io_registerCleanup(UCLN_IO_LOCBUND, locbund_cleanup);
                umtx_unlock(NULL);
            }
        }

        /* Copy the needed formatter. */
        result->fNumberFormat[style-1] = unum_clone(gPosixNumberFormat[style-1], &status);
    }
    return result->fNumberFormat[style-1];
}