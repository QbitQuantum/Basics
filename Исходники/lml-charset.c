static int _charset_detect(const char *in, size_t len, const char **charset, int *confidence)
{
    UCharsetDetector *csd;
    const UCharsetMatch *ucm;
    UErrorCode status = U_ZERO_ERROR;

    csd = ucsdet_open(&status);
    if ( U_FAILURE(status) ) {
        prelude_log(PRELUDE_LOG_ERR, "ICU: error opening character set detector: %s.\n", u_errorName(status));
        return -1;
    }

    ucsdet_setText(csd, in, len, &status);
    if( U_FAILURE(status) ) {
        prelude_log(PRELUDE_LOG_ERR, "ICU: error setting text for character set detection: %s.\n", u_errorName(status));
        goto error;
    }

    ucm = ucsdet_detect(csd, &status);
    if( U_FAILURE(status) ) {
        prelude_log(PRELUDE_LOG_ERR, "ICU: character set detection failed: %s.\n", u_errorName(status));
        goto error;
    }

    *confidence = ucsdet_getConfidence(ucm, &status);
    if ( U_FAILURE(status) ) {
        prelude_log(PRELUDE_LOG_ERR, "ICU: error retrieving character set confidence: %s.\n", u_errorName(status));
        goto error;
    }

    *charset = ucsdet_getName(ucm, &status);
    if ( U_FAILURE(status) ) {
        prelude_log(PRELUDE_LOG_ERR, "ICU: error retrieving character set name: %s.\n", u_errorName(status));
        goto error;
    }

    return 0;

error:
    ucsdet_close(csd);
    return -1;
}