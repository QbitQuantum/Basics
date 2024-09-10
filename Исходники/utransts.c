static void TestGetRulesAndSourceSet() {
    UErrorCode status = U_ZERO_ERROR;
    UTransliterator *utrans = utrans_openU(transSimpleID, -1, UTRANS_FORWARD, NULL, 0, NULL, &status);
    if ( U_SUCCESS(status) ) {
        USet* uset;
        UChar ubuf[kUBufMax];
        int32_t ulen;

        status = U_ZERO_ERROR;
        ulen = utrans_toRules(utrans, FALSE, ubuf, kUBufMax, &status);
        if ( U_FAILURE(status) || ulen <= 50 || ulen >= 100) {
            log_err("FAIL: utrans_toRules unescaped, expected noErr and len 50-100, got error=%s and len=%d\n",
                    u_errorName(status), ulen);
        }

        status = U_ZERO_ERROR;
        ulen = utrans_toRules(utrans, FALSE, NULL, 0, &status);
        if ( status != U_BUFFER_OVERFLOW_ERROR || ulen <= 50 || ulen >= 100) {
            log_err("FAIL: utrans_toRules unescaped, expected U_BUFFER_OVERFLOW_ERROR and len 50-100, got error=%s and len=%d\n",
                    u_errorName(status), ulen);
        }

        status = U_ZERO_ERROR;
        ulen = utrans_toRules(utrans, TRUE, ubuf, kUBufMax, &status);
        if ( U_FAILURE(status) || ulen <= 100 || ulen >= 200) {
            log_err("FAIL: utrans_toRules escaped, expected noErr and len 100-200, got error=%s and len=%d\n",
                    u_errorName(status), ulen);
        }

        status = U_ZERO_ERROR;
        uset = utrans_getSourceSet(utrans, FALSE, NULL, &status);
        ulen = uset_toPattern(uset, ubuf, kUBufMax, FALSE, &status);
        uset_close(uset);
        if ( U_FAILURE(status) || ulen <= 4 || ulen >= 20) {
            log_err("FAIL: utrans_getSourceSet useFilter, expected noErr and len 4-20, got error=%s and len=%d\n",
                    u_errorName(status), ulen);
        }

        status = U_ZERO_ERROR;
        uset = utrans_getSourceSet(utrans, TRUE, NULL, &status);
        ulen = uset_toPattern(uset, ubuf, kUBufMax, FALSE, &status);
        uset_close(uset);
        if ( U_FAILURE(status) || ulen <= 4 || ulen >= 20) {
            log_err("FAIL: utrans_getSourceSet ignoreFilter, expected noErr and len 4-20, got error=%s and len=%d\n",
                    u_errorName(status), ulen);
        }

        utrans_close(utrans);
    } else {
        log_data_err("FAIL: utrans_openRules(%s) failed, error=%s (Are you missing data?)\n",
                transSimpleCName, u_errorName(status));
    }
}