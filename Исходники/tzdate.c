void getICUCurrentTime(char* icutime, double timeToCheck) {
    UDateFormat *fmt;
    const UChar *tz = 0;
    UChar *s = 0;
    UDateFormatStyle style = UDAT_RELATIVE;
    UErrorCode status = U_ZERO_ERROR;
    int32_t len = 0;
    int i;

    fmt = udat_open(style, style, 0, tz, -1,NULL,0, &status);

    len = udat_format(fmt, timeToCheck, 0, len, 0, &status);

    if (status == U_BUFFER_OVERFLOW_ERROR)
        status = U_ZERO_ERROR;

    s = (UChar*) malloc(sizeof(UChar) * (len+1));

    if(s == 0) 
        goto finish;

    udat_format(fmt, timeToCheck, s, len + 1, 0, &status);
    
    if (U_FAILURE(status)) 
        goto finish;

    /* +1 to NULL terminate */
    for(i = 0; i < len+1; i++) {
        icutime[i] = (char)s[i];
    }

finish:
    udat_close(fmt);
    free(s);
}