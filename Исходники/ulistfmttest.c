static void TestUListFmt() {
    const ListFmtTestEntry * lftep;
    for (lftep = listFmtTestEntries; lftep->locale != NULL ; lftep++ ) {
        UErrorCode status = U_ZERO_ERROR;
        UListFormatter *listfmt = ulistfmt_open(lftep->locale, &status);
        if ( U_FAILURE(status) ) {
            log_data_err("ERROR: ulistfmt_open fails for locale %s, status %s\n", lftep->locale, u_errorName(status));
        } else {
            UChar ubufActual[kUBufMax];
            int32_t ulenActual = ulistfmt_format(listfmt, strings, stringLengths, lftep->stringCount, ubufActual, kUBufMax, &status);
            if ( U_FAILURE(status) ) {
                log_err("ERROR: ulistfmt_format fails for locale %s count %d (real lengths), status %s\n", lftep->locale, lftep->stringCount, u_errorName(status));
            } else {
                UChar ubufExpected[kUBufMax];
                int32_t ulenExpected = u_unescape(lftep->expectedResult, ubufExpected, kUBufMax);
                if (ulenActual != ulenExpected || u_strncmp(ubufActual, ubufExpected, ulenExpected) != 0) {
                    log_err("ERROR: ulistfmt_format for locale %s count %d (real lengths), actual \"%s\" != expected \"%s\"\n", lftep->locale,
                            lftep->stringCount, aescstrdup(ubufActual, ulenActual), aescstrdup(ubufExpected, ulenExpected));
                }
            }
            /* try again with all lengths -1 */
            status = U_ZERO_ERROR;
            ulenActual = ulistfmt_format(listfmt, strings, stringLengthsNeg, lftep->stringCount, ubufActual, kUBufMax, &status);
            if ( U_FAILURE(status) ) {
                log_err("ERROR: ulistfmt_format fails for locale %s count %d (-1 lengths), status %s\n", lftep->locale, lftep->stringCount, u_errorName(status));
            } else {
                UChar ubufExpected[kUBufMax];
                int32_t ulenExpected = u_unescape(lftep->expectedResult, ubufExpected, kUBufMax);
                if (ulenActual != ulenExpected || u_strncmp(ubufActual, ubufExpected, ulenExpected) != 0) {
                    log_err("ERROR: ulistfmt_format for locale %s count %d (-1   lengths), actual \"%s\" != expected \"%s\"\n", lftep->locale,
                            lftep->stringCount, aescstrdup(ubufActual, ulenActual), aescstrdup(ubufExpected, ulenExpected));
                }
            }
            /* try again with NULL lengths */
            status = U_ZERO_ERROR;
            ulenActual = ulistfmt_format(listfmt, strings, NULL, lftep->stringCount, ubufActual, kUBufMax, &status);
            if ( U_FAILURE(status) ) {
                log_err("ERROR: ulistfmt_format fails for locale %s count %d (NULL lengths), status %s\n", lftep->locale, lftep->stringCount, u_errorName(status));
            } else {
                UChar ubufExpected[kUBufMax];
                int32_t ulenExpected = u_unescape(lftep->expectedResult, ubufExpected, kUBufMax);
                if (ulenActual != ulenExpected || u_strncmp(ubufActual, ubufExpected, ulenExpected) != 0) {
                    log_err("ERROR: ulistfmt_format for locale %s count %d (NULL lengths), actual \"%s\" != expected \"%s\"\n", lftep->locale,
                            lftep->stringCount, aescstrdup(ubufActual, ulenActual), aescstrdup(ubufExpected, ulenExpected));
                }
            }
            
            /* try calls that should return error */
            status = U_ZERO_ERROR;
            ulenActual = ulistfmt_format(listfmt, NULL, NULL, lftep->stringCount, ubufActual, kUBufMax, &status);
            if (status != U_ILLEGAL_ARGUMENT_ERROR || ulenActual > 0) {
                log_err("ERROR: ulistfmt_format for locale %s count %d with NULL strings, expected U_ILLEGAL_ARGUMENT_ERROR, got %s, result %d\n", lftep->locale,
                        lftep->stringCount, u_errorName(status), ulenActual);
            }
            status = U_ZERO_ERROR;
            ulenActual = ulistfmt_format(listfmt, strings, NULL, lftep->stringCount, NULL, kUBufMax, &status);
            if (status != U_ILLEGAL_ARGUMENT_ERROR || ulenActual > 0) {
                log_err("ERROR: ulistfmt_format for locale %s count %d with NULL result, expected U_ILLEGAL_ARGUMENT_ERROR, got %s, result %d\n", lftep->locale,
                        lftep->stringCount, u_errorName(status), ulenActual);
            }

            ulistfmt_close(listfmt);
        }
    }
}